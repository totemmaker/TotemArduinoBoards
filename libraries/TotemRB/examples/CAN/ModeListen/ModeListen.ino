#include <Arduino.h>
/*
  Example of using CAN peripheral in Listen mode.
  This mode only listens CAN bus without interacting with it (can't write).
  Used in cases to make sure RoboBoard X4 won't intervene with
  ongoing CAN bus traffic. Typically used in monitor applications.

  NOTE: For listen mode to work - there must be at least 2 devices on CAN bus.

  Documentation: https://docs.totemmaker.net/roboboard/api/can
  
  Only works with RoboBoard X4!
*/
// Function that prints CAN packet to serial monitor
void printPacket(CANPacket &packet) {
  Serial.print("Got "); // Print type (EXT or STD)
  Serial.print(packet.ext ? "EXT" : "STD");
  Serial.print(", ID: "); // Print ID
  Serial.print(packet.id, HEX);
  Serial.print(", Len: "); // Print data length
  Serial.print(packet.len);
  if (packet.rtr) { // Print packet type: Remote-Transmission request
    Serial.print(", RTR packet");
  }
  else { // Print "data" contents
    Serial.print(", Data:");
    for (int i=0; i<packet.len; i++) {
      Serial.printf(" %02x", packet.data[i]);
    }
  }
  Serial.println(); // New line
}
// Setup program
void setup() {
  // Start serial monitor at baud 115200
  Serial.begin(115200);
  // Start CAN peripheral at 500kbps in Listen mode
  // "Listen" mode only monitors CAN bus line (can't write, read-only)
  CAN.beginListen(500); // 25, 50, 100, 125, 250, 500, 800, 1000
}
// Loop program
void loop() {
  // Wait for CAN packet receive
  if (CAN.readPacketWait()) {
    // Get received packet
    auto packet = CAN.getPacket();
    // Print received packet to serial monitor
    printPacket(packet);
  }
}
