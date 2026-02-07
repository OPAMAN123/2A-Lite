# 2A-Lite — Offline Emergency P2P Communication (ESP-NOW)

**Short description:**  
2A-Lite is a minimal, low-cost offline emergency communication prototype using ESP32 (ESP-NOW). It supports one-way emergency messages with acknowledgements, measures round-trip latency (RTT) and packet success rate vs distance, and is intended as a reproducible undergraduate research project.

## Repository layout
- `firmware/` — Arduino sketches for sender and receiver.
- `docs/architecture.md` — system architecture and packet formats.
- `docs/testing.md` — experimental methodology and test checklist.
- `docs/results.md` — measured and modelled results (tables + interpretation).
- `figures/` — graphs (RTT vs distance, Success rate vs distance).

## Quick start (for reviewers)
1. Flash `firmware/receiver/receiver.ino` to one ESP32 and power it (power bank or charger).  
2. Flash `firmware/sender/sender.ino` to the other ESP32. Edit `receiverMAC`/`senderMAC` in code if needed.  
3. Open Serial Monitor on the sender (`115200`) to collect CSV logs in the format: `msg_id,rtt_ms,sentCount`.

## Key results (summary)
| Distance (m) | Avg RTT (ms) | Max RTT (ms) | Success Rate (%) | Data Type |
|-------------:|-------------:|-------------:|------------------:|:---------:|
| 1  | 15.2 | 35 | 99.0 | Measured |
| 5  | 19.1 | 33 | 65.8 | Measured |
| 10 | 28.4 | 46 | 45.0 | Modelled |
| 20 | 38.7 | 61 | 20.0 | Modelled |

(Full details in `docs/results.md`.)

## Limitations & future work
- Results are for indoor, high-interference conditions (many Wi-Fi APs & hotspots).
- Future work: multi-hop relaying, mesh using ESP-NOW, power consumption profiling, button/LED UI, and encryption for authentication.


## Run the Project

1. Open `firmware/receiver/receiver.ino` and flash to ESP32
2. Power receiver (power bank or laptop)
3. Open `firmware/sender/sender.ino`, set MACs, and flash
4. Open Serial Monitor at 115200 to view results


## License
This project is published under the MIT License. See `LICENSE`.
