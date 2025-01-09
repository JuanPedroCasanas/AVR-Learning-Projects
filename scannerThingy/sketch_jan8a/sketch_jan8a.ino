#include <avr/io.h>
#include <util/delay.h>
//lil scanner thing with five leds in the D port. Mostly to get acquainted with bit shifting again

int main(void)
{
  DDRD = 0b0011111;

  while(1)
  {
    int i;

    for(i = 0; i <= 5; i++)
    {
      PORTD |= (1 << i); 
      _delay_ms(100);
    }

    for(; i >= 0; i--)
    {
      PORTD ^= (1 << i);
      _delay_ms(100);
    }
  }


}

