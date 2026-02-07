# Architecture — 2A-Lite

## Goals
- Provide a small offline emergency messaging link between two ESP32 nodes without internet or cellular networks.
- Measure latency and reliability under realistic interference.

## Topology
- Peer-to-peer, two nodes: **Sender** and **Receiver**.
- Communication uses **ESP-NOW** (MAC-layer direct frames). No AP or TCP/IP.

## Packet formats
**Emergency packet (Sender → Receiver)**:
```c
typedef struct {
  uint8_t msg_id;
  char payload[32];       // e.g. "HELP"
  uint32_t timestamp_ms;  // millis() at sender
} emergency_packet_t;
