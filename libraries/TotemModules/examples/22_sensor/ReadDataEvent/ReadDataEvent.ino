#include <Arduino.h>
/*
  Module:  [22] Totem Environment sensor module
  Details: Example showing how to read sensor data without blocking code execution
  
  Note: Reading values without event (sensor.temp.getC()) delays code for
  ~1ms. Function will send request to module and awaits for response.
  Same as I2C based communication.
  This example toggles events on / off and measures time required to call function.
  When events are enabled - module starts to broadcast value changes, which are stored in
  internal buffer. Latest stored value is returned on function call.
*/
// Initialize Environment sensor module
Module22 sensor;
// Define variables required for this example
bool eventsStarted; // State if events are enabled
int eventsCount; // Amount of times event was called
// Function to receive Environment module events
void sensorEvent() {
  // Check if received "light" event
  if (sensor.light.isEvent()) {
    // Turn on LED if it's too dark
    if (sensor.light.getLumen() < 2000)
      sensor.led.on();
    else
      sensor.led.off();
  }
  // Increment events counter
  eventsCount++;
}
// Parallel loop to toggle events
void loopToggleEvents() {
  // Start sending events from module
  sensor.light.eventStart();
  sensor.temp.eventStart();
  eventsStarted = true;
  delay(3000); // Wait 3 seconds
  // Stop sending events from module
  sensor.light.eventStop();
  sensor.temp.eventStop();
  eventsStarted = false;
  eventsCount = 0; // Reset counter
  delay(3000); // Wait 3 seconds
}
// Initialize program
void setup() {
  // Start Serial Monitor communication at 9600 speed
  Serial.begin(9600);
  // Register event function for led toggling
  // Optional. In case required to know when value is updated
  sensor.addEvent(sensorEvent);
  // Create parallel loop to toggle events
  addLoop(loopToggleEvents);
}
// Loop program
void loop() {
  // Measure time (microseconds) it takes to receive value from module
  int start, end, total;
  start = micros(); // Save time before call
  int luminosity = sensor.light.getLumen();
  float temperature = sensor.temp.getC();
  int humidity = sensor.temp.getHumidity();
  end = micros(); // Save time after call
  // Total time taken to read value from module
  total = end-start;
  // Print information
  Serial.printf("Lumen: %5d, Temp: %.2fC, Humidity: %3d%%. Events: %s %d. Time: %dus.\n",
    luminosity, temperature, humidity,
    eventsStarted ? "on" : "off", eventsCount, total
  );
  // Delay printing
  delay(70);
}