#ifndef TOTEMMODULEX
#define TOTEMMODULEX

#include "TotemModule.h"

class TotemModuleX {
public:
    TotemModuleX(uint16_t number, uint16_t serial) : module(number, serial, this, onModuleDataReceive) {}
    
    void addEvent(void (*moduleEvt)(void)) {
        eventHandler = moduleEvt;
    }
protected:
    TotemModule module;
    static constexpr uint32_t C(const char *cmdString) {
        return TotemModule::hashCmd(cmdString);
    }
private:
    ModuleData *eventData = nullptr;
    void (*eventHandler)(void) = nullptr;

    static void onModuleDataReceive(void *context, ModuleData data) {
        TotemModuleX *instance = (TotemModuleX*)context;
        if (instance->eventHandler) {
            instance->eventData = &data;
            instance->eventHandler();
            instance->eventData = nullptr;
        }
    }
    
    friend class TotemModuleFeature;
};

class TotemModuleFeature {
    TotemModuleX &parent;
    const uint32_t cmd;
    ModuleData tempData;
public:
    TotemModuleFeature(TotemModuleX *parent, uint32_t cmd = 0) : parent(*parent), cmd(cmd) {

    }
    bool isEvent() {
        return parent.eventData && parent.eventData->getHashCmd() == cmd;
    }
    void event() {
        parent.module.subscribe(cmd, 0);
    }
    void event(uint32_t intervalMs) {
        if (intervalMs == 0)
            parent.module.unsubscribe(cmd);
        else
            parent.module.subscribe(cmd, intervalMs);
    }
    void eventOnce() {
        parent.module.read(cmd);
    }
protected:
    ModuleData* getCmd() {
        if (isEvent()) {
            return parent.eventData;
        }
        else {
            tempData = parent.module.readWait(cmd);
            return &tempData;
        }
    }
    void writeCmd(uint32_t value) {
        parent.module.write(cmd, value);
    }
    void writeCmd(uint32_t cmd, uint32_t value) {
        parent.module.write(cmd, value);
    }
    TotemModule& getModule() {
        return parent.module;
    }
    static constexpr uint32_t C(const char *cmdString) {
        return TotemModuleX::C(cmdString);
    }
};

#endif /* TOTEMMODULEX */
