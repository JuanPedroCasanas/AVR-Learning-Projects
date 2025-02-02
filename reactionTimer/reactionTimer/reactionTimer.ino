#include <USART.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>



#define BUTTON_PORT PORTB
#define BUTTON_DDR DDRB
#define BUTTON_PIN PORTB1
#define BUTTON_IN PINB

#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_PIN PORTB2

#define MAX_DELAY 2000

void randomDelay()
{
  uint16_t randomTime = rand() % (MAX_DELAY + 1);

  for(; (randomTime + 1) > 0; randomTime--)
  {
    _delay_ms(1);
  }

}

void printMilliseconds(uint16_t value) 
  {
  /* Given a value in milliseconds, prints out how many seconds
     you took over the serial port.  Does ascii conversion, prints
     decimal point, and drops extra leading zeros.
   */
  uint8_t digit;
                                               /* add up ten-thousands */
  digit = 0;
  while (value >= 10000) 
  {
    digit++;
    value -= 10000;
  }
  if (digit) {
    transmitByte('0' + digit);
  }
                                                   /* add up thousands */
  digit = 0;
  while (value >= 1000) 
  {
    digit++;
    value -= 1000;
  }
  transmitByte('0' + digit);

                            /* decimal point here b/c dividing by 1000 */
  transmitByte('.');

                                                    /* add up hundreds */
  digit = 0;
  while (value >= 100) 
  {
    digit++;
    value -= 100;
  }
  transmitByte('0' + digit);
                                                        /* add up tens */
  digit = 0;
  while (value >= 10) {
    digit++;
    value -= 10;
  }
  transmitByte('0' + digit);

  // Ones digit is easy.
  transmitByte('0' + value);

  printString(" seconds.\r\n");
}


int main(void)
{
  uint16_t timerValue;

  LED_DDR |= (1 << LED_PIN);
  BUTTON_DDR &= ~(1 << BUTTON_PIN);

  BUTTON_PORT |= (1 << BUTTON_PIN); //Pullup resistor  

  //prescaler set to 1024 = roughly 64 microseconds per cpu tick = 15.625ms per cpu tick = 1ms per roughly 1/16 cpu ticks
  TCCR1B |= (1 << CS12) | (1 << CS10);

  initUSART();

  while(1)
  {
      LED_PORT &= ~(1 << LED_PIN);  
      printString("Press any key to start...\n");
      receiveByte();
      printString("Get ready!\n");

      randomDelay();
      LED_PORT |= (1 << LED_PIN);
      TCNT1 = 0; //reset timer
      //check if button was already pressed

      while(BUTTON_IN & (1 << BUTTON_PIN) ) //Loop until button is pressed (LOW VOLTAGE on press)
      { 
      }

      timerValue = TCNT1 /15.625; //15.625ms per cpu tick CAN ONLY STORE UP TO 4194MS BEFORE OVERFLOWING!
      printString("Congrats! Your score was: ");
      printMilliseconds(timerValue);
      printString("\n");


  }



  return 0;
} 