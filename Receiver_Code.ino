#include <avr/io.h>
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR (FOSC/(16*BAUD))-1
int main(void)
{
  DDRD=(1<<DDD6);
  TCCR0A=(1<<COM0A1)|(1<<WGM00)|(1<<WGM01);
  TCCR0B=(1<<CS00);
  USART_Init(MYUBRR);
  while(1)
  {
    OCR0A=USART_Receive();
  }
}
void USART_Init( unsigned int ubrr)
{
 UBRR0H = (unsigned char)(ubrr>>8);
 UBRR0L = (unsigned char)ubrr;
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}
unsigned char USART_Receive( void )
{
 while ( !(UCSR0A & (1<<RXC0)) );
 return UDR0;
}

