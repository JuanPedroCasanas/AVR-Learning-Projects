#include <macros.h>
#include <pinDefines.h>
#include <portpins.h>
#include <util/delay.h>

/*
Simple POV toy made with five leds & resistors connected to the PORTD pins from 0 - 4 (D0 to D4 in Arduino UNO). 

!!! Be careful while flashing !!! 
If leds are connected to the D0 and D1 port (RX & TX) while flashing the process will hang. Unplug said pins to flash correctly. 

*/

void displayPov(uint8_t dir)
{
    PORTD = dir;
    _delay_ms(20);
};

int main(void)
{
  DDRD = 0b00011111;


  while(1)
  {
    displayPov(0b00011111);
    displayPov(0b00011011);
    displayPov(0b00010001);
    displayPov(0b00000000);
    displayPov(0b00000100);
    displayPov(0b00001110);
  }
}