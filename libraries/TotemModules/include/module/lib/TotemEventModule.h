#ifndef TOTEMEVENTMODULE
#define TOTEMEVENTMODULE

#include "TotemModule.h"
#include "Channels.h"

struct TotemModuleData {
    TotemModule module;
    ModuleData *eventData;
    void (*eventHandler)(void);
    TotemModuleData(uint16_t number, uint16_t serial, void *context, TotemModule::DataReceiver2 receiver) :
    module(number, serial, context, receiver), eventData(nullptr), eventHandler(nullptr) { }
};

class TotemSimpleModule {
protected:
    TotemModuleData data;
public:
    TotemSimpleModule(uint16_t number, uint16_t serial, void *context = nullptr, TotemModule::DataReceiver2 receiver = nullptr) : data(number, serial, context, receiver) {}
};

class TotemEventModule : public TotemSimpleModule {
public:
    TotemEventModule(uint16_t number, uint16_t serial) : TotemSimpleModule(number, serial, this, onModuleDataReceive) {}
    
    void addEvent(void (*moduleEvt)(void)) {
        data.eventHandler = moduleEvt;
    }
private:
    static void onModuleDataReceive(void *context, ModuleData data) {
        TotemEventModule *instance = (TotemEventModule*)context;
        if (instance->data.eventHandler) {
            instance->data.eventData = &data;
            instance->data.eventHandler();
            instance->data.eventData = nullptr;
        }
    }
};

namespace Feature {

static constexpr uint32_t CMD(const char *cmdString) {
    return TotemModule::hashCmd(cmdString);
}

class Simple {
protected:
    TotemModuleData &parent;
    const uint32_t *cmdList;
    const uint16_t cmdListSize;

    void writeCustomCmd(uint32_t cmd, uint32_t value) {
        parent.module.write(cmd, value);
    }
    void writeCustomCmd(uint32_t cmd) {
        parent.module.write(cmd);
    }
    void writeChannel(uint8_t ch, uint32_t value) {
        if (ch == chAll)
            for (int i=0; i<cmdListSize; i++) { parent.module.write(cmdList[i], value); }
        else if (ch < cmdListSize)
            parent.module.write(cmdList[ch], value);
    }
    void writeChannel(uint8_t ch) {
        if (ch == chAll)
            for (int i=0; i<cmdListSize; i++) { parent.module.write(cmdList[i]); }
        else if (ch < cmdListSize)
            parent.module.write(cmdList[ch]);
    }
public:
    template <int SIZE>
    Simple(TotemModuleData &data, const uint32_t (&list)[SIZE]) : parent(data), cmdList(list), cmdListSize(SIZE) { }
};

class MultiEvent : public Simple {
    ModuleData tempData;
public:
    template <int SIZE>
    MultiEvent(TotemModuleData &data, const uint32_t (&list)[SIZE]) : Simple(data, list)
    { static_assert(SIZE > 1, "Multi event must use multiple commands"); }
    bool isEvent(uint8_t num) {
        if (num >= cmdListSize) return false;
        return parent.eventData && parent.eventData->getHashCmd() == cmdList[num];
    }
    void event(uint8_t num) {
        if (num >= cmdListSize) return;
        parent.module.subscribe(cmdList[num], 0);
    }
    void event(uint8_t num, uint32_t intervalMs) {
        if (num >= cmdListSize) return;
        if (intervalMs == 0)
            parent.module.unsubscribe(cmdList[num]);
        else
            parent.module.subscribe(cmdList[num], intervalMs);
    }
    void eventOnce(uint8_t num) {
        if (num >= cmdListSize) return;
        parent.module.read(cmdList[num]);
    }
protected:
    ModuleData* getCmd(uint8_t num) {
        if (isEvent(num)) {
            return parent.eventData;
        }
        else {
            tempData = parent.module.readWait(cmdList[num]);
            return &tempData;
        }
    }
    void writeChannel(uint8_t num, uint32_t value) {
        parent.module.write(cmdList[num], value);
    }
    TotemModule& getModule() {
        return parent.module;
    }
};
// Code indexer ignores protected inheritance
// Duplication of MultiEvent with protected access
class MultiEventHidden : public Simple {
    ModuleData tempData;
public:
    template <int SIZE>
    MultiEventHidden(TotemModuleData &data, const uint32_t (&list)[SIZE]) : Simple(data, list)
    { static_assert(SIZE > 1, "Multi event must use multiple commands"); }
protected:
    bool isEvent(uint8_t num) {
        if (num >= cmdListSize) return false;
        return parent.eventData && parent.eventData->getHashCmd() == cmdList[num];
    }
    void event(uint8_t num) {
        if (num >= cmdListSize) return;
        parent.module.subscribe(cmdList[num], 0);
    }
    void event(uint8_t num, uint32_t intervalMs) {
        if (num >= cmdListSize) return;
        if (intervalMs == 0)
            parent.module.unsubscribe(cmdList[num]);
        else
            parent.module.subscribe(cmdList[num], intervalMs);
    }
    void eventOnce(uint8_t num) {
        if (num >= cmdListSize) return;
        parent.module.read(cmdList[num]);
    }
    ModuleData* getCmd(uint8_t num) {
        if (isEvent(num)) {
            return parent.eventData;
        }
        else {
            tempData = parent.module.readWait(cmdList[num]);
            return &tempData;
        }
    }
    void writeChannel(uint8_t num, uint32_t value) {
        parent.module.write(cmdList[num], value);
    }
    TotemModule& getModule() {
        return parent.module;
    }
};
class SingleEvent : public Simple {
    ModuleData tempData;
public:
    template <int SIZE>
    SingleEvent(TotemModuleData &data, const uint32_t (&list)[SIZE]) : Simple(data, list) 
    { static_assert(SIZE == 1, "Single event must use only one command"); }
    bool isEvent() {
        return parent.eventData && parent.eventData->getHashCmd() == cmdList[0];
    }
    void event() {
        parent.module.subscribe(cmdList[0], 0);
    }
    void event(uint32_t intervalMs) {
        if (intervalMs == 0)
            parent.module.unsubscribe(cmdList[0]);
        else
            parent.module.subscribe(cmdList[0], intervalMs);
    }
    void eventOnce() {
        parent.module.read(cmdList[0]);
    }
protected:
    ModuleData* getCmd() {
        if (isEvent()) {
            return parent.eventData;
        }
        else {
            tempData = parent.module.readWait(cmdList[0]);
            return &tempData;
        }
    }
    TotemModule& getModule() {
        return parent.module;
    }
};

} // namespace Feature

#endif /* TOTEMEVENTMODULE */
