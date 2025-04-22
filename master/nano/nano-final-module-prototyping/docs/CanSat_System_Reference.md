# CanSat System Reference (Updated)

## 1. Project Overview
A secondary mission for the Canadian CanSat competition to profile atmospheric pollutants at discrete altitudes and filter zones.  
A 5015 fan draws air through activated‑carbon filter strips; a servo multiplexes airflow across filter sections at varying heights. Onboard sensors log environmental and pollutant data; a GPS module provides geo‑tags. Data batches write to SD (primary backup) and transmit via LoRa to a ground station, using adaptive sampling, a one‑button UI, and fault‑tolerant recovery.

---

## 2. Hardware & Pin Mapping
| Peripheral            | Interface       | Nano Every Pin(s)            |
|-----------------------|-----------------|------------------------------|
| BME680 (SPI mode)     | SPI             | D13 (SCK), D11 (MOSI), D12 (MISO), D8 (CS) |
| SGP30                 | I²C             | A4 (SDA), A5 (SCL)           |
| SD Card               | SPI             | D13 (SCK), D11 (MOSI), D12 (MISO), D10 (CS) |
| RP2040 Link           | Serial1 UART    | D1 (TX1), D0 (RX1)           |
| GPS (NEO‑6M)          | SoftwareSerial  | D4 (RX), D5 (TX)             |
| MQ2, MQ4, MQ9, MQ135  | Analog          | A0, A1, A2, A3               |
| Servo (filter)        | PWM             | D6                           |
| Fan Control           | Digital         | D7 (MOSFET gate)             |
| One‑Button            | Digital In      | D2 (button → GND)            |
| Status LED            | Digital Out     | D3 (via 220 Ω)               |
| Spare I/O             | —               | D8*, D9, A6, A7              |

* D8 repurposed as BME680 CS; Spare I/O now includes D9, A6, A7.

### Per‑Module Wiring
- **BME680** (SPI):
  - VIN→5 V, GND→GND
  - SCK→D13, MOSI→D11, MISO→D12, CS→D8
- **SGP30** (I²C): VCC→3.3 V, GND→GND, SDA→A4, SCL→A5  
- **SD Card** (SPI): VCC→5 V, GND→GND, MOSI→D11, MISO→D12, SCK→D13, CS→D10
- **MQ Sensors**:
  - **MQ2:** VCC→5 V, GND→GND, OUT→A0
  - **MQ4:** VCC→5 V, GND→GND, OUT→A1
  - **MQ9:** VCC→5 V, GND→GND, OUT→A2  *(replaces MQ7; no heater cycling required)*
  - **MQ135:** VCC→5 V, GND→GND, OUT→A3
- **GPS (NEO‑6M)**: VCC→5 V, GND→GND, TX→D4, RX→D5
- **OLED (I²C)**: VCC→3.3 V, GND→GND, SDA→A4, SCL→A5
- **Servo**: VCC→5 V, GND→GND, SIG→D6
- **Fan**: +→5 V, –→MOSFET Drain; MOSFET Gate→D7; Source→GND
- **Button**: D2→button; other side→GND (internal pull‑up)
- **LED**: Anode→D3 via 220 Ω resistor; Cathode→GND
- **Nano↔RP2040 UART**: D1→RP2040 RX1; D0←RP2040 TX1

---

## 3. Software Subsystems
### 3.1 UI & Control
- **One‑Button** (D2):
  - **Long‑press ≥ 3 s** → Calibration + Health‑Check
  - **Short‑press < 1 s** → Toggle Start/Pause/Resume
- **LED** (D3): blink patterns for modes & errors
- **OLED**: prompts, ✓/✗ health icons, live stats

### 3.2 Calibration & Health‑Check
1. **Baro Zero**: avg 10 × BME680 → P₀
2. **GPS Fix**: poll NEO‑6M @1 Hz till ≥ 4 sats or 2 min → record lat/lon/alt
3. **Gas Baseline** (optional): sample MQ2, MQ4, MQ9, MQ135 for clean‑air reference
4. **Health Checks**: SD ping, Serial1 PING, LoRa ping

### 3.3 Sampling & Logging
- **Sensors**:
  - BME680 (SPI) & SGP30 (I²C) @1 Hz
  - MQ2, MQ4, MQ9, MQ135 @ batch interval (every 5 s)
  - GPS @1 Hz for geo‑tags
  - Altitude via barometric formula
- **Batching**: buffer 5 samples → one packet

### 3.4 Storage Manager
- **Primary**: write batch to SD every 5 s
- **Failover**: on SD error → disable SD writes; direct‑uplink only

### 3.5 Comm Manager (Serial1)
- Frame & send batches → await ACK/NACK → retry or buffer

### 3.6 RP2040 LoRa Manager
- **Time‑Sync**: downlink epoch every 10 s → Nano re‑anchors clock
- **Uplink**: transmit data + LOCATION every 30 s @ 917 MHz, 125 kHz BW, SF12
- **Recovery**: continuous retry of all queued batches

### 3.7 Adaptive Sampling
- RAM < 75% → 1 Hz
- RAM ≥ 75% → 0.5 Hz
- RAM ≥ 90% → 0.2 Hz
- RAM full → drop oldest, enqueue newest

### 3.8 Error Logger
- Log errors to **ERROR_LOG.txt** on SD
- OLED/LED alert
- SYSERR packets uplinked or queued

---

## 4. Data & Control Flow
1. **Power‑Up** → BOOT splash
2. **Calibration** (long‑press): baro zero, GPS fix, baseline, health‑checks
3. **Ready** → short‑press to start logging
4. **Logging**:
   - Sensors → batch → SD & Serial1 → RP2040 → LoRa → ground
   - Fan ON; servo steps zones; periodic LOCATION uplinks
5. **Pause/Resume** (short‑press)
6. **Shutdown** via master switch

---

## 5. Error & Recovery Highlights
| Failure     | Detect               | Action & Recovery                                |
|-------------|----------------------|--------------------------------------------------|
| SD fail     | write error          | direct‑uplink; retry SD                          |
| LoRa down   | no ground ACK        | buffer all; retry; throttle if RAM               |
| RAM full    | buffer = 100%       | drop oldest; log “RAM_DROP”                      |
| Sync miss   | no epoch in 15 s     | log “SYNC_MISS”; continue relative time          |
| GPS fail    | no 4‑sat fix in 2 min| warn “GPS_FAIL”; user override                   |
| Comm NACK   | Serial1 NACK         | retry R times; then buffer                       |
| Sensor err  | I²C/ADC fail         | discard; log “SENSOR_ERR”                        |
| Any error   | code generated       | log→SD; OLED/LED; SYSERR uplink                  |

---

## 6. Timing & Throughput
- **Sampling:** 1 Hz (adaptive down to 0.2 Hz)
- **Batch size:** 5 samples (~5 s)
- **LoRa airtime:** ~0.4 s/batch (~8% duty)
- **Time‑sync interval:** 10 s
- **Location uplink:** 30 s

---

## 7. Spare I/O
- **Free pins:** D9, A6, A7

