# Arduino Nano Every Pinout

## Power & Reference
- **+3.3 V** (regulator output)  
- **+5 V** (regulator output)  
- **VIN** (raw input voltage)  
- **GND** (ground) × 2 pins  
- **AREF** (analog reference)  
- **RESET** × 2 (reset MCU)  

## On‑Board LED
- **LED_BUILTIN** – D13 (PE2 / SCK)  

## Digital I/O
- **D0 (RX)** – PC5  
- **D1 (TX)** – PC4  
- **D2** – PA0  
- **D3 (~PWM)** – PF5  
- **D4** – PC6  
- **D5 (~PWM)** – PB2  
- **D6 (~PWM)** – PF4  
- **D7** – PA1  
- **D8** – PE3  
- **D9 (~PWM)** – PB0  
- **D10** – PB1  
- **D11 (MOSI, SPI SC1)** – PE0  
- **D12 (MISO, SPI SC1)** – PE1  
- **D13 (SCK, SPI SC1)** – PE2  

## Analog Inputs

| Arduino | Alt‑D# | MCU Port | Analog Channel |
|:-------:|:------:|:--------:|:--------------:|
| A0      | D14    | PD3      | AIN[3]         |
| A1      | D15    | PD2      | AIN[2]         |
| A2      | D16    | PD1      | AIN[1]         |
| A3      | D17    | PD0      | AIN[0]         |
| A4      | D18    | PA2      | SDA (I²C Data) |
| A5      | D19    | PA3      | SCL (I²C Clock)|
| A6      | D20    | PD4      | AIN[4]         |
| A7      | D21    | PD5      | AIN[5]         |

## Serial, SPI & I²C Breakdown
- **Serial 0**  
  - RX – D0 (PC5)  
  - TX – D1 (PC4)  

- **SPI (SC1)**  
  - MOSI – D11 (PE0)  
  - MISO – D12 (PE1)  
  - SCK  – D13 (PE2)  

- **I²C**  
  - SDA – A4 (PA2)  
  - SCL – A5 (PA3)  
