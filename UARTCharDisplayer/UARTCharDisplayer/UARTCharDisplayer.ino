//Reads character input. Displays its ascii value in binary using 8 leds: PORTC0 - PORTC1 & PORTD2 - PORTD7

#include <avr/io.h>
#include <util/delay.h>
#include <USART.h>

int main(void)
{
  //Setup
  char serialCharacter;

  DDRD = 0b11111100;
  DDRC = 0b00000011;
  initUSART();
  printString("Hello world!\n");
  


  //Loop
  while(1)
  {

    serialCharacter = receiveByte();
    transmitByte(serialCharacter);
    printString("\nCharacter: \n");
    printByte(serialCharacter);    
    //This whole workaround is because i don't have 8 sequential pins on Arduino UNO without using TX and RX pins so i have to use two ports

    PORTD = ( serialCharacter & 0b11111100 );
    PORTC = ( serialCharacter & 0b00000011 ); 

  }






  return 0;
}