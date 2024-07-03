/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_MODULE_DATA
#define INCLUDE_TOTEM_MODULE_DATA

namespace totem {

struct ModuleData {
    bool isInt() {
        return ptr == nullptr;
    }
    bool isString() {
        return ptr != nullptr;
    }
    int getInt() {
        return value;
    }
    const char *getString() {
        return reinterpret_cast<char*>(ptr);
    }
    template <typename Type>
    bool getData(Type **data) {
        return getData<Type>(*data);
    }
    template <typename Type>
    bool getData(Type *&data) {
        data = reinterpret_cast<Type*>(ptr);
        return ptr != nullptr;
    }
    template <typename Type>
    bool getData(Type **data, int32_t &len) {
        return getData<Type>(*data, len);
    }
    template <typename Type>
    bool getData(Type *&data, int32_t &len) {
        data = reinterpret_cast<Type*>(ptr);
        len = (ptr == nullptr) ? 0 : value;
        return ptr != nullptr;
    }
    uint32_t getHashCmd() {
        return cmdHash;
    }
    ModuleData(uint32_t cmd, uint8_t *str, uint32_t len) : cmdHash(cmd), ptr(str), value(len) { }
    ModuleData(uint32_t cmd, int32_t value) : cmdHash(cmd), ptr(0), value(value) { }
    ModuleData() {}
private:
    uint32_t cmdHash = 0;
    uint8_t *ptr = nullptr;
    int32_t value = 0;
};

} // namespace totem

#endif /* INCLUDE_TOTEM_MODULE_DATA */
