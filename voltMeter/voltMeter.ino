#include <USART.h>
#include <math.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define REF_VCC 5.080
#define VOLTAGE_DIV_FACTOR 3.022

void setupADC()
{
  ADMUX |= (1 << REFS0); //AVCC ref voltage
  ADMUX &= ~(0b00001111); // MUX 0..3 = 0 -> ADC0 as input
  ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // 128 prescaler, 125kHz
  ADCSRA |= (1 << ADEN); //Enable ADC
  //free running mode
}

void setupADCSleepMode()
{
  set_sleep_mode(SLEEP_MODE_ADC);
  ADCSRA |= (1 << ADIE); //enable adc interrupt
  sei();
}

EMPTY_INTERRUPT(ADC_vect);

uint16_t oversample16x(void) 
{
  uint16_t oversampledValue = 0;
  uint8_t i;
  for (i = 0; i < 16; i++) {
  sleep_mode();
  oversampledValue += ADC;
  }
  return (oversampledValue >> 2);
}

void printFloat(float number) 
{
  int intPart = (int)number;  // Integer part
  int decPart = (int)((number - intPart) * 100);  // Two decimal places

  // Correct rounding
  if (decPart < 0) decPart = -decPart;  // Ensure positive decimal part

  transmitByte('0' + intPart / 10);  // Tens place
  transmitByte('0' + intPart % 10);  // Ones place
  transmitByte('.');
  transmitByte('0' + (decPart / 10));  // Tenths place
  transmitByte('0' + (decPart % 10));  // Hundredths place
  printString("\r\n");
}


int main(void)
{
  float measuredVoltage;

  initUSART();
  printString("\r\nDigital Voltmeter\r\n\r\n");
  setupADC();
  setupADCSleepMode();



  while(1)
  {
    measuredVoltage = oversample16x() * VOLTAGE_DIV_FACTOR * REF_VCC / (4096.0);
    printFloat(measuredVoltage);
    _delay_ms(500);
    


  }



}