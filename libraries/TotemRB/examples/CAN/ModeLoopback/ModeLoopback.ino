#include <Arduino.h>
/*
  Example of using CAN peripheral in Loopback mode.
  This mode is used to testing CAN bus without any devices connected.
  All written packets will be received by "read" functions right away.

  Function sendCAN will send packets each 200ms
  loop will receive these packets

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
// Send CAN packets in 200ms intervals
void sendCAN() {
  static uint8_t data[1] = {0};
  data[0]++;
  // Send standard CAN packet with ID: 0x7F and data with incrementing 8-bit value
  CAN.writePacketStd(0x7F, data, 1);
  delay(200);
}
// Setup program
void setup() {
  // Start serial monitor at baud 115200
  Serial.begin(115200);
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
