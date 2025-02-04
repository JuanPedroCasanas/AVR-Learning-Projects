
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "scale8.h"

#define SPEAKER_PORT PORTD
#define SPEAKER_DDR DDRD
#define SPEAKER PORTD6


static inline void initTimer(void) 
{
  TCCR0A |= (1 << WGM01);
  /* CTC mode */
  TCCR0A |= (1 << COM0A0);
  /* Toggles pin each cycle through */
  TCCR0B |= (1 << CS00) | (1 << CS01);
  /* CPU clock / 64 */
}
static inline void playNote(uint8_t wavelength, uint16_t duration) 
{
  OCR0A = wavelength;
  SPEAKER_DDR |= (1 << SPEAKER);
  while (duration) 
  {
    _delay_ms(1);
    duration--;
  }
  SPEAKER_DDR &= ~(1 << SPEAKER);
}

int main(void) 
{
  // -------- Inits --------- //
  initTimer();
  // ------ Event loop ------ //
  SPEAKER_PORT |= (1 << SPEAKER);
  while (1) 
  {
    playNote(C2, 200);
    playNote(E2, 200);
    playNote(G2, 200);
    playNote(Ax2, 200);
    playNote(G2, 200);
    playNote(E2, 200);
    playNote(C2, 200);
    _delay_ms(1000);
    playNote(C2, 200);
    playNote(F2, 200);
    playNote(A2, 200);
    playNote(C3, 200);
    playNote(A2, 200);
    playNote(F2, 200);
    playNote(C2, 200);
    _delay_ms(1000);
    playNote(G2, 200);
    playNote(B2, 200);
    playNote(D2, 200);
    playNote(F3, 200);
    playNote(D2, 200);
    playNote(B2, 200);
    playNote(G2, 200);
        _delay_ms(1000);
    playNote(C2, 200);
    playNote(E2, 200);
    playNote(G2, 200);
    playNote(C3, 200);
    playNote(G2, 200);
    playNote(E2, 200);
    playNote(C2, 200);
     _delay_ms(1000);
  }

}


























