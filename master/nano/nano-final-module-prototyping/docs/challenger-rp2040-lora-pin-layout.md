# Challenger RP2040 LoRa Pinout

## Power & Control Pins
- **RESET** (external reset)  
- **+3.3 V** (3.3 V regulator output)  
- **ARef** (analog reference)  
- **GND** (ground) × 2  
- **BAT** (battery input)  
- **EN** (enable)  
- **USB / 5 V** (USB 5 V supply)  

---

## Arduino‑Style Pins & RP2040 Mappings

| Arduino Label | RP2040 GPIO | Alt UART Pin | Alt I2C Pin | Notes           |
|:-------------:|:-----------:|:------------:|:-----------:|:---------------:|
| A0            | ADC0        | CTS1         | SDA1        | analog input    |
| A1            | ADC1        | RTS1         | SCL1        | analog input    |
| A2            | ADC2        | TX0          | SDA0        | analog input    |
| A3            | ADC3        | RX0          | SCL0        | analog input    |
| A4*           | IO19        | RTS0         | SCL1        | digital‑only    |
| A5*           | IO21        | CTS1         | SCL0        | digital‑only    |
| SCK           | IO22        | SCK          | SDA1        | SPI clock       |
| SDO           | IO23        | RTS1         | SCL1        | SPI MISO        |
| SDI           | IO20        | TX1          | SDA0        | SPI MOSI        |
| RX            | IO17        | RX1          | SCL0        | UART RX         |
| TX            | IO16        | TX0          | SDA0        | UART TX         |
| IO8 (D13)     | IO8         | TX1          | SDA0        | Arduino D13     |
| IO7 (D12)     | IO7         | RTS1         | SCL1        | Arduino D12     |
| IO6 (D11)     | IO6         | CTS1         | SDA1        | Arduino D11     |
| IO5 (D10)     | IO5         | RX1          | SCL0        | Arduino D10     |
| IO4 (D9)      | IO4         | TX1          | SDA0        | Arduino D9      |
| IO3 (D6)      | IO3         | RTS0         | SCL1        | Arduino D6      |
| IO2 (D5)      | IO2         | CTS0         | SDA1        | Arduino D5      |
| IO1 (SCL)     | IO1         | RX0          | SCL0        | Arduino SCL     |
| IO0 (SDA)     | IO0         | TX0          | SDA0        | Arduino SDA     |

\* **Digital‑only**, no ADC capability on this board.

---

> **Note:** There’s also a U.FL 50 Ω connector for an external LoRa antenna.
