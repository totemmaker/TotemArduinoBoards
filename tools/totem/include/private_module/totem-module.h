/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_MODULE
#define INCLUDE_TOTEM_MODULE

#include <stdint.h>

#include "totem-module-data.h"

class TotemModule {
public:
    TotemModule *next = nullptr;
    using DataReceiver = void (*)(ModuleData data);
    using DataReceiver2 = void (*)(void *context, ModuleData data);
    using DataReceiver3 = void (*)(void *context, ModuleData data, int ack);

    TotemModule(uint16_t number, uint16_t serial, void *context, DataReceiver3 receiver);
    TotemModule(uint16_t number, uint16_t serial, void *context, DataReceiver2 receiver);
    TotemModule(uint16_t number, uint16_t serial, DataReceiver receiver);
    TotemModule(uint16_t number, uint16_t serial = 0);

    ~TotemModule();

    bool write(const char *command) {
        return write(hashCmd(command));
    }
    bool write(const char *command, int32_t value) {
        return write(hashCmd(command), value);
    }
    template <int VSIZE>
    bool write(const char *command, const char (&value)[VSIZE]) {
        return write(hashCmd(command), value);
    }
    bool write(const char *command, const uint8_t *bytes, uint32_t bytesCount) {
        return write(hashCmd(command), bytes, bytesCount);
    }
    bool write(const char *command, int8_t A, int8_t B, int8_t C, int8_t D) {
        return write(hashCmd(command), A, B, C, D);
    }
    bool write(const char *command, int8_t A, int8_t B, int8_t C) {
        return write(hashCmd(command), A, B, C);
    }
    bool writeWait(const char *command) {
        return writeWait(hashCmd(command));
    }
    bool writeWait(const char *command, int32_t value) {
        return writeWait(hashCmd(command), value);
    }
    template <int VSIZE>
    bool writeWait(const char *command, const char (&value)[VSIZE]) {
        return writeWait(hashCmd(command), value);
    }
    bool writeWait(const char *command, const uint8_t *bytes, uint32_t bytesCount) {
        return writeWait(hashCmd(command), bytes, bytesCount);
    }
    bool writeWait(const char *command, int8_t A, int8_t B, int8_t C, int8_t D) {
        return writeWait(hashCmd(command), A, B, C, D);
    }
    bool writeWait(const char *command, int8_t A, int8_t B, int8_t C) {
        return writeWait(hashCmd(command), A, B, C);
    }
    
    bool read(const char *command) {
        return read(hashCmd(command));
    }
    ModuleData readWait(const char *command) {
        return readWait(hashCmd(command));
    }
    bool readWait(const char *command, ModuleData &result) {
        return readWait(hashCmd(command), result);
    }
    bool subscribe(const char *command, int intervalMs = 0) {
        return subscribe(hashCmd(command), intervalMs);
    }
    bool subscribeWait(const char *command, int intervalMs = 0) {
        return subscribeWait(hashCmd(command), intervalMs);
    }
    bool unsubscribe(const char *command) {
        return unsubscribe(hashCmd(command));
    }
    bool unsubscribeWait(const char *command) {
        return unsubscribeWait(hashCmd(command));
    }
    void attachOnData(DataReceiver receiver) {
        this->receiver = receiver;
    }

    bool write(uint32_t command) {
        return moduleWrite(command, false);
    }
    bool write(uint32_t command, int32_t value) {
        return moduleWrite(command, value, false);
    }
    template <int VSIZE>
    bool write(uint32_t command, const char (&value)[VSIZE]) {
        return moduleWrite(command, value, VSIZE-1, false);
    }
    bool write(uint32_t command, const uint8_t *bytes, uint32_t bytesCount) {
        return moduleWrite(command, reinterpret_cast<const char*>(bytes), bytesCount, false);
    }
    bool write(uint32_t command, int8_t A, int8_t B, int8_t C, int8_t D) {
        return moduleWrite(command, toValue(A, B, C, D), false);
    }
    bool write(uint32_t command, int8_t A, int8_t B, int8_t C) {
        return moduleWrite(command, toValue(0, A, B, C), false);
    }
    bool writeWait(uint32_t command) {
        return moduleWrite(command, true);
    }
    bool writeWait(uint32_t command, int32_t value) {
        return moduleWrite(command, value, true);
    }
    template <int VSIZE>
    bool writeWait(uint32_t command, const char (&value)[VSIZE]) {
        return moduleWrite(command, value, VSIZE-1, true);
    }
    bool writeWait(uint32_t command, const uint8_t *bytes, uint32_t bytesCount) {
        return moduleWrite(command, reinterpret_cast<const char*>(bytes), bytesCount, true);
    }
    bool writeWait(uint32_t command, int8_t A, int8_t B, int8_t C, int8_t D) {
        return moduleWrite(command, toValue(A, B, C, D), true);
    }
    bool writeWait(uint32_t command, int8_t A, int8_t B, int8_t C) {
        return moduleWrite(command, toValue(0, A, B, C), true);
    }

