//lil scanner thing with five leds in the D port. Mostly to get acquainted with bit shifting again


#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIME 75
#define OSCILATIONS 1
#define RANDOM_LED_ITERATIONS 5


int main(void)
{
  DDRD = 0b11111000;
  uint8_t i;
  uint8_t j;
  uint16_t delay_time = DELAY_TIME;
  uint16_t randomNum = 0x1234;
  uint8_t randomLed;

  while(1)
  {
    for(j = 0; j < OSCILATIONS; j++)
    {

      for(i = 2; i <= 7; i++)
      {
        PORTD |= (1 << i); 
        _delay_ms(delay_time);
      }

      for(i = 2; i <= 7; i++)
      {
        PORTD &= ~(1 << i);
        _delay_ms(delay_time);
      }


      for(i = 7; i < 255; i--)
      {
        PORTD |= (1 << i); 
        _delay_ms(delay_time);
      }

      for(i = 7; i < 255; i--)
      {
        PORTD &= ~(1 << i);
        _delay_ms(delay_time);
      }
    }

    for(i = 0; i < RANDOM_LED_ITERATIONS; i++)
    {
      retry:
      randomNum = randomNum * 2053 + 13849;
      randomLed = ((randomNum >> 8) & 0b00000111);
      if(randomLed <= 3) //Prevens unconnected ports from lighting up
      {
        goto retry;
      }
      PORTD = (1 << randomLed); 
      _delay_ms(DELAY_TIME + 150);
      PORTD ^= (1 << randomLed);  
      _delay_ms(DELAY_TIME);
    }

    PORTD = 0;
  }
  return 0;
  
}

