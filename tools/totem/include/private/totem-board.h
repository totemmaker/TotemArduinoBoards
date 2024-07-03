/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef TOTEM_INCLUDE_BOARD
#define TOTEM_INCLUDE_BOARD

namespace _Totem {

class BoardClass {
public:
    ///////////////////////
    //   Board control
    ///////////////////////
    
    /// @brief Restart board
    /// @param async [true:false] delay action
    void restart(bool async = false);
    /// @brief Is USB port connected
    /// @return [true:false] is connected
    bool isUSB();
    /// @brief Wait if USB cable is plugged in
    /// @param timeout max wait time. 0 - indefinitely
    /// @return true - USB plugged out. false - timeout
    bool waitUSB(uint32_t timeout = 0);

    ///////////////////////
    // Control appearance
    ///////////////////////

    /// @brief Set custom RoboBoard name visible during App connection
    /// @param name string up to 30 characters
    void setName(const char *name);
    /// @brief Set 16-bit appearance identifier (robot model)
    /// @param model [0:0xFFFF] identifier
    void setModel(uint16_t model);
    /// @brief Set board RGB color. Displayed upon board start
    /// @param r [0:255] amount of Red color
    /// @param g [0:255] amount of Green color
    /// @param b [0:255] amount of Blue color
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    /// @brief Set board HEX color. Displayed upon board start
    /// @param hex [0:0xFFFFFF] 24-bit HEX color code
    void setColor(uint32_t hex);
    /// @brief Read custom RoboBoard name (visible during App connection)
    /// @return string up to 30 characters
    const char* getName();
    /// @brief Read 16-bit appearance identifier (robot model)
    /// @return [0:0xFFFF] model identifier
    uint16_t getModel();
    /// @brief Read board HEX color. Displayed upon board start
    /// @return [0:0xFFFFFF] 24-bit HEX color code
    uint32_t getColor();

    ///////////////////////
    //   Get versions
    ///////////////////////

    /// @brief Read RoboBoard type number
    /// @return [3:4] X3 or X4
    int getNumber();
    /// @brief Read RoboBoard revision number
    /// @return [10:30] v1.0, v3.0, ...
    int getRevision();
    /// @brief Read RoboBoard revision string
    /// @return "1.0" 
    char* getRevisionStr();
    /// @brief Read RoboBoard software build version number
    /// @return 32-bit encoded value
    uint32_t getSoftwareVersion();
    /// @brief Read RoboBoard software build version string
    /// @return "2.0.14-totem.1"
    char* getSoftwareVersionStr();
    /// @brief Read RoboBoard X4 co-processor firmware version number
    /// @return [100:200]
    int getDriverVersion();
    /// @brief Read RoboBoard X4 co-processor firmware version string
    /// @return "1.00"
    char* getDriverVersionStr();

    ///////////////////////
    // Board configuration
    ///////////////////////
    
    /// @brief Enable 3.3V LDO (RoboBoard X3 only)
    /// @param state [true:false] enable / disable
    void setEnable3V3(bool state);
    /// @brief Enable charging mode (power off + RGB indication)
    /// @param state [true:false] enable / disable
    void setChargingMode(bool state);
    /// @brief Enable RGB battery & app connect status display
    /// @param state [true:false] enable / disable
    void setStatusRGB(bool state);
    /// @brief Enable motor beep on power on and app connect
    /// @param state [true:false] enable / disable
    void setStatusSound(bool state);
    /// @brief Check if 3.3V LDO (RoboBoard X3 only) is enabled
    /// @return [true:false] enabled / disabled
    bool getEnable3V3();
    /// @brief Check if charging mode (power off + RGB indication) is enabled
    /// @return [true:false] enabled / disabled
    bool getChargingMode();
    /// @brief Check if RGB status display is enabled
    /// @return [true:false] enabled / disabled
    bool getStatusRGB();
    /// @brief Check if motor beep status display is enabled
    /// @return [true:false] enabled / disabled
    bool getStatusSound();
    ///////////////////////
    //  Settings storage
    ///////////////////////
    
    /// @brief Erase stored configuration
    /// @param async [true:false] delay action
    void settingsErase(bool async = false);
    /// @brief Store current configuration
    /// @param async [true:false] delay action
    void settingsSave(bool async = false);
};

} // namespace _Totem

namespace totem {

extern _Totem::BoardClass Board;

} // namespace totem

#endif /* TOTEM_INCLUDE_BOARD */
