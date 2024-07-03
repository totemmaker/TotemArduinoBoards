/* 
 * Copyright 2023 Totem Technology, UAB
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */
#ifndef INCLUDE_TOTEM_RGB
#define INCLUDE_TOTEM_RGB

#include <stdint.h>

namespace _Totem {

class SingleRGB {
public:
    /// @brief Change color to RGB value
    /// @param r [0:255] amount of Red color
    /// @param g [0:255] amount of Green color
    /// @param b [0:255] amount of Blue color
    void color(uint8_t r, uint8_t g, uint8_t b);
    /// @brief Change color to HEX value
    /// @param hex [0:0xFFFFFF] 24-bit HEX color code
    void color(uint32_t hex);
    /// @brief Turn ON
    void on();
    /// @brief Turn OFF
    void off();
    /// @brief Toggle between ON / OFF state
    void toggle();
    /// @brief Is turned ON
    /// @return [true:false] - is ON
    bool isOn();
    ///////////////////////
    //   Configuration
    ///////////////////////
    /// @brief Get current RGB color
    /// @return [0:0xFFFFFF] 24-bit HEX color code
    uint32_t getColor();
    /// @brief Set RGB peripheral state
    /// @param state [true:false] enable / disable
    void setEnable(bool state);
    /// @brief Is RGB peripheral enabled
    /// @return [true:false] is enabled
    bool getEnable();
    /// @brief Set state
    /// @param state [true:false] - ON / OFF
    void setState(uint8_t state);
    /// @brief Get state
    /// @return [true:false] - ON / OFF
    int getState();

    SingleRGB(int8_t num);
private:
    /// @brief Private value
    const int8_t _num;
};

class RGBClass : public SingleRGB {
public:
    RGBClass();

    ///////////////////////
    //   Color control
    ///////////////////////
    
    /// @brief Set maximum LED brightness
    /// @param level [0:255] max brightness
    void setBrightness(uint8_t level);
    /// @brief Read configured maximum LED brightness
    /// @return [0:255] max brightness
    int getBrightness();
    /// @brief [deprecated] Set maximum LED brightness
    /// @param dim [0:255] max brightness
    [[deprecated("Replaced by setBrightness()")]]
    void setDim(uint8_t dim) { setBrightness(dim); }
    /// @brief [deprecated] Read configured maximum LED brightness
    /// @return [0:255] max brightness
    [[deprecated("Replaced by getBrightness()")]]
    int getDim() { return getBrightness(); }
    
    /// @brief Change all LED to Totem colors (green,yellow,blue)
    void colorTotem();
    /// @brief Access LED A control interface
    SingleRGB A;
    /// @brief Access LED B control interface
    SingleRGB B;
    /// @brief Access LED C control interface
    SingleRGB C;
    /// @brief Access LED D control interface
    SingleRGB D;
    /// @brief Access specific LED with array index
    /// @param num [0:3] array index
    /// @return single LED control interface
    SingleRGB& operator[](int num);
};

} // namespace _Totem

namespace totem {

extern _Totem::RGBClass RGB;

} // namespace totem

#endif /* INCLUDE_TOTEM_RGB */
