#include <Arduino.h>
#include <TotemModule22.h>
/*
  Module:  [22] Totem Environment sensor module
  RoboBoard example to receive sensor data updates inside event function.
*/
// Initialize Environment sensor module
TotemModule22 sensor;
// Define variables required for this example
int colorP[3], IR, lumen, humidity, resistance;
float temp[2], ntc, pressure[2], altitude;
// Function to receive Distance module events
void sensorEvent(int evt) {
  // Read precise colors [0:262143]
  if (evt == TotemModule22::evtColor) {
    colorP[0] = sensor.getColorR();
    colorP[1] = sensor.getColorG();
    colorP[2] = sensor.getColorB();
  }
  // Read light
  else if (evt == TotemModule22::evtIR) IR = sensor.getIR();
  else if (evt == TotemModule22::evtLumen) lumen = sensor.getLumen();
  // Read temperature
  else if (evt == TotemModule22::evtTemp) {
    temp[0] = sensor.getTempC();
    temp[1] = sensor.getTempF();
  }
  // Read humidity
  else if (evt == TotemModule22::evtHumidity) humidity = sensor.getHumidity();
  else if (evt == TotemModule22::evtNtc) {
    ntc = sensor.getNtcC();
    resistance = sensor.getNtcResistance();
  }
  // Read pressure
  else if (evt == TotemModule22::evtPressure) {
    pressure[0] = sensor.getPressureMbar();
    pressure[1] = sensor.getPressurePsi();
  }
  else if (evt == TotemModule22::evtAltitude) altitude = sensor.getAltitudeMeter();
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 115200 speed
  Serial.begin(115200);
  // Register event function for Environment sensor module
  sensor.addEvent(sensorEvent);
  // Call values for start broadcasting (required for events to works)
  sensor.getColorR();
  sensor.getColorG();
  sensor.getColorB();
  sensor.getIR();
  sensor.getLumen();
  sensor.getTempC();
  sensor.getHumidity();
  sensor.getNtcC();
  sensor.getPressureMbar();
  sensor.getAltitudeMeter();
}
// Loop program
void loop() {
  Serial.print("LIGHT: ");
  // Print precise color values [0:262143]
  Serial.printf("Precise R: %5d G: %5d B: %5d | ", 
    colorP[0], colorP[1], colorP[2]
  );
  // Print amount of infrared light and luminosity
  Serial.printf("Infrared %5d Luminosity: %5d\n",
    IR, lumen
  );
  // Print temperature and humidity
  Serial.print("HUMID: ");
  Serial.printf("Temp: %.2fC %.2fF Humidity: %3d%% | ", 
    temp[0], temp[1], humidity
  );
  // Print external NTC thermistor temperature (if connected)
  Serial.printf("NTC Temp: %.2fC NTC resistance: %5dR\n",
    ntc, resistance
  );
  // Print atmospheric pressure
  Serial.print("BARO:  ");
  Serial.printf("Pressure: %.3fbar %2fpsi Altitude: %3.0fm\n", 
    pressure[0], pressure[1], altitude
  );
  // Delay printing for 1000ms
  delay(1000);
}