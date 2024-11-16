# Battery-Powered Voltage Meter

A simple battery-powered voltage meter built using an STC microcontroller. This project measures voltage levels using the ADC, displays the levels via LEDs, and triggers a buzzer at the highest voltage level.

## Table of Contents
- [Features](#features)
- [Hardware Components](#hardware-components)
- [Software Requirements](#software-requirements)
- [How It Works](#how-it-works)
- [Circuit Design](#circuit-design)
- [Firmware Implementation](#firmware-implementation)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [License](#license)

---

## Features
- Measures voltage using a 10-bit ADC.
- Maps voltage to 10 levels, indicated by LEDs.
- Activates a buzzer at the highest voltage level.
- Compact 2-layer PCB with all components on the top layer.
- Basic enclosure design for protection and usability.

---

## Hardware Components
- **Microcontroller**: STC8H1K08 or similar.
- **LEDs**: 4 LEDs for voltage indication.
- **Buzzer**: For audio indication at high voltage.
- **Resistors**: For LED current limiting and voltage divider.
- **Capacitors**: For decoupling.
- **DC-DC Converter**: To regulate voltage for the microcontroller.
- **PCB**: Custom-designed 2-layer PCB.

---

## Software Requirements
- **Compiler**: [Keil uVision](https://www.keil.com/) or SDCC for firmware development.
- **Programming Tool**: STC-ISP for flashing the microcontroller.
- **Libraries**: `FwLib` for STC microcontrollers.

---

## How It Works
1. The ADC reads the voltage between two points.
2. The firmware maps the ADC value to 10 levels.
3. LEDs illuminate corresponding to the voltage level:
   - 1 LED for the lowest level.
   - Up to 4 LEDs for the highest levels.
4. The buzzer beeps when the highest level is reached.

---

## Circuit Design
The circuit includes:
- ADC input with a voltage divider (if required).
- GPIO pins for LED and buzzer control.
- Power supply with a DC-DC converter.

Refer to the `schematic.pdf` file for the complete circuit diagram.

---

## Firmware Implementation
The firmware:
- Initializes the ADC for continuous sampling.
- Maps ADC results to voltage levels.
- Controls GPIO pins to activate LEDs and buzzer.

Refer to the [`main.c`](main.c) file for the complete firmware code.

---

## Getting Started
### Hardware Setup
1. Assemble the PCB.
2. Connect the voltage meter's input terminals to the voltage source.
3. Mount the components in the enclosure.

### Software Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/the7ag/8051-Voltage-Meter.git
   ```
2. Open the project in Keil uVision or SDCC.
3. Compile the code and flash it to the microcontroller using STC-ISP.

---

## Usage
1. Power the device using a battery.
2. Observe the LEDs to determine the voltage level.
3. Listen for the buzzer to identify high voltage.

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Feel free to reach out if you have any questions or need further assistance! 😊
