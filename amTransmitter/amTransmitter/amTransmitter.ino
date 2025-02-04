#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BEEP_DELAY 1000
#define BEEP_DURATION 500

#define ANTENNA_PORT PORTD
#define ANTENNA_DDR DDRD
#define ANTENNA_PIN PORTD6

#define AM_FREQUENCY_FACTOR 4 
//AM Frequency = (F_CPU / Prescaler) / AM_FREQUENCY_FACTOR (OCR2A) + 1 (Extra cycle the timer goes through)
// From f = f_cpu / ( 2* N* (1 + OCRnx) )
// Good values for the AM band from 2 to 6: pick one that's clear
// Divide by two b/c we're toggling on or off each loop;
// a full cycle of the carrier takes two loops.
// 16Mhz / (2 * 1 * (1+2)) = 2666 kHz
// 16Mhz / (2 * 1 * (1+3)) = 2000 kHz
// 16Mhz / (2 * 1 * (1+4)) = 1600 kHz
// 16Mhz / (2 * 1 * (1+5)) = 1340 kHz
// 16Mhz / (2 * 1 * (1+6)) = 1140 kHz
// 16Mhz / (2 * 1 * (1+7)) = 1000 kHz


ISR(TIMER2_COMPA_vect)
{
  ANTENNA_DDR ^= (1 << ANTENNA_PIN);
}

void initTimer0()
{
  TCCR0A |= (1 << WGM01); //CTC Mode
  TCCR0A |= (1 << COM0A0); //toggle OC0A (PD6) on compare match
  TCCR0B |= (1 << CS00); //Start clock, no prescaler
  OCR0A = AM_FREQUENCY_FACTOR; //Set compare value to carrier frequency factor
}

void initTimer2()
{
  TCCR2A |= (1 << WGM21); //CTC Mode
  TCCR2B |= (1 << CS21) | (1 << CS20); //Start clock, 1/32 prescaler. I didnt calculate much, just kept it to this value to keep the pitches value low in the transmitBeep function
  TIMSK2 |= (1 << OCIE2A); //Interrupts on compare match
}

void transmitBeep(uint16_t pitch,  uint16_t duration)
{
  OCR2A = pitch;
  sei(); //Enable interrupts to modulate the carrier frequency
  TCNT2 = 0;
  do 
  {
    _delay_ms(1);
    duration--;
  } 
  while (duration > 0);
  cli();
  ANTENNA_DDR ^= (1 << ANTENNA_PIN);
}

int main(void)
{
  initTimer0();
  initTimer2();

  while(1)
  {
    //I was too lazy to use the scale.h file, but his should transmit a major chord

    transmitBeep(250, BEEP_DURATION);
    _delay_ms(BEEP_DELAY);
    transmitBeep(200, BEEP_DURATION);
    _delay_ms(BEEP_DELAY);
    transmitBeep(166, BEEP_DURATION);
    _delay_ms(BEEP_DELAY);
    transmitBeep(125, BEEP_DURATION);
    _delay_ms(BEEP_DELAY);

  }
}