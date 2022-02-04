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
class Line : public Feature::MultiEventHidden {
    const uint32_t cmdList[2] = {
        Feature::CMD("line/pos"), Feature::CMD("line/color")
    };
public:
    Line(TotemModuleData &d) : Feature::MultiEventHidden(d, cmdList) { }
    // Get line position [-35:35]
    int getPosition() {
        return this->getCmd(0)->getInt();
    }
    // Get color of detected line ['W','B',0]
    char getColor() {
        return this->getCmd(1)->getInt();
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
    // Event Position
    bool isEventPosition() { return this->isEvent(0); }
    void eventPosition() { this->event(0); }
    void eventPosition(uint32_t intervalMs) { this->event(0, intervalMs); }
    void eventOncePosition() { this->eventOnce(0); }
    // Event Color (junction)
    bool isEventColor() { return this->isEvent(1); }
    void eventColor() { this->event(1); }
    void eventColor(uint32_t intervalMs) { this->event(1, intervalMs); }
    void eventOnceColor() { this->eventOnce(1); }
};
class Sensor : public Feature::MultiEventHidden {
    const uint32_t cmdList[2] = {
        Feature::CMD("sensor/range"), Feature::CMD("sensor/raw")
    };
public:
    Sensor(TotemModuleData &d) : Feature::MultiEventHidden(d, cmdList) { }
    // Get accuracy of line detection [0:100]%. Higher is better
    int getAccuracy() {
        return this->getCmd(0)->getInt();
    }
    // Get raw sensor contrast readings [0:100]%
    void getRaw(uint8_t raw[8]) {
        uint8_t *ptr;
        if (!(this->getCmd(1)->getData(ptr)))
            return;
        for (int i=0; i<8; i++) 
            raw[i] = ptr[i];
    }
    // Set minimum required accuracy to start line following [0:100]%
    void setThreshold(uint8_t contrast) {
        this->writeCustomCmd(Feature::CMD("sensor/threshold"), contrast);
    }
    // Event Accuracy
    bool isEventAccuracy() { return this->isEvent(0); }
    void eventAccuracy() { this->event(0); }
    void eventAccuracy(uint32_t intervalMs) { this->event(0, intervalMs); }
    void eventOnceAccuracy() { this->eventOnce(0); }
    // Event Raw
    bool isEventRaw() { return this->isEvent(1); }
    void eventRaw() { this->event(1); }
    void eventRaw(uint32_t intervalMs) { this->event(1, intervalMs); }
    void eventOnceRaw() { this->eventOnce(1); }
};
template <int LED_CNT>
class Led : public Feature::Simple {
    uint8_t ledState = 0;
    const uint32_t cmdList[1] = {
        Feature::CMD("led")
    };
public:
    Led(TotemModuleData &d) : Feature::Simple(d, cmdList) { }
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
        this->writeChannel(0, ledState); 
    }
    // Read LED state [HIGH:LOW] (on / off)
    bool isOn(uint8_t ch) {
        if (ch >= LED_CNT) return false;
        return ledState & (1 << ch);
    }
    
    // Reset LED to default operation (display line position)
    void reset() {
        ledState = 0;
        this->writeChannel(0, -1);
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
        this->writeChannel(0, reverse);
    }
};
}

class Module14 : public TotemEventModule {
public:
    Features14::Line line;
    Features14::Sensor sensor;
    Features14::Led<8> led;

    Module14(uint16_t serial = 0) : TotemEventModule(14, serial),
    line(data), sensor(data), led(data)
    { }
};

#endif /* MODULE14 */
