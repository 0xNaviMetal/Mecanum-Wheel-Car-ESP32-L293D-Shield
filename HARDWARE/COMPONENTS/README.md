# 🔌 Hardware Documentation

This section contains all the hardware details, components, and wiring instructions needed to build the ESP32 Mecanum Wheel Car.

## 🛒 Bill of Materials (BOM)
To build this project, you will need the following components:

* **ESP32 Microcontroller** (CH340 version used in this build)
* **L293D Motor Drive Shield** (Standard Arduino Uno form factor)
* **4x DC Gear Motors** (with appropriate voltage rating for your power supply)
* **4x Mecanum Wheels** (Important: Make sure to have 2 'Left' and 2 'Right' wheels for proper kinematics)
* **Jumper wires & basic soldering equipment**

---

## ⚡ Wiring & Power Connections

*(You can add an image of your schematic here like this: `![Schematic](schematics/diagram.png)`)*

### ESP32 to 74HC595 (L293D Shield)
| Shield Pin (74HC595) | ESP32 GPIO | Function |
| :--- | :--- | :--- |
| `DIR_SER` | **GPIO 21** | Serial Data Pin |
| `DIR_CLK` | **GPIO 19** | Clock Pin |
| `DIR_LATCH` | **GPIO 23** | Latch Pin |
| `DIR_EN` | **GPIO 18** | Output Enable (Active LOW) |

---

## 🚀 Hardware Setup & Getting Started

1. **Wiring:** Connect the ESP32 to the L293D shield according to the pin table above using jumper wires.
2. **Power Distribution (CRITICAL):** 
   * Ensure the ESP32 is powered safely via 3.3V/5V.
   * The L293D shield **must** receive external motor power.
   * **Do not** power the 4 DC motors directly from the ESP32 pins, or you will burn the board!
3. **Upload Firmware:** Open the code in the `Firmware/` folder using the Arduino IDE, select your ESP32 board, and flash the code.
4. **Bluetooth Setup:** 
   * Download a standard Bluetooth Serial Terminal app on your smartphone (e.g., "Serial Bluetooth Terminal" on Android).
   * Pair your phone to the ESP32 (Bluetooth name: `BT.ESP32`).
   * Send characters like `F`, `B`, `L`, `R`, or `S` to test the motor rotations.
