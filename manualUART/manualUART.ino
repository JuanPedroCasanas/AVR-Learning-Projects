//Dumb project to understand how to read the data sheet for ATMEGA328 microcontroller and manually set UART protocol

#include <USART.h>
#include <binaryMacro.h>
#include <macros.h>
#include <pinDefines.h>

#define BAUD_RATE 9600L

int main(void)
{

  uint16_t ubrr = (uint16_t) ( ( F_CPU  / (BAUD_RATE * 16) ) - 1 );

  // Set baud rate
  UBRR0H = (uint8_t)(ubrr >> 8);   // High byte of the baud rate
  UBRR0L = (uint8_t)(ubrr);        // Low byte of the baud rate

  //Enable RX & TX
  UCSR0B |= (1 << RXEN0);
  UCSR0B |= (1 << TXEN0);

  //6 bits of data per message
  UCSR0C = (1 << UCSZ01);

  while(1)
  {
    while(!(UCSR0A & (1 << UDRE0)))
    {
      //Do nothing if data registry is not empty
    };
  
    UDR0 = '?'; //Should transmit correctly

    while(!(UCSR0A & (1 << UDRE0)))
    {
      //Do nothing if data registry is not empty
    };

    UDR0 = '@'; //Should truncate because this value cannot be stored in 6 bits
    
    while (!(UCSR0A & (1<<RXC0)))
    {
      //wait for data to be received
    };
    
    //echo data back to the pc
    UDR0 = UDR0;



    _delay_ms(5000);

  }

  return 0;
}