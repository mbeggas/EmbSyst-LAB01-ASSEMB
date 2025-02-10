#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

// Global variables (placed in .data and .bss sections)
uint8_t global_data = 0x55;   // Initialized (.data section)
uint8_t global_bss;

int main() {
  do{
    Serial.begin(9600);
    _delay_ms(10000);

    Serial.println("=== AVR Memory Sections ===\r\n");

    // Print addresses of global variables
    Serial.print("Address of global_data (.data): ");
    Serial.println((uint16_t)&global_data, HEX);

    Serial.print("Address of global_bss (.bss): ");
    Serial.println((uint16_t)&global_bss, HEX);

    // Read Stack Pointer (SP)
    uint16_t sp = (SPH << 8) | SPL;
    Serial.print("Stack Pointer (SP) position: ");
    Serial.println(sp, HEX);

  }while (1);
}
