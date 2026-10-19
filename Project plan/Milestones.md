# Project Schedule: Milestones & Phases

## Phase 1: Power and Safety (Hardware)
**Deadline: till 25.10.2026**

* **Equipment**
  * Buy necessary equipment.
* **Battery System**
  * Solder the 18650 battery holder to the 2S BMS (Battery Management System) board.
* **Charging Module**
  * Solder the TP5100 charging module with a USB-C port (set the 8.4V jumper).
* **Voltage Regulation**
  * Connect the LM2596 voltage regulator.
  * Calibrate it using the adjustment screw to output exactly 5.0V before connecting anything else.

---

## Phase 2: Software Setup
**Deadline: till 31.10.2026**

* **IDE Setup**
  * Configure the Keil uVision5 development environment.
* **System Clocks**
  * Initialize system clocks.
* **PC Communication**
  * Configure the hardware UART.
  * Establish communication with a PC terminal (send an initial "Hello World" message).

---

## Phase 3: Core Drivers
**Deadline: till 20.11.2026**

* **OLED Display**
  * Configure I2C and initialize the OLED display.
  * Display a static bitmap of an eye, loaded from Flash memory.
* **Servomotors**
  * Configure TPM0 (50 Hz PWM) and control 4 servomotors.
  * Test the range of motion to ensure the mechanisms are not damaged.
* **Buzzer**
  * Configure TPM1 (variable PWM) and test a single note on the buzzer.

---

## Phase 4: Sensors & Logic
**Deadline: till 19.12.2026**

* **Temperature Sensor**
  * Read ADC values from an LM35 temperature sensor.
* **RFID Module**
  * Configure SPI and read the UID from RFID tags using an RC522 module.
* **Vibration Sensor**
  * Configure an external interrupt for the SW-420 vibration sensor.
* **Main Logic**
  * Implement the final State Machine in `main.c` to handle sensor inputs.

---

## Phase 5: LabVIEW Application
**Deadline: till 24.12.2026**

* **User Interface**
  * Develop a program in LabVIEW to facilitate communication via a user interface.
