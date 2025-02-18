#include <avr/io.h>
#include <util/delay.h>

//For some reason my SG90 servo likes these values instead of the traditional 1 - 1.5 - 2 ms values
#define PULSE_MIN 125 //0.5ms at 64 prescaler
#define PULSE_MID 375//1.5ms
#define PULSE_HIGH 625//2.5ms

#define SERVO PORTB1
#define SERVO_PORT PORTB
#define SERVO_DDR DDRB


void initTimer1()
{
  //Toggle OCR1A on compare match
  TCCR1A |= (1 << COM1A1);

  //Fast PWM, ICR1 as top
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);

  TCCR1B |= (1 << CS10) | (1 << CS11); //64 prescaler = 4 microseconds per tick


  ICR1 = 5000; //How many 4 microseconds ticks do i need to get to 20 milliseconds? (20*10^-3)/(4*10^-6) = 5000 

}


void sentPulse(uint16_t pulse)
{
  OCR1A = pulse;
}



int main(void)
{
  SERVO_DDR |= (1 << SERVO);
  sentPulse(PULSE_MID);
  initTimer1();

  while(1)
  {
    _delay_ms(3000);
    sentPulse(PULSE_MIN);
    _delay_ms(750);
    sentPulse((PULSE_MIN + PULSE_MID) / 2);
    _delay_ms(1500);
    sentPulse(PULSE_HIGH);
    _delay_ms(750);
    sentPulse((PULSE_HIGH + PULSE_MID) / 2);
    _delay_ms(1500);
    sentPulse(PULSE_MID);
    _delay_ms(1000);

    for(uint16_t i = PULSE_HIGH; i > PULSE_MIN; i--)
    {
      sentPulse(i);
      _delay_ms(10);
    }
    sentPulse(PULSE_MID);
  }

}
