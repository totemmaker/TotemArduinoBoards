/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_CAN
#define INCLUDE_TOTEM_CAN

#if ARDUINO_ROBOBOARD_X4

namespace totem {

struct CANPacket {
    uint16_t ext : 1;
    uint16_t rtr : 1;
    int16_t filter;
    uint32_t id;
    uint8_t len;
    uint8_t data[8];
};

} // namespace totem

namespace _Totem {

class CANClass {
public:
    // Hardware filter

    /// @brief Set hardware filter registers. For advanced use only.
    /// @param code acceptance code
    /// @param mask acceptance mask
    /// @param single single or dual filter mode
    void setHardwareFilter(uint32_t code, uint32_t mask, bool single);
    /// @brief Set extended hardware filter
    /// @param id identifier [0:0x1FFFFFFF]
    /// @param mask mask
    void setHardwareFilterExt(uint32_t id, uint32_t mask) { setHardwareFilter(id << 3, ~(mask << 3), true); }
    /// @brief Set standard hardware filter
    /// @param id identifier [0:0x7FF]
    /// @param mask mask
    void setHardwareFilterStd(uint32_t id, uint32_t mask) { setHardwareFilter((id & 0x7FF) << 21, ~((mask & 0x7FF) << 21), true); }
    /// @brief Set standard (dual) hardware filter
    /// @param id1 identifier 1 [0:0x7FF]
    /// @param mask1 mask 1
    /// @param id2 identifier 2 [0:0x7FF]
    /// @param mask2 mask 2
    void setHardwareFilterDual(uint32_t id1, uint32_t mask1, uint32_t id2, uint32_t mask2) {
        setHardwareFilter(
            ((id1 & 0x7FF) << 21) | ((id2 & 0x7FF) << 5),
            ~(((mask1 & 0x7FF) << 21) | ((mask2 & 0x7FF) << 5)),
            false);
    }

    /// @brief Set standard software filter
    /// @param num filter number [0:15] (mailbox)
    /// @param id identifier [0:0x7FF]
    /// @param mask mask
    /// @return 0 if filter was added
    int setFilterStd(uint32_t num, uint32_t id, uint32_t mask);
    /// @brief Set extended software filter
    /// @param num filter number [0:15] (mailbox)
    /// @param id identifier [0:0x1FFFFFFF]
    /// @param mask mask
    /// @return 0 if filter was added
    int setFilterExt(uint32_t num, uint32_t id, uint32_t mask);
    /// @brief Reset specified filter (disable). Pass -1 to reset all.
    /// @param num filter number [0:15] (mailbox)
    /// @return 0 if filter was removed
    int resetFilter(int num = -1);

    /// @brief Start CAN bus in Normal mode
    /// @param baud baud (25, 50, 100, 125, 250, 500, 800, 1000)
    /// @param rxLen (optional) rx queue length. Default 30
    /// @param txLen (optional) tx queue length. Default 30
    /// @return 0 - if success
    int begin(uint32_t baud, uint16_t rxLen = 30, uint16_t txLen = 30);
    /// @brief Start CAN bus in Listen mode
    /// @param baud baud (25, 50, 100, 125, 250, 500, 800, 1000)
    /// @param rxLen (optional) rx queue length. Default 30
    /// @param txLen (optional) tx queue length. Default 30
    /// @return 0 - if success
    int beginListen(uint32_t baud, uint16_t rxLen = 30, uint16_t txLen = 30);
    /// @brief Start CAN bus in Loopback mode
    /// @param baud baud (25, 50, 100, 125, 250, 500, 800, 1000)
    /// @param rxLen (optional) rx queue length. Default 30
    /// @param txLen (optional) tx queue length. Default 30
    /// @return 0 - if success
    int beginLoopback(uint32_t baud, uint16_t rxLen = 30, uint16_t txLen = 30);

    /// @brief Stop CAN bus peripheral
    /// @return 0 - if stopped
    int end();

    /// @brief Check if CAN bus state is "running"
    /// @return true if running
    bool isRunning();

    /// @brief Switch between "running" and "stopped" states
    /// @param state true - "running", false - "stopped"
    /// @return 0 - if state changed
    int setEnable(bool state);

    /// @brief Register event function to receive CAN packets
    /// @param evtFunc function name
    /// @return 0 - if added
    int addEvent(void (*evtFunc)(void));
    /// @brief Register event function to receive CAN packets
    /// @param evtFunc function name
    /// @param arg pointer passed to registered function
    /// @return 0 - if added
    int addEvent(void (*evtFunc)(void*), void *arg);
    /// @brief Remove registered event function
    /// @param evtFunc function name
    /// @return 0 - if removed
    int removeEvent(void (*evtFunc)(void));
    /// @brief Remove registered event function
    /// @param evtFunc function name
    /// @param arg pointer passed to registered function
    /// @return 0 - if removed
    int removeEvent(void (*evtFunc)(void*), void *arg);

    /// @brief Write CAN packet (configure type trough parameters)
    /// @param ext true - extended, false - standard
    /// @param id identifier
    /// @param data data pointer
    /// @param len data length
    /// @param rtr true - rtr msg, false - data msg
    /// @return 0 - if success
    int writePacket(bool ext, uint32_t id, uint8_t *data, uint32_t len, bool rtr = false);
    /// @brief Write standard CAN packet
    /// @param id identifier [0:0x7FF]
    /// @param data data pointer
    /// @param len data length
    /// @return 0 - if success
    int writePacketStd(uint32_t id, uint8_t *data, uint32_t len) { return writePacket(false, id, data, len, false); }
    /// @brief Write extended CAN packet
    /// @param id identifier [0:0x1FFFFFFF]
    /// @param data data pointer
    /// @param len data length
    /// @return 0 - if success
    int writePacketExt(uint32_t id, uint8_t *data, uint32_t len) { return writePacket(true, id, data, len, false); }
    /// @brief Write standard RTR CAN packet
    /// @param id identifier [0:0x7FF]
    /// @param len data length field
    /// @return 0 - if success
    int writePacketStdRtr(uint32_t id, uint32_t len) { return writePacket(false, id, nullptr, len, true); }
    /// @brief Write extended RTR CAN packet
    /// @param id identifier [0:0x1FFFFFFF]
    /// @param len data length field
    /// @return 0 - if success
    int writePacketExtRtr(uint32_t id, uint32_t len) { return writePacket(true, id, nullptr, len, true); }

    /// @brief Read CAN packet from RX buffer
    /// @return true - if new packet read
    bool readPacket();
    /// @brief Wait until CAN packet is read from RX buffer
    /// @param timeout wait time. 0 - indefinitely
    /// @return true - if new packet read
    bool readPacketWait(uint32_t timeout = 0);

    /// @brief Get latest read CAN packet
    /// @return CANPacket structure
    totem::CANPacket getPacket();

    /// @brief Return CAN peripheral alerts
    /// @return alerts state
    int readAlerts();
    /// @brief Get RX packets count (waiting to read)
    /// @return queued RX packets
    int readRxCount();
};

} // namespace _Totem

namespace totem {

extern _Totem::CANClass CAN;

} // namespace totem

#endif // ARDUINO_ROBOBOARD_X4

#endif /* INCLUDE_TOTEM_CAN */
