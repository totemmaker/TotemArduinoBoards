#ifndef TOTEM_INCLUDE_BATTERY
#define TOTEM_INCLUDE_BATTERY

namespace _Totem {

class BatteryClass {
public:
    /// @brief Read battery State Of Charge (%)
    /// @return [0:100]% charge state
    int getSOC();
    /// @brief Read battery voltage (V)
    /// @return [2.8:4.2]V - X3. [8.40:12.60]V - X4
    float getVoltage();
    /// @brief Read battery current (A)
    /// @return [-2.0:2.0]A. negative - discharging
    float getCurrent();
    /// @brief Is battery charging
    /// @return [true:false] is charging
    bool isCharging();
};

} // namespace _Totem

namespace totem {

extern _Totem::BatteryClass Battery;

} // namespace totem

#endif /* TOTEM_INCLUDE_BATTERY */
