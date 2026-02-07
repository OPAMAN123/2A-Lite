#include <WiFi.h>
#include <esp_now.h>

typedef struct {
  uint8_t msg_id;
  char payload[32];
  uint32_t timestamp_ms;
} emergency_packet_t;

typedef struct {
  uint8_t msg_id;
  uint32_t ack_timestamp_ms;
} ack_packet_t;

// Sender MAC: D4:E9:F4:B4:FF:F4
uint8_t senderMAC[] = {0xD4, 0xE9, 0xF4, 0xB4, 0xFF, 0xF4};

void onReceive(const esp_now_recv_info_t *info,
               const uint8_t *incomingData,
               int len) {

  emergency_packet_t rxPacket;
  memcpy(&rxPacket, incomingData, sizeof(rxPacket));

  uint32_t now = millis();

  Serial.println("=== EMERGENCY PACKET RECEIVED ===");
  Serial.print("From MAC: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", info->src_addr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();

  Serial.print("Message ID: ");
  Serial.println(rxPacket.msg_id);

  Serial.print("Payload: ");
  Serial.println(rxPacket.payload);

  Serial.print("One-way latency (ms): ");
  Serial.println(now - rxPacket.timestamp_ms);

  Serial.println("================================");

  // Send ACK
  ack_packet_t ack;
  ack.msg_id = rxPacket.msg_id;
  ack.ack_timestamp_ms = now;

  esp_now_send(senderMAC, (uint8_t *)&ack, sizeof(ack));
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(1000);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, senderMAC, 6);
  peer.channel = 0;
  peer.encrypt = false;
  esp_now_add_peer(&peer);

  esp_now_register_recv_cb(onReceive);
  Serial.println("ESP-NOW Receiver Ready");
}

void loop() {}
