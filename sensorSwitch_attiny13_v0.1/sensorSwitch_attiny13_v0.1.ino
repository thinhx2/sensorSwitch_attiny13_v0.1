#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define butPin PB1
#define ledPin PB0

volatile boolean butIsShort = false;
volatile boolean led = false;


// the setup function runs once when you press reset or power the board
void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(butPin, INPUT);

  // External Interrupt(s) initialization
  // INT0: On
  // INT0 Mode: Falling Edge
  // Interrupt on any change on pins PCINT0-5: Off
  GIMSK = (1 << INT0) | (0 << PCIE);
  MCUCR = (1 << ISC01) | (0 << ISC00);
  GIFR = (1 << INTF0) | (0 << PCIF);

}

// the loop function runs over and over again forever
void loop() {
  while (1) {
    if (butIsShort) {
      digitalWrite(ledPin, !digitalRead(ledPin));
      butIsShort = false;
    }
  }
}
// External Interrupt 0 service routine
ISR(INT0_vect)
{
  butIsShort = true;
}
