#include <WiFi.h>
#include <esp_now.h>

/* ===================== CONFIG ===================== */

// Receiver MAC: B0:CB:D8:9D:33:14
uint8_t receiverMAC[] = {0xB0, 0xCB, 0xD8, 0x9D, 0x33, 0x14};

// Report statistics every N packets
const uint32_t REPORT_INTERVAL = 20;

// Send interval (ms)
const uint32_t SEND_INTERVAL_MS = 2000;

/* ===================== DATA STRUCTS ===================== */

typedef struct {
  uint8_t msg_id;
  char payload[32];
  uint32_t timestamp_ms;
} emergency_packet_t;

typedef struct {
  uint8_t msg_id;
  uint32_t ack_timestamp_ms;
} ack_packet_t;

/* ===================== GLOBAL STATE ===================== */

uint8_t  msgCounter = 0;
uint32_t sendTimes[256];

uint32_t sentCount = 0;
uint32_t ackCount  = 0;

unsigned long lastSendMs = 0;

/* ===================== CALLBACKS ===================== */

// SEND CALLBACK (NEW ESP32 CORE API)
void onSend(const wifi_tx_info_t *tx_info,
            esp_now_send_status_t status) {
  // Intentionally minimal to avoid serial spam
  (void)tx_info;
  (void)status;
}

// RECEIVE CALLBACK (ACKs)
void onReceive(const esp_now_recv_info_t *info,
               const uint8_t *incomingData,
               int len) {

  (void)info;
  (void)len;

  ack_packet_t ack;
  memcpy(&ack, incomingData, sizeof(ack));

  uint32_t rtt = millis() - sendTimes[ack.msg_id];
  ackCount++;

  Serial.print("ACK ");
  Serial.print(ack.msg_id);
  Serial.print(" | RTT(ms): ");
  Serial.println(rtt);
}

/* ===================== SETUP ===================== */

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  delay(1000);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_send_cb(onSend);
  esp_now_register_recv_cb(onReceive);

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, receiverMAC, 6);
  peer.channel = 0;
  peer.encrypt = false;

  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("ESP-NOW Sender Ready");
}

/* ===================== LOOP ===================== */

void loop() {

  // Rate-limit transmissions
  if (millis() - lastSendMs < SEND_INTERVAL_MS) {
    return;
  }
  lastSendMs = millis();

  // Build packet
  emergency_packet_t packet;
  packet.msg_id = msgCounter;
  strcpy(packet.payload, "HELP");
  packet.timestamp_ms = millis();

  sendTimes[msgCounter] = packet.timestamp_ms;

  // Send
  esp_now_send(receiverMAC, (uint8_t *)&packet, sizeof(packet));
  sentCount++;
  msgCounter++;

  // Periodic statistics (CLEAN & RELIABLE)
  if (sentCount % REPORT_INTERVAL == 0) {
    Serial.println("----- STATS -----");
    Serial.print("Sent: ");
    Serial.println(sentCount);
    Serial.print("ACKs: ");
    Serial.println(ackCount);
    Serial.print("Success rate (%): ");
    Serial.println((ackCount * 100.0) / sentCount);
    Serial.println("-----------------");
  }
}
