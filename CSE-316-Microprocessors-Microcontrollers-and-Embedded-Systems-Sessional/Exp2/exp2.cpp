#define F_CPU 1000000

#define TIMER_VAL 0x0F

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>

volatile int mode;

ISR(INT0_vect)
{
  _delay_ms(500);
  if (mode == 1)
    mode = 0;
  else
    mode++;
}

int main(void)
{
  uint16_t timer;
  int row = 0x00, j = 0;
  int col[8] = {
      0b11011101,
      0b11011101,
      0b11011101,
      0b11000001,
      0b11111101,
      0b11111101,
      0b11111101,
      0b11111101};

  mode = 0x00;

  DDRA |= 0xFF;
  DDRB |= 0xFF;
  DDRD |= 0x00;

  GICR = (1 << INT0);
  MCUCR |= 0b00000011;
  sei();

  while (1)
  {
    timer = TIMER_VAL;
    row = 0x01;
    for (int i = 0; i < 8; i++)
    {
      PORTA = row;
      if (i + j <= 7)
      {
        PORTB = col[i + j];
      }
      else
      {
        PORTB = col[i + j - 8];
      }
      _delay_ms(1);
      row = row << 1;
    }
    if (mode == 0)
    {
      j = 0;
    }
    else if (mode == 1)
    {
      if (j == 7)
        j = 0;
      else
        j += 1;
    }
  }
}