# Results — 2A-Lite

## Environment
Indoor testing under heavy RF interference (≈9–10 Wi-Fi APs detected; phone hotspot and laptop Wi-Fi active).

## Measured data summaries

| Distance (m) | Packets sent | Packets received | Success Rate (%) | Avg RTT (ms) | Max RTT (ms) |
|-------------:|-------------:|-----------------:|------------------:|-------------:|-------------:|
| 1  | 100 | 99  | 99.0  | 15.2 | 35 |
| 5  | 120 | 79  | 65.8  | 19.1 | 33 |

## Modelled (extrapolated) data
| Distance (m) | Packets sent | Packets received | Success Rate (%) | Avg RTT (ms) | Max RTT (ms) |
|-------------:|-------------:|-----------------:|------------------:|-------------:|-------------:|
| 10 | 100 | 45  | 45.0  | 28.4 | 46 |
| 20 | 100 | 20  | 20.0  | 38.7 | 61 |

## Graphs
- `figures/rtt_vs_distance.png` — Average RTT vs Distance  
- `figures/success_vs_distance.png` — Success Rate vs Distance

## Interpretation
Experimental results show near-perfect reliability (≈99%) and low RTT (~15 ms) at 1 m under heavy interference. At 5 m, success rate drops to ~66% and RTT increases modestly. Extrapolation suggests rapid degradation beyond 10 m in dense RF environments, implying practical systems would require relays or mesh for larger coverage.

Figure 1 — Average Round-Trip Latency vs Distance (ms)
Average round-trip latency measured under heavy Wi-Fi interference.  

![Average RTT vs Distance](../figures/rtt_vs_distance.png)


Figure 2 — Packet Success Rate vs Distance (%)
Packet success rate under heavy Wi-Fi interference.  
Modelled points indicate expected degradation beyond measured range.

![Success Rate vs Distance](../figures/success_vs_distance.png)
