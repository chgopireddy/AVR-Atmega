#include <avr/io.h>
#include <avr/interrupt.h>
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR (FOSC/(16*BAUD))-1
int main(void)
{
  sei();
  ADMUX = (1<<REFS0)|(1<<ADLAR);
  ADCSRA = (1<<ADEN)|(1<<ADSC)|(1 << ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  USART_Init(MYUBRR);
  while(1);
} 
ISR(ADC_vect)
{
 USART_Transmit( ADCH );
 ADCSRA |= (1<<ADSC);
}
void USART_Init( unsigned int ubrr)
{
 UBRR0H = (unsigned char)(ubrr>>8);
 UBRR0L = (unsigned char)ubrr;
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}
void USART_Transmit( unsigned char data )
{
while ( !( UCSR0A & (1<<UDRE0)) );
UDR0 = data;
}

