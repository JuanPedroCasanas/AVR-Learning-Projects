#include <USART.h>
#include <binaryMacro.h>
#include <macros.h>
#include <portpins.h>
#include <util/delay.h>

#define TRANSMIT_PIN PORTD3
#define BUTTON_PIN PORTD2
#define TRANSMIT_LED PORTB0
#define DEBOUNCE_TIME 5



uint8_t debounce(uint8_t port, uint8_t pin) 
{
  if (!(port & (1 << pin))) 
  {
    _delay_us(DEBOUNCE_TIME);
  }
  
  if (!(port & (1 << pin))) 
  {
  return 1; // Button pressed (low)
  }
  return 0;
}


int main (void)
{
  DDRD = 0b11110000; // PORTD7 - PORTD4 are used for displaying the binary. PORTD3 - PORTD2 are used for taking input from the buttons
  DDRB = (1 << TRANSMIT_LED); //Used for displaying the 'transmit in progress' led 

  PORTD = 0b00001100; //Init pullup resistors

  uint8_t binaryMessage = 0x00;


  while(1)
  {
    if(debounce(PIND, TRANSMIT_PIN))
    {
      binaryMessage = 0x00;
      PORTD &= 0x0F; //Reset display leds
      //start transmiting
      PORTB |= (1 << TRANSMIT_LED);

      for(int i = 3; i >= 0; i--)
      {
        PORTD |= (1 << i + 4); //offset for upper part of the PORTD registry
        
        for(uint16_t timeLeft = 1000; timeLeft > 0; timeLeft--)
        {
          if(debounce(PIND, BUTTON_PIN))
          {
            binaryMessage |= (1 << i);
            PIND |= (1 << BUTTON_PIN);
          }
          _delay_ms(1);
        }


        PORTD &= (0 << i + 4);
        _delay_ms(500);
        
      }
      PORTB &= (0 << TRANSMIT_LED);
      PORTD |= (binaryMessage << 4); //display message on leds
    }
  }
}