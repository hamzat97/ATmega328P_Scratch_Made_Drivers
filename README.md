# ATmega328P_Scratch_Made_Drivers

Welcome to the GitHub repository for **"Beyond the Libraries: Developing Pure C Drivers from Scratch for ATmega328P"**, a comprehensive guide and resource hub for learning how to develop drivers for the ATmega328P microcontroller from the ground up using pure C. No predefined libraries, no shortcuts, just bare metal programming. The drivers developed in this project include GPIO, ADC, Timers, and UART.

<p align="center"><img src="giphy.webp"></p>

## 📜 Overview

This repository contains :

- **Documentation** : A detailed presentation that covers :
  
  - GPIO, ADC, Timers, and UART peripherals.
  - Key concepts and operation of each peripheral.
  - Step by step driver development process.
  - Testing and simulation using ISIS Proteus.

- **Source Code** : Fully functional and tested pure C driver implementations for :

  - General Purpose Input/Output (GPIO)
  - Analog to Digital Converter (ADC)
  - Timer1 (Timing, Counting and PWM generation)
  - UART (Serial Communication)

- **Simulation Schematics** : Proteus ISIS schematics for testing and validating the drivers.

## 🌿 Repository Structure

```
├── Documentation.pdf
├── Source_Code
│   ├── GPIO
│   │   ├── gpio.h
│   │   ├── gpio.c
│   │   └── app_gpio.c
│   │   └── app_gpio.elf
│   │   └── app_gpio.hex
│   ├── ADC
│   │   ├── adc.h
│   │   ├── adc.c
│   │   └── app_adc.c
│   │   └── app_adc.elf
│   │   └── app_adc.hex
│   ├── Timers
│   │   ├── timer1.h
│   │   ├── timer1.c
│   │   └── app_timer1.c
│   │   └── app_timer1.elf
│   │   └── app_timer1.hex
│   ├── UART
│   │   ├── uart.h
│   │   ├── uart.c
│   │   └── app_uart_transmitter.c
│   │   └── app_uart_receiver.c
│   │   └── app_uart_transmitter.elf
│   │   └── app_uart_transmitter.hex
│   │   └── app_uart_receiver.elf
│   │   └── app_uart_receiver.hex
├── Schematics
│   ├── Schematic_GPIO.dsn
│   ├── Schematic_ADC.dsn
│   ├── Schematic_TIMER1.dsn
│   └── Schematic_UART.dsn
└── README.md
```

## ✨ Key Features

- **Educational Focus** : Designed for embedded systems enthusiasts looking to master low-level MCU programming.
- **Comprehensive Approach** : Covers peripheral operation, register-level configurations, and testing.
- **No Dependencies** : Builds and runs using only AVR-GCC and AVRDude.
- **Cross-Compatible** : Suitable for both DIP and TQFP versions of ATmega328P.

## 📘 Documentation

The documentation provides :

- Peripheral overviews
- Key configuration registers
- Driver development steps
- Testing and simulation instructions

## 🚀 Getting Started

### Requirements
To make the most of this repository, you will need :
- **Hardware** : Arduino Uno (optional) or ATmega328P microcontroller setup.
- **Software** :
  - AVR-GCC Toolchain
  - AVRDude
  - Proteus ISIS for simulation
  - VS Code or any preferred text editor/IDE

### Quick Start Guide

**1.** Clone the repository :

  ```
  git clone https://github.com/your_username/beyond-the-libraries.git
  ```

**2.** Navigate to the desired driver folder (e.g., GPIO) :

```
cd Source_Code/GPIO
```

**3.** Build and flash the code (e.g., GPIO) :

```
avr-gcc -g -Os -DF CPU=16000000UL -mmcu=atmega328p -o APP_GPIO.elf APP_GPIO.c GPIO.c
avr-objcopy -O ihex -R .eeprom APP GPIO.elf APP GPIO.hex
#  -g           : Includes debugging information (optional for debugging).
#  -Os          : Optimizes the code for size.
#  -DF_CPU=     : Defines the clock frequency (16 MHz here).
#  -mmcu=       : Specifies the target microcontroller (ATmega328P in this case).
#  -o ...       : Specifies the output file (APP_GPIO.elf).
#  APP_GPIO.c   : The main application source file.
#  GPIO.c       : The GPIO driver source file.
#  -O ihex      : Specifies the output file format (Intel HEX).
#  -R .eeprom   : Excludes the EEPROM section from the output.
#  APP_GPIO.elf : The input file (compiled ELF file).
#  APP_GPIO.hex : The output HEX file to flash onto the microcontroller.
```

Upload the code to the simulated ATmega328P in the prepared schematic or flash your Arduino Uno with AVRDude, as shown below.

![SCREEN_GITHUB](https://github.com/user-attachments/assets/83a1ebca-8cb8-40e7-8e5e-9bbd62f5a59e)

**4.** Test the functionality using the provided Proteus schematics.

## 📧 Contact

Have questions or feedback? Reach out via :
- **Email** : hamzataous847@gmail.com
- **LinkedIn** : https://ma.linkedin.com/in/hamza-taous-374b45173

The journey starts here. Clone this repository and use it as a foundation to build something amazing, the sky is is the limit!