    bool read(uint32_t command) {
        return moduleRead(command, false);
    }
    ModuleData readWait(uint32_t command) {
        response.command = command;
        response.waiting = true;
        bool succ = moduleRead(response.command, true);
        if (!succ || response.waiting) {
            ModuleData data(0, (uint8_t*)"", 0);
            return data;
        }
        return response.data;
    }
    bool readWait(uint32_t command, ModuleData &result) {
        response.command = command;
        response.waiting = true;
        bool succ = moduleRead(response.command, true);
        if (!succ || response.waiting) return false;
        result = response.data;
        return true;
    }
    bool subscribe(uint32_t command, int intervalMs = 0, bool responseReq = false) {
        return moduleSubscribe(command, intervalMs, responseReq);
    }
    bool subscribeWait(uint32_t command, int intervalMs = 0) {
        return moduleSubscribe(command, intervalMs, true);
    }
    bool unsubscribe(uint32_t command) {
        return subscribe(command, -1);
    }
    bool unsubscribeWait(uint32_t command) {
        return subscribeWait(command, -1);
    }

    void setNumber(uint16_t number) {
        this->number = number;
    }
    void setSerial(uint16_t serial) {
        this->serial = serial;
    }
    uint16_t getNumber() {
        return number;
    }
    uint16_t getSerial() {
        return serial;
    }
    uint32_t getError() {
        return requestError;
    }
    bool ping();
    
    static constexpr uint32_t hashCmd(const char *command) {
        return fnv1a32Hash(2166136261, command);
    }
    static constexpr uint16_t hashModel(const char *model) {
        return fnv1a16Hash(2166136261, model);
    }

    void onMessageReceive(void *message);

    static void removeEventHandler(void *handlerInstance, uint32_t address);
    static void addEventHandler(void **handlerInstance, uint32_t address, void (*func)(int evt));
    static void callEventHandler(uint32_t address, int evt);

    static bool find(uint16_t number = 0, uint16_t serial = 0);
    static uint16_t foundNumber;
    static uint16_t foundSerial;
private:
    uint16_t number;
    uint16_t serial;
    volatile struct {
        int    command = -1;
        bool succ = false;
        bool waiting = false;
    } request;
    void giveResponse(int command, bool succ);
    void prepareWait(int command);
    bool waitResponse(int timeout);
    bool isFromModule(uint16_t number, uint16_t serial);
    void onModuleData(ModuleData msgData, int ack);
    uint32_t requestError = 0;
    void setError(uint32_t err) {
        requestError = err;
    }
    uint32_t toValue(int8_t A, int8_t B, int8_t C, int8_t D) {
        uint32_t value = 0;
        value |= (static_cast<uint32_t>(A) & 0xFF) << 24;
        value |= (static_cast<uint32_t>(B) & 0xFF) << 16;
        value |= (static_cast<uint32_t>(C) & 0xFF) << 8;
        value |= (static_cast<uint32_t>(D) & 0xFF);
        return value;
    }
    
    struct {
        int command;
        ModuleData data;
        bool waiting;
    } response;
    void *receiverContext = nullptr;
    DataReceiver receiver = nullptr;
    DataReceiver2 receiver2 = nullptr;
    DataReceiver3 receiver3 = nullptr;

    bool moduleWrite(int command, bool responseReq);
    bool moduleWrite(int command, int value, bool responseReq);
    bool moduleWrite(int command, const char *data, uint32_t len, bool responseReq);
    bool moduleRead(int command, bool blocking);
    bool moduleSubscribe(int command, int interval, bool responseReq);
    
    static constexpr uint32_t fnv1a32Hash(uint32_t hash, const char *cmd) {
        return (*cmd) ? fnv1a32Hash(((hash ^ *cmd ) * 16777619), cmd+1) : hash;
    }
    static constexpr uint32_t fnv1a16Hash(uint32_t hash, const char *cmd) {
        return (*cmd) ? fnv1a16Hash(((hash ^ *cmd ) * 16777619), cmd+1) : ((hash>>16) ^ (hash & ((uint32_t)0xFFFF)));
    }

    void *mutex = nullptr;
};

#endif /* INCLUDE_TOTEM_MODULE */
