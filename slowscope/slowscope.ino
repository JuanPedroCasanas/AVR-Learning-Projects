/*
this is a very lazy project because i didn't want to bother with implementing the python code on my pc to display the 'osciloscope'
As it is now, it only reads values from a photoresistors and transmits said values via UART protocol
*/

#include <util/delay.h>
#include <avr/io.h>
#include <USART.h>

#define SAMPLE_DELAY 200
void setupADC()
{
  //setup for free running ADC
  ADCSRA |= (1 << ADEN); //Enable ADC
  ADMUX |= (1 << MUX2) | (1 << REFS0) | (1 << ADLAR); // Using A4 pin and AVCC as volt reference. Left justify results (I'll only be using ADCH and ignore the two LSB)
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //128 prescale for 16mHz should give 125kHz
  ADCSRA |= (1 << ADATE) | (1 << ADSC); //Enable autotrigger and start first conversion
}


int main(void)
{
  setupADC();
  initUSART();
  int i = 0;
  //loop
  while(1)
  {
    i++;  
    transmitByte(ADCH);
    _delay_ms(SAMPLE_DELAY);

  }

  return 0;
}
