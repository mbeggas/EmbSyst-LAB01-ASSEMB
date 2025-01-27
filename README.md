# Lab 1: Blinking an LED Using AVR Assembly on Arduino Uno

## Objective
This lab demonstrates how to use AVR assembly to control the GPIO pins of the ATmega328P microcontroller on an Arduino Uno. Specifically, you will blink the onboard LED (connected to **Pin 13**, or **PB5**).

---

## Hardware Requirements
- Arduino Uno board  
- USB cable  

---

## Software Requirements
- [Microship studio](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio) (AVR Assembler and AVR-C compiler for AVR microcontrollers)  
- [AVRDUDE](https://www.arduino.cc/en/software) (Integrated with Arduino IDE)  
To use AVRDUDE, upload HEX using Arduino IDE, set the upload mode to verbose in File->Preferences, then use the same command avrdude
---

## Pre-Lab Notes
1. **Registers Overview**:  
   - **DDRB**: Configures data direction for Port B (Input = `0`, Output = `1`).  
   - **PORTB**: Sets output high (`1`) or low (`0`) for Port B pins.  

2. **Pin Mapping**:  
   - **Pin 13** on Arduino Uno corresponds to **PB5** in the ATmega328P microcontroller.

---

## Circuit Diagram
No external wiring is needed for this lab. The Arduino Uno's onboard LED is pre-wired to **Pin 13 (PB5)**.

---

## Assembly Code

```asm
.include "m328Pdef.inc"  ; Include ATmega328P definitions

.org 0x0000             ; Reset vector
rjmp RESET              ; Jump to the RESET routine

.org 0x0040             ; Program code starts here
RESET:
    ; Set PB5 (Arduino Pin 13) as output
    ldi r16, 0b00100000  ; Load bit 5 (PB5) as output
    out DDRB, r16        ; Write to DDRB register

MAIN_LOOP:
    ; Turn on LED
    sbi PORTB, 5         ; Set PB5 (turn LED on)
    rcall DELAY          ; Call delay subroutine

    ; Turn off LED
    cbi PORTB, 5         ; Clear PB5 (turn LED off)
    rcall DELAY          ; Call delay subroutine

    rjmp MAIN_LOOP       ; Repeat loop

DELAY:
    ldi r18, 0xFF        ; Outer loop counter
DELAY_OUTER:
    ldi r19, 0xFF        ; Inner loop counter
DELAY_INNER:
    dec r19              ; Decrement inner counter
    brne DELAY_INNER     ; Repeat inner loop
    dec r18              ; Decrement outer counter
    brne DELAY_OUTER     ; Repeat outer loop
    ret                  ; Return from subroutine
