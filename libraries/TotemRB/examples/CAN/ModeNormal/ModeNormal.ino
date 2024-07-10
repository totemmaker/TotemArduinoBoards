#include <Arduino.h>
/*
  Example of sending and receiving CAN packets.

  NOTE: at least one more device has to be connected to
        CAN bus for "normal" mode to work.

  Documentation: https://docs.totemmaker.net/roboboard/api/can
*/
#if !ROBOBOARD_X4
#pragma GCC error "This example only works with RoboBoard X4"
#endif
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
  if (CAN.readPacketWait(200)) {
    // Get received packet
    auto packet = CAN.getPacket();
    // Print received packet to serial monitor
    Serial.printf("Got packet: %s, ID: %x, len: %d\n", packet.ext?"EXT":"STD", packet.id, packet.len);
  }
  // Send packet after stop waiting with "CAN.readPacketWait"
  static uint8_t data[1] = {0};
  data[0]++;
  // Send standard CAN packet with ID: 0x7F and data with incrementing 8-bit value
  CAN.writePacketStd(0x7F, data, 1);
}
