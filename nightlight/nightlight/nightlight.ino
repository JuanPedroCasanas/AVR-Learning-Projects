/*
  This program makes use of a potentiometer connected to PORTC5 and a photoresistor connected to PORTC0
  The potentiometer determines a threshold of darkness for which a nighlight consisting of eight leds connected partially to PORTD and PORTB (To not interfere with TX & RX pins) that light up once said  threshold is reached.



*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>

//PINS
#define POT_PIN PORTC5
#define LIGHT_SENSOR_PIN PORTC0

uint16_t readADC(uint8_t channel) 
{
  ADMUX = (0xf0 & ADMUX) | channel;
  ADCSRA |= (1 << ADSC);
  loop_until_bit_is_clear(ADCSRA, ADSC);
  return ADC;
}

int main(void) 
{
  // -------- Inits --------- //
  uint16_t lightThreshold;
  uint16_t sensorValue;
  
  // Set up ADC

  /* reference voltage on AVCC */
  ADMUX |= (1 << REFS0);

  /* ADC clock prescaler /128 */
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  
  /* enable ADC */
  ADCSRA |= (1 << ADEN);
  
  //LED PORTS ARE PORTD 2 - 7 & PORTB 0 - 1
  DDRD = 0b11111100;
  DDRB = 0b00000011;

  while (1)
  {
    lightThreshold = readADC(POT_PIN);
    sensorValue = readADC(LIGHT_SENSOR_PIN);
    if (sensorValue < lightThreshold) 
    {
        PORTD = 0b11111100;
        PORTB = 0b00000011;
    }
    else 
    {
      PORTD = 0x00;
      PORTB = 0X00;
    }
  }
  return (0);
}