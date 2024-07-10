#include <Arduino.h>
/*
  Example of receiving CAN packet inside loop (polling).

  Documentation: https://docs.totemmaker.net/roboboard/api/can
*/
#if !ROBOBOARD_X4
#pragma GCC error "This example only works with RoboBoard X4"
#endif
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
  // Start CAN peripheral at 500kbps
  CAN.begin(500); // 25, 50, 100, 125, 250, 500, 800, 1000
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
  // Note: you can also use CAN.readPacketWait(200) to wait for 200ms and return false
  // if packet was not received. In that case you use "loop" for other things occasionally.
  // Or register new "loop" with addLoop() function
}
