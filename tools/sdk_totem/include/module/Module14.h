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
#ifndef MODULE14
#define MODULE14

#include "lib/TotemEventModule.h"

namespace Features14 {
using namespace Feature;
namespace cmd {
enum Commands {
    sensor_threshold = CMD("sensor/threshold"),
    sensor_range     = CMD("sensor/range"),
    sensor_raw       = CMD("sensor/raw"),
    line_junction    = CMD("line/junction"),
    line_color       = CMD("line/color"),
    line_pos         = CMD("line/pos"),
    led              = CMD("led"),
};
} // namespace cmd
class Line : public SingleEvent {
    const uint32_t events[2] = {cmd::line_pos, cmd::line_color};
public:
    Line(TotemModuleData &d) : SingleEvent(d, events) { }
    // Get line position [-35:35]
    int getPosition() {
        return this->getCmd(cmd::line_pos).getInt();
    }
    // Get color of detected line ['W','B',0]
    void setColor(char color) {
        writeCmd(cmd::line_color, color);
    }
    // Get color of detected line ['W','B',0]
    char getColor() {
        return this->getCmd(cmd::line_color).getInt();
    }
    // Check if detected line color is white
    bool isColorWhite() {
        return this->getColor() == 'W';
    }
    // Check if detected line color is black
    bool isColorBlack() {
        return this->getColor() == 'B';
    }
    // Check if lines junction is detected (got from color)
    bool isJunction() {
        return this->getColor() == 0;
    }
    // Check if line is currently detected
    bool isDetected() {
        return this->getColor() != 0;
    }
};
class Sensor : public SingleEvent {
    const uint32_t events[2] = {cmd::sensor_range, cmd::sensor_raw};
public:
    Sensor(TotemModuleData &d) : SingleEvent(d, events) { }
    // Get accuracy of line detection [0:100]%. Higher is better
    int getAccuracy() {
        return this->getCmd(cmd::sensor_range).getInt();
    }
    // Get raw sensor contrast readings [0:100]%
    void getRaw(uint8_t raw[8]) {
        uint8_t *ptr;
        if (!(this->getCmd(cmd::sensor_raw).getData(ptr)))
            return;
        for (int i=0; i<8; i++) 
            raw[i] = ptr[i];
    }
    // Set minimum required accuracy to start line following [0:100]%
    void setThreshold(uint8_t contrast) {
        this->writeCmd(cmd::sensor_threshold, contrast);
    }
};
template <int LED_CNT>
class Led : public NoEvent {
    uint8_t ledState = 0;
public:
    Led(TotemModuleData &d) : NoEvent(d) { }
    // Turn LED on
    void on(uint8_t ch) {
        this->set(ch, 1);
    }
    // Turn LED off
    void off(uint8_t ch) {
        this->set(ch, 0);
    }
    // Toggle LED (on / off)
    void toggle(uint8_t ch) {
        if (ch == chAll)
            this->setBinary(~ledState);
        else
            this->set(ch, !(this->isOn(ch)));
    }
    // Set LED state [HIGH:LOW] (on / off)
    void set(uint8_t ch, uint8_t state) {
        if (ch == chAll)
            ledState = state ? 0xFF : 0;
        else if (ch < LED_CNT) {
            if (state) ledState |= (1 << ch);
            else ledState &= ~(1 << ch);
        }
        else
            return;
        this->writeCmd(cmd::led, ledState); 
    }
    // Read LED state [HIGH:LOW] (on / off)
    bool isOn(uint8_t ch) {
        if (ch >= LED_CNT) return false;
        return ledState & (1 << ch);
    }
    
    // Reset LED to default operation (display line position)
    void reset() {
        ledState = 0;
        this->writeCmd(cmd::led, -1);
    }
    // Set LED state by binary representation [B00000000:B11111111]
    void setBinary(uint8_t bin) {
        uint8_t reverse = 0;
        ledState = bin;
        for (int i=0; i<8; i++) {
            reverse <<= 1;
            reverse |= (bin & 1);
            bin >>= 1;
        }
        this->writeCmd(cmd::led, reverse);
    }
};
} // namespace Features14

class Module14 : public Feature::TotemEventModule {
    uint8_t rawBuffer[8];
    Feature::Event eventsList[5] = {
        cmd::sensor_threshold,
        cmd::sensor_range,
        {cmd::sensor_raw, rawBuffer, 8},
        cmd::line_color,
        cmd::line_pos,
    };
public:
    using cmd = Features14::cmd::Commands;
    Features14::Line line;
    Features14::Sensor sensor;
    Features14::Led<8> led;

    Module14(uint16_t serial = 0) : Feature::TotemEventModule(14, serial, eventsList),
    line(data), sensor(data), led(data)
    { }
};

#endif /* MODULE14 */
