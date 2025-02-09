# Arduino Beginner Lab: LED Control with a Push Button

## Materials Required 🛠️
- 1 Arduino board (UNO, Mega, Nano...)
- 1 LED
- 1 220Ω resistor (for the LED)
- 1 push button
- 1 10kΩ resistor (for the button)
- Jumper wires
- A breadboard

## Circuit Wiring ⚡

1. **LED**:
   - The **long leg (anode)** of the LED is connected to **pin 9** on the Arduino via a **220Ω resistor**.
   - The **short leg (cathode)** is connected to **GND** (ground).

2. **Push Button**:
   - One leg of the button is connected to **GND**.
   - The other leg is connected to **pin 2** on the Arduino and to **+5V via a 10kΩ resistor** (pull-up).

## Arduino Code (C++) 🎛️

```cpp
const int ledPin = 9;  // LED pin
const int buttonPin = 2;  // Button pin
int buttonState = 0;  // Button state

void setup() {
  pinMode(ledPin, OUTPUT);  // LED as output
  pinMode(buttonPin, INPUT_PULLUP);  // Button as input with internal pull-up
}

void loop() {
  buttonState = digitalRead(buttonPin);  // Read button state
  
  if (buttonState == LOW) {  // Button pressed (pull-up active)
    digitalWrite(ledPin, HIGH);  // Turn LED on
  } else {
    digitalWrite(ledPin, LOW);  // Turn LED off
  }
}
```

## Explanation 🧐
- `pinMode(buttonPin, INPUT_PULLUP);` → Enables Arduino's internal pull-up resistor.
- `digitalRead(buttonPin);` → Reads button state (`LOW` if pressed, `HIGH` otherwise).
- `digitalWrite(ledPin, HIGH);` → Turns LED on when the button is pressed.

## AVR-C Code 🎛️

```c
#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB1  // LED connected to PB1 (Arduino pin 9)
#define BUTTON_PIN PD2  // Button connected to PD2 (Arduino pin 2)

int main(void) {
    DDRB |= (1 << LED_PIN);  // Set LED pin as output
    DDRD &= ~(1 << BUTTON_PIN);  // Set button pin as input
    PORTD |= (1 << BUTTON_PIN);  // Enable pull-up resistor on button pin
    
    while (1) {
        if (!(PIND & (1 << BUTTON_PIN))) {  // Check if button is pressed (LOW state)
            PORTB |= (1 << LED_PIN);  // Turn LED on
        } else {
            PORTB &= ~(1 << LED_PIN);  // Turn LED off
        }
    }
    return 0;
}
```

## Explanation 🧐
- `DDRB |= (1 << LED_PIN);` → Configures LED pin as an output.
- `DDRD &= ~(1 << BUTTON_PIN);` → Configures button pin as an input.
- `PORTD |= (1 << BUTTON_PIN);` → Activates the pull-up resistor on the button pin.
- `if (!(PIND & (1 << BUTTON_PIN)))` → Checks if the button is pressed (LOW state).
- `PORTB |= (1 << LED_PIN);` → Turns LED on when the button is pressed.

## AVR Assembly Code 🎛️

```assembly
    .include "m328pdef.inc"  ; Include device definitions for ATmega328P

    ; Define LED and Button pins
    .equ LED_PIN = PB1  ; LED connected to PB1 (Arduino pin 9)
    .equ BUTTON_PIN = PD2  ; Button connected to PD2 (Arduino pin 2)

    .cseg
    .org 0x00
    rjmp main

main:
    ; Configure LED_PIN as output
    sbi DDRB, LED_PIN
    
    ; Configure BUTTON_PIN as input
    cbi DDRD, BUTTON_PIN
    sbi PORTD, BUTTON_PIN  ; Enable pull-up resistor

loop:
    sbis PIND, BUTTON_PIN  ; Check if button is pressed (LOW state)
    rjmp turn_on
    rjmp turn_off

turn_on:
    sbi PORTB, LED_PIN  ; Turn LED on
    rjmp loop

turn_off:
    cbi PORTB, LED_PIN  ; Turn LED off
    rjmp loop
```

## Explanation 🧐
- `sbi DDRB, LED_PIN;` → Sets LED pin as output.
- `cbi DDRD, BUTTON_PIN;` → Sets button pin as input.
- `sbi PORTD, BUTTON_PIN;` → Activates the pull-up resistor on the button pin.
- `sbis PIND, BUTTON_PIN;` → Skips the next instruction if the button is not pressed.
- `sbi PORTB, LED_PIN;` → Turns LED on when the button is pressed.
- `cbi PORTB, LED_PIN;` → Turns LED off when the button is not pressed.

