#include <Arduino.h>
/*
  Module:  [22] Totem Environment sensor module
  Details: Example showing how to read sensor data
  
  Note: Reading values directly (sensor.distance.getMM()) delays code for
  ~1ms. Function will send request to module and and awaits for response.
  Same as I2C based communication.
  If you want non-blocking code, check "Event" based example.
*/
// Initialize Environment sensor module
Module22 sensor;
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
}
// Loop program
void loop() {
  Serial.print("LIGHT: ");
  // Print precise color values and amount of infrared light and luminosity [0:262143]
  Serial.printf(" Color R: %5d G: %5d B: %5d | IR: %5d Lumen: %5d\n", 
    sensor.color.getRed(),
    sensor.color.getGreen(),
    sensor.color.getBlue(),
    sensor.light.getIR(),
    sensor.light.getLumen()
  );
  // Print temperature and humidity
  Serial.print("HUMID: ");
  Serial.printf("Temp: %.2fC %.2fF Humidity: %3d%% | ", 
    sensor.temp.getC(),
    sensor.temp.getF(),
    sensor.temp.getHumidity()
  );
  // Print external NTC thermistor temperature (if connected)
  Serial.printf("NTC Temp: %.2fC NTC resistance: %5dR\n",
    sensor.ntc.getC(),
    sensor.ntc.getResistance()
  );
  // Print atmospheric pressure
  Serial.print("BARO:  ");
  Serial.printf("Pressure: %.3fbar %2fpsi Altitude: %3.0fm\n", 
    sensor.pressure.getMbar(),
    sensor.pressure.getPsi(),
    sensor.altitude.getMeter()
  );
  // Delay printing for 1000ms
  delay(1000);
}