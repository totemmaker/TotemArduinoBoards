#include <Arduino.h>
/*
  Module:  [22] Totem Environment sensor module
  Details: Example showing how to read sensor data without blocking code execution
  
  Note: Reading values directly (sensor.temp.getC()) delays code for
  ~700 microseconds (less than 1ms). Function will send request to module and
  and awaits for response. Same as I2C based communication.
  This example shows how to use event functions to avoid blocking code.
*/
// Initialize Environment sensor module
Module22 sensor;
// Define variables required for this example
int color[3], colorP[3], IR, lumen, humidity, resistance;
float temp[2], ntc, pressure[2], altitude;
// Function to receive Distance module events
void sensorEvent() {
  // Getting parameters inside event won't delay code execution.
  // Data is taken from current received event.
  // Check if received event is for "color" parameter
  if (sensor.color.isEvent()) {
    // Store color value to variables
    color[0] = sensor.color.getR();
    color[1] = sensor.color.getG();
    color[2] = sensor.color.getB();
  }
  // Read precise colors [0:262143]
  else if (sensor.colorR.isEvent()) colorP[0] = sensor.colorR.get();
  else if (sensor.colorG.isEvent()) colorP[1] = sensor.colorG.get();
  else if (sensor.colorB.isEvent()) colorP[2] = sensor.colorB.get();
  // Read light
  else if (sensor.IR.isEvent()) IR = sensor.IR.get();
  else if (sensor.lumen.isEvent()) lumen = sensor.lumen.get();
  // Read temperature
  else if (sensor.temp.isEvent()) {
    temp[0] = sensor.temp.getC();
    temp[1] = sensor.temp.getF();
  }
  // Read humidity
  else if (sensor.humidity.isEvent()) humidity = sensor.humidity.get();
  else if (sensor.ntc.isEvent()) {
    ntc = sensor.ntc.getC();
    resistance = sensor.ntc.getResistance();
  }
  // Read pressure
  else if (sensor.pressure.isEvent()) {
    pressure[0] = sensor.pressure.getMbar();
    pressure[1] = sensor.pressure.getPsi();
  }
  else if (sensor.altitude.isEvent()) altitude = sensor.altitude.getMeter();
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Register event function for Environment sensor module
  sensor.addEvent(sensorEvent);
}
// Loop program
void loop() {
  Serial.print("LIGHT: ");
  // Print RGB color [0-255]
  Serial.printf("Color: R:%3d G:%3d B:%3d",
    color[0], color[1], color[2]
  );
  // Print precise color values [0:262143]
  Serial.printf(" Precise R: %5d G: %5d B: %5d | ", 
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
  // Call single parameter read and return it inside event function
  // Won't delay code execution. Updated values will be ready for next print
  sensor.color.eventOnce();
  sensor.colorR.eventOnce();
  sensor.colorG.eventOnce();
  sensor.colorB.eventOnce();
  sensor.IR.eventOnce();
  sensor.lumen.eventOnce();
  sensor.temp.eventOnce();
  sensor.humidity.eventOnce();
  sensor.ntc.eventOnce();
  sensor.pressure.eventOnce();
  sensor.altitude.eventOnce();
  // Delay printing for 1000ms
  delay(1000);
}