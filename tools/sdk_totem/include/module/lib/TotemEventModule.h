/*
 Copyright (c) 2021 Totemmaker.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef TOTEMEVENTMODULE
#define TOTEMEVENTMODULE

#include "TotemModule.h"

namespace Feature {

static constexpr uint32_t CMD(const char *cmdString) {
    return TotemModule::hashCmd(cmdString);
}

struct Event {
    uint32_t cmd = 0;
    uint8_t *ptr = nullptr;
    int32_t value = 0;
    uint8_t enabled = 0;

    Event(uint32_t cmd) : cmd(cmd) { }
    Event(uint32_t cmd, uint8_t *ptr, uint32_t size) : cmd(cmd), ptr(ptr), value(size) { }
};

struct TotemModuleData {
    TotemModule module;
    Event *evtList;
    uint16_t listSize;
    ModuleData *activeEvent;
    TotemModuleData(uint16_t number, uint16_t serial, void *context, TotemModule::DataReceiver2 receiver, Event *evtList, uint16_t listSize) :
    module(number, serial, context, receiver), evtList(evtList), listSize(listSize), activeEvent(nullptr) { }
};

class NoEvent {
public:
    template <int SIZE>
    NoEvent(Feature::TotemModuleData &data, const uint32_t (&chList)[SIZE]) : parent(data), chList(chList), chListSize(SIZE) { }
    NoEvent(Feature::TotemModuleData &data) : parent(data), chList(nullptr), chListSize(0) { }

protected:
    TotemModuleData &parent;
    const uint32_t * const chList;
    const uint8_t chListSize;

    void writeCmd(uint32_t cmd, uint32_t value) {
        parent.module.write(cmd, value);
    }
    void writeCmd(uint32_t cmd) {
        parent.module.write(cmd);
    }
    void writeChannel(uint8_t ch, uint32_t value) {
        if (ch >= chListSize) return;
        parent.module.write(chList[ch], value);
    }
    void writeChannel(uint8_t ch) {
        if (ch >= chListSize) return;
        parent.module.write(chList[ch]);
    }
    Event* findEvent(uint32_t cmd) {
        for (int i=0; i<parent.listSize; i++) {
            if (parent.evtList[i].cmd == cmd)
                return &parent.evtList[i];
        }
        return nullptr;
    }
    ModuleData getCmd(uint32_t cmd) {
        Event *event = findEvent(cmd);
        if (event == nullptr) {
            ModuleData dummy;
            return dummy;
        }
        ModuleData moduleData(event->cmd, event->ptr, event->value);
        if (event->enabled == 0) {
            moduleData = parent.module.readWait(event->cmd);
        }
        return moduleData;
    }
    void setEvent(Event *event) {
        if (event == nullptr) return;
        parent.module.subscribe(event->cmd, 0);
        event->enabled = 1;
    }
    void setEvent(Event *event, uint32_t intervalMs) {
        if (event == nullptr) return;
        if (intervalMs == 0) {
            if (event->enabled != 2)
                parent.module.unsubscribe(event->cmd);
            event->enabled = 0;
        }
        else {
            parent.module.subscribe(event->cmd, intervalMs);
            event->enabled = 1;
        }
    }
    void readEvent(Event *event) {
        if (event == nullptr) return;
        parent.module.read(event->cmd);
        event->enabled = 2;
    }
};

class SingleEvent : public NoEvent {
public:
    template <int SIZE>
    SingleEvent(Feature::TotemModuleData &data, const uint32_t (&chList)[SIZE]) : NoEvent(data, chList) { }
    SingleEvent(Feature::TotemModuleData &data) : NoEvent(data) { }

    bool isEvent() {
        if (parent.activeEvent == nullptr) return false;
        for (int i=0; i<chListSize; i++) {
            if (parent.activeEvent->getHashCmd() == chList[i])
                return true;
        }
        return false;
    }
    void eventStart() {
        for (int i=0; i<chListSize; i++) {
            setEvent(findEvent(chList[i]));
        }
    }
    void eventStart(uint32_t intervalMs) {
        for (int i=0; i<chListSize; i++) {
            setEvent(findEvent(chList[i]), intervalMs);
        }
    }
    void eventStop() {
        eventStart(0);
    }
    void eventOnce() {
        for (int i=0; i<chListSize; i++) {
            readEvent(findEvent(chList[i]));
        }
    }
};

class ChannelEvent : public NoEvent {
public:
    template <int SIZE>
    ChannelEvent(Feature::TotemModuleData &data, const uint32_t (&chList)[SIZE]) : NoEvent(data, chList) { }
    ChannelEvent(Feature::TotemModuleData &data) : NoEvent(data) { }

    bool isEvent(uint8_t ch) {
        if (ch >= chListSize) return false;
        return parent.activeEvent && parent.activeEvent->getHashCmd() == chList[ch];
    }
    void eventStart(uint8_t ch) {
        if (ch == 0xFF) {
            for (ch=0; ch<chListSize; ch++)
                setEvent(findEvent(chList[ch]));
        }
        else if (ch < chListSize) {
            setEvent(findEvent(chList[ch]));
        }
    }
    void eventStart(uint8_t ch, uint32_t intervalMs) {
        if (ch == 0xFF) {
            for (ch=0; ch<chListSize; ch++)
                setEvent(findEvent(chList[ch]), intervalMs);
        }
        else if (ch < chListSize) {
            setEvent(findEvent(chList[ch]), intervalMs);
        }
    }
    void eventStop(uint8_t ch) {
        eventStart(ch, 0);
    }
    void eventOnce(uint8_t ch) {
        if (ch == 0xFF) {
            for (ch=0; ch<chListSize; ch++)
                readEvent(findEvent(chList[ch]));
        }
        else if (ch < chListSize) {
            readEvent(findEvent(chList[ch]));
        }
    }

protected:
    ModuleData getChannel(uint8_t ch) {
        if (ch >= chListSize) {
            ModuleData dummy;
            return dummy;
        }
        return getCmd(chList[ch]);
    }
};

class TotemEventModule {
protected:
    TotemModuleData data;
    void (*evtHandler)(void);
public:
    template <int SIZE>
    TotemEventModule(uint16_t number, uint16_t serial, Event (&eventsList)[SIZE])
    : data(number, serial, this, onModuleDataReceive, eventsList, SIZE) {}

    void addEvent(void (*moduleEvt)(void)) {
        evtHandler = moduleEvt;
    }
    uint32_t getEventCmd() {
        if (data.activeEvent == nullptr) return 0;
        return data.activeEvent->getHashCmd();
    }
    TotemModule& getController() {
        return data.module;
    }
private:
    void updateEventList(ModuleData &moduleData) {
        for (int i=0; i<data.listSize; i++) {
            if (data.evtList[i].cmd == moduleData.getHashCmd()) {
                if (data.evtList[i].ptr) {
                    uint8_t *ptr; int32_t len;
                    moduleData.getData(ptr, len);
                    if (len != data.evtList[i].value) continue;
                    for (int s=0; s<len; s++) { data.evtList[i].ptr[s] = ptr[s]; }
                }
                else {
                    data.evtList[i].value = moduleData.getInt();
                }
                break;
            }
        }
    }
    static void onModuleDataReceive(void *context, ModuleData moduleData) {
        TotemEventModule *instance = (TotemEventModule*)context;
        instance->updateEventList(moduleData);
        if (instance->evtHandler) {
            instance->data.activeEvent = &moduleData;
            instance->evtHandler();
            instance->data.activeEvent = nullptr;
        }
    }
};

} // namespace Feature

#endif /* TOTEMEVENTMODULE */
