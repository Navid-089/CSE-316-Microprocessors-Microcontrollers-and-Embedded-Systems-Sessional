#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000
int main(void)
{
  DDRA = 0xFC; // input
  PORTA = 0x00;
  DDRB = 0x0F; // output
  while (1)
  {
    if (PINA & (1 << PINA0))
    {
      PORTB = (PORTB + 5) % 16;
      _delay_ms(100);
    }
    if (PINA & (1 << PINA1))
    {
      PORTB = (PORTB + 11) % 16;
      _delay_ms(100);
    }
  }
  return 0;
}
