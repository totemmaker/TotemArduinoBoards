/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_EVENT_MODULE
#define INCLUDE_TOTEM_EVENT_MODULE

#include "totem-module.h"

namespace Feature {

// Convert string to 32bit hash
static constexpr uint32_t CMD(const char *cmdString) {
    return TotemModule::hashCmd(cmdString);
}
// Event data object
struct Event {
    ModuleData data;
    struct {
        uint8_t subscribed : 1;
        uint8_t streaming : 1;
    } state = { .subscribed = 0, .streaming = 0 };

    Event(uint32_t cmd) : data(cmd, 0, 0) { }
    Event(uint32_t cmd, uint8_t *ptr, uint32_t size) : data(cmd, ptr, size) { }
};
// Totem module with event functionality
class TotemEventModule {
    Event *eventList;
    uint16_t eventListCnt;
public:
    template <int SIZE>
    TotemEventModule(uint16_t number, uint16_t serial, Event (&eventList)[SIZE]) : 
    eventList(eventList), eventListCnt(SIZE), module(number, serial, this, onModuleDataReceive) { }
    ~TotemEventModule() { TotemModule::removeEventHandler(eventHandlerInst, module.getSerial() << 16 | module.getNumber()); }
    // Register event handler function
    using EventHandler = void (*)(int evt);
    void addEvent(EventHandler evtHandler) {
        // Register event handler
        TotemModule::addEventHandler(&eventHandlerInst,
        module.getSerial() << 16 | module.getNumber(),
        evtHandler);
    }
    // Reset module subscriptions
    void reset() {
        for (int i=0; i<eventListCnt; i++) {
            if (eventList[i].state.streaming) {
                module.unsubscribe(eventList[i].data.getHashCmd());
            }
            eventList[i].state.streaming = 0;
            eventList[i].state.subscribed = 0;
        }
    }

    TotemModule module;
protected:
    // Write 32bit int value to command
    void writeCmdInt(uint32_t cmd, int32_t value) {
        module.write(cmd, value);
    }
    // Read command returning ModuleData object
    ModuleData readCmd(uint32_t cmd) {
        // Return event object if command is added to the list
        Event *event = findEvent(cmd);
        if (event) {
            // Subscribe if not already streaming
            if (!event->state.streaming) {
                event->state.subscribed = 1;
                module.subscribe(cmd, 0, true);
                return module.readWait(cmd);
            }
            // Return cached value
            return event->data;
        }
        else {
            // Perform simple read until result is received
            return module.readWait(cmd);
        }
    }
    // Read command returning 32bit integer
    int32_t readCmdInt(uint32_t cmd) {
        return readCmd(cmd).getInt();
    }
    // Call registered event handler
    virtual void callEventHandler(int event) {
        if (eventHandlerInst) TotemModule::callEventHandler(
        module.getSerial() << 16 | module.getNumber(), event);
    }

private:
    // Event handler instance
    void *eventHandlerInst = nullptr;
    // Find event index by command
    int findEventIdx(uint32_t cmd) {
        for (int i=0; i<eventListCnt; i++) {
            if (eventList[i].data.getHashCmd() == cmd)
                return i;
        }
        return -1;
    }
    // Find event object by command
    Event* findEvent(uint32_t cmd) {
        int idx = findEventIdx(cmd);
        return idx == -1 ? nullptr : &eventList[idx];
    }
    // Module data handler
    static void onModuleDataReceive(void *context, ModuleData moduleData, int ack) {
        TotemEventModule *instance = (TotemEventModule*)context;
        int idx = instance->findEventIdx(moduleData.getHashCmd());
        if (idx != -1) {
            // Get event object
            Event *event = &(instance->eventList[idx]);
            // Update event state and call handler
            if (ack == -1) {
                event->state.subscribed = 0;
            }
            else if (ack == 1 && event->state.subscribed) {
                event->state.streaming = 1;
            }
            else if (event->state.streaming) {
                // Save latest data and call event handler
                event->data = moduleData;
                instance->callEventHandler(((uint32_t)instance->module.getNumber() << 16) + idx);
            }
        }
    }
};

} // namespace Feature

#endif /* INCLUDE_TOTEM_EVENT_MODULE */
