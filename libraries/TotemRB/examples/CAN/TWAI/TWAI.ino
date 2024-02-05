#include <Arduino.h>
/*
  Example of using RoboBoard X4 with low-level TWAI (CAN) driver.
  Documentation:
  TWAI: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/twai.html
  Totem: https://docs.totemmaker.net/roboboard/api/can

  Only works with RoboBoard X4!
*/
// Include TWAI driver
#include <driver/twai.h>
// Select mode
#define CAN_MODE_NORMAL
// #define CAN_MODE_LISTEN
// #define CAN_MODE_LOOPBACK

void write_loop();
// Setup program
void setup() {
  // Start serial monitor at baud 115200
  Serial.begin(115200);
  // Start CAN peripheral on TX pin 14 and RX pin 34
#ifdef CAN_MODE_LOOPBACK
  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_17, GPIO_NUM_34, TWAI_MODE_NO_ACK);
#elif defined(CAN_MODE_LISTEN) 
  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_17, GPIO_NUM_34, TWAI_MODE_LISTEN_ONLY);
#else 
  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_17, GPIO_NUM_34, TWAI_MODE_NORMAL);
#endif
  // Change TX and RX queue size (if required)
  // g_config.tx_queue_len = 5;
  // g_config.rx_queue_len = 5;
  // Select baud rate config to 500kBits
  twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
  // Set acceptance filter to allow all packets
  twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
  esp_err_t err;
  // Initialize TWAI driver
  err = twai_driver_install(&g_config, &t_config, &f_config);
  // Print error (if not OK)
  while (err != ESP_OK) {
    Serial.printf("\ntwai_driver_install() error: 0x%X (%s)", err, esp_err_to_name(err));
    delay(1000);
  }
  // Enable CAN transceiver chip on pin 5
  digitalWrite(5, LOW); // LOW - enable, HIGH - disable
  // Start twai driver
  err = twai_start();
  // Print error (if not OK)
  while (err != ESP_OK) {
    Serial.printf("\ntwai_start() error: 0x%X (%s)", err, esp_err_to_name(err));
    delay(1000);
  }
#ifndef CAN_MODE_LISTEN
  // Start write loop function to send CAN packets
  addLoop(write_loop);
#endif
}
// Loop program
void write_loop() {
  static int counter = 0;
  uint8_t data[] = {1,2,3,4,5,6,7,8};
  // Prepare TX message
  twai_message_t tx_message = {0};
#ifdef CAN_MODE_LOOPBACK
  tx_message.self = 1; // Special flag for "loopback" mode
#endif
  tx_message.extd = 0; // 0 - Standard packet, 1 - Extended packet
  tx_message.rtr = 0; // 0 - Data packet, 1 - RTR packet
  tx_message.identifier = 0x100 + counter++; // Set identifier with incrementing value
  tx_message.data_length_code = 8; // Send 8 bytes of "data"
  memcpy(tx_message.data, data, 8); // Copy "data" to message
  // Transmit message to CAN bus
  esp_err_t err = twai_transmit(&tx_message, pdMS_TO_TICKS(100));
  // Print error (if not OK)
  while (err != ESP_OK) {
    Serial.printf("\ntwai_transmit() error: 0x%X (%s)", err, esp_err_to_name(err));
    delay(1000);
  }
  // Wait 300 ms until next transmission
  delay(300);
}
// Loop program
void loop() {
  twai_message_t rx_message;
  // Wait indefinitely until any CAN packet is received
  esp_err_t err = twai_receive(&rx_message, portMAX_DELAY);
  // Print received packet
  if (err == ESP_OK) {
    // Print packet information
    Serial.printf("\nGot: %s, ID: %X, len: %d ",
        rx_message.extd?"EXT":"STD",
        rx_message.identifier,
        rx_message.data_length_code);
    // Print packet data (if available)
    if (rx_message.data_length_code && !rx_message.rtr) {
      for (int i=0; i<rx_message.data_length_code; i++)
        Serial.printf(" %02X", rx_message.data[i]);
    }
  }
  // Else - print error (if not OK)
  else {
    Serial.printf("\ntwai_receive() error: 0x%X (%s)", err, esp_err_to_name(err));
    delay(1000);
  }
}
