// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#define LED_DDR DDRB
#define LED_PORT PORTB
// -------- Functions --------- //
static inline void initADC0(void) {
ADMUX |= (1 << REFS0); //Ref volt to ADCC

ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Prescaler to 128, should give 128Khz on the arduino uno 16Mhz clock

ADCSRA |= (1 << ADEN);
 /* enable ADC */
}
int main(void) 
{
  // -------- Inits --------- //
  uint8_t ledValue;
  uint16_t adcValue;
  uint8_t i;
  initADC0();
  LED_DDR = 0xff;
  

  // ------ Event loop ------ //
  while (1) 
  {
    ADCSRA |= (1 << ADSC);
    
    loop_until_bit_is_clear(ADCSRA, ADSC);
    
    adcValue = ADC;
    //read only two MSB (three LEDS)
    ledValue = (adcValue >> 8);

    LED_PORT = 0;
    for(uint8_t i = 0; i <= ledValue; i++)
    {
      LED_PORT |= (1 << i);
    }
    _delay_ms(100);
  }
return (0);
}