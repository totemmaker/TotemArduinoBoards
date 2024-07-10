#include <Arduino.h>
/*
  Example to demonstrate usage of hardware CAN filter.
  Function sendCAN will send packets each 200ms
  loop will receive these packets

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
// Send CAN packets in 200ms intervals
void sendCAN() {
  static uint8_t data[1] = {0};
  data[0]++;
  // Send standard CAN packet with ID: 0x7F and data with incrementing 8-bit value
  CAN.writePacketStd(0x100 + 0xA0, data, sizeof(data));
  CAN.writePacketStd(0x100 + 0xA1, data, sizeof(data));
  CAN.writePacketStd(0x100 + 0xA2, data, sizeof(data));
  CAN.writePacketExt(0x123400 + 0xA3, data, sizeof(data));
  delay(200);
}
// Setup program
void setup() {
  // Start serial monitor at baud 115200
  Serial.begin(115200);
  // Set hardware filter to receive only:
  // - Standard message with IDs: 0A1,1A1,2A1,3A1,4A1,5A1,6A1,7A1
  // - Standard message with IDs: 0A2,1A2,2A2,3A2,4A2,5A2,6A2,7A2
  // - Extended message 0x1234A3 will be ignored
  // - Message 0x1A0 will be ignored
  // Note: must be called before CAN.begin !
  CAN.setHardwareFilterDual(0xA1, 0xFF, 0xA2, 0xFF);
  // Start CAN peripheral at 500kbps in Loopback mode
  // Used for self-test and examples. All written packets will be received right away.
  CAN.beginLoopback(500); // 25, 50, 100, 125, 250, 500, 800, 1000
  // Add second "loop" function to send CAN packets
  addLoop(sendCAN);
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
