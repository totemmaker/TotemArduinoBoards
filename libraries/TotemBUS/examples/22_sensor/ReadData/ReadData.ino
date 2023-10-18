#include <Arduino.h>
/*
  Module:  [22] Totem Environment sensor module
  RoboBoard example to read sensor data
*/
// Initialize Environment sensor module
TotemModule22 sensor;
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
}
// Loop program
void loop() {
  Serial.print("LIGHT: ");
  // Print precise color values [0:262143]
  Serial.printf(" Precise R: %5d G: %5d B: %5d | ", 
    sensor.getColorR(),
    sensor.getColorG(),
    sensor.getColorB()
  );
  // Print amount of infrared light and luminosity
  Serial.printf("Infrared %5d Luminosity: %5d\n",
    sensor.getIR(),
    sensor.getLumen()
  );
  // Print temperature and humidity
  Serial.print("HUMID: ");
  Serial.printf("Temp: %.2fC %.2fF Humidity: %3d%% | ", 
    sensor.getTempC(),
    sensor.getTempF(),
    sensor.getHumidity()
  );
  // Print external NTC thermistor temperature (if connected)
  Serial.printf("NTC Temp: %.2fC NTC resistance: %5dR\n",
    sensor.getNtcC(),
    sensor.getNtcResistance()
  );
  // Print atmospheric pressure
  Serial.print("BARO:  ");
  Serial.printf("Pressure: %.3fbar %2fpsi Altitude: %3.0fm\n", 
    sensor.getPressureMbar(),
    sensor.getPressurePsi(),
    sensor.getAltitudeMeter()
  );
  // Delay printing for 1000ms
  delay(1000);
}