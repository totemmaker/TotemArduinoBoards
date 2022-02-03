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
int color[3], IR, lumen, humidity, resistance;
float temp[2], ntc, pressure[2], altitude;
// Function to receive Distance module events
void sensorEvent() {
  // Getting parameters inside event won't delay code execution.
  // Data is taken from current received event.
  // Read precise colors and IR + Lumen [0:262143]
       if (sensor.light.isEventRed()) color[0] = sensor.light.getRed();
  else if (sensor.light.isEventGreen()) color[1] = sensor.light.getGreen();
  else if (sensor.light.isEventBlue()) color[2] = sensor.light.getBlue();
  else if (sensor.light.isEventIR()) IR = sensor.light.getIR();
  else if (sensor.light.isEventLumen()) lumen = sensor.light.getLumen();
  // Read temperature
  else if (sensor.temp.isEventTemperature()) {
    temp[0] = sensor.temp.getC();
    temp[1] = sensor.temp.getF();
  }
  // Read humidity
  else if (sensor.temp.isEventHumidity()) humidity = sensor.temp.getHumidity();
  else if (sensor.ntc.isEventTemperature()) ntc = sensor.ntc.getC();
  else if (sensor.ntc.isEventResistance()) resistance = sensor.ntc.getResistance();
  // Read pressure
  else if (sensor.pressure.isEventPressure()) {
    pressure[0] = sensor.pressure.getMbar();
    pressure[1] = sensor.pressure.getPsi();
  }
  else if (sensor.pressure.isEventAltitude()) altitude = sensor.pressure.getAltMeter();
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
  // Print precise color values [0:262143]
  Serial.printf("Color R: %5d G: %5d B: %5d | ", 
    color[0], color[1], color[2]
  );
  // Print amount of infrared light and luminosity [0:262143]
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
  sensor.light.eventOnceRed();
  sensor.light.eventOnceGreen();
  sensor.light.eventOnceBlue();
  sensor.light.eventOnceIR();
  sensor.light.eventOnceLumen();
  sensor.temp.eventOnceTemperature();
  sensor.temp.eventOnceHumidity();
  sensor.ntc.eventOnceTemperature();
  sensor.ntc.eventOnceResistance();
  sensor.pressure.eventOncePressure();
  sensor.pressure.eventOnceAltitude();
  // Delay printing for 1000ms
  delay(1000);
}