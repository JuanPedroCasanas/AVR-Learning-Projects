/*
very dumb code to figure out interrupts
It runs blinky and sets up an interrupt hooked up to a button that triggers a buzzer when the button is pressed
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED PORTB2


#define BUZZER_PORT PORTB
#define BUZZER_DDR DDRB
#define BUZZER PORTB0

#define BUTTON_BANK PCIE0
#define BUTTON_PORT PORTB
#define BUTTON_DDR DDRB
#define BUTTON_INT PCINT1
#define BUTTON_INT_VECT PCINT0_vect
#define BUTTON PORTB1


ISR(BUTTON_INT_VECT)
{
  BUZZER_PORT ^= (1 << BUZZER);
}


int main(void)
{
  LED_DDR |= (1 << LED);
  BUZZER_DDR |= (1 << BUZZER);
  BUTTON_DDR &= ~(1 << BUTTON); 
  
  //ENABLE PULLUP
  BUTTON_PORT |= (1 << BUTTON);


  PCICR |= (1 << BUTTON_BANK);
  PCMSK0 |= (1 << BUTTON_INT);

  sei();

  while(1)
  {
    LED_PORT |= (1 << LED);
    _delay_ms(1000);
    LED_PORT &= ~(1 << LED);
    _delay_ms(1000);
  }
}
