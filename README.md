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
## Arduino Code
```c
// Define the pin number for the built-in LED
const int ledPin = 13; 

void setup() {
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(ledPin, HIGH);
  // Wait for 1 second (1000 milliseconds)
  delay(1000);

  // Turn the LED off
  digitalWrite(ledPin, LOW);
  // Wait for 1 second (1000 milliseconds)
  delay(1000);
}

```
---
## Assembly Code

```asm
	.include "m328pdef.inc"

	.def	mask 	= r16		; mask register
	.def	ledR 	= r17		; led register
	.def	oLoopR 	= r18		; outer loop register
	.def	iLoopRl = r24		; inner loop register low
	.def	iLoopRh = r25		; inner loop register high

	.equ	oVal 	= 71		; outer loop value
	.equ	iVal 	= 28168		; inner loop value

	.cseg
	.org	0x00
	clr	ledR			; clear led register
	ldi	mask,(1<<PINB5)		; load 00100000 into mask register (0x20)
	out	DDRB,mask		; set PINB0 to output

start:	eor	ledR,mask		; toggle PINB0 in led register
	out	PORTB,ledR		; write led register to PORTB

	ldi	oLoopR,oVal		; initialize outer loop count

oLoop:	
	ldi	iLoopRl,LOW(iVal)	; intialize inner loop count in inner
	ldi	iLoopRh,HIGH(iVal)	; loop high and low registers

iLoop:	
	sbiw	iLoopRl,1		; decrement inner loop registers
	brne	iLoop			; branch to iLoop if iLoop registers != 0

	dec	oLoopR			; decrement outer loop register
	brne	oLoop			; branch to oLoop if outer loop register != 0

	rjmp	start			; jump back to start

```
