#define F_CPU 1000000

#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "lcd.h"

int main(void)
{
  MCUCSR = (1 << JTD);
  MCUCSR = (1 << JTD);

  DDRB = 0xFF;
  DDRC = 0xFF;
  DDRD = 0xFF;

  ADCSRA = 0b10000111;
  ADMUX = 0b01110000;

  unsigned char result;
  unsigned int voltage, fraction;
  char buffer[4];

  Lcd4_Init();

  while (1)
  {
    ADCSRA |= (1 << ADSC);
    while ((ADCSRA & (1 << ADIF)) == 0)
      ;

    result = ADCH;
    voltage = ((result << 2) * 5) / 51;
    fraction = voltage % 10;
    voltage = voltage / 10;

    sprintf(buffer, "%d.%d V", voltage, fraction);
    Lcd4_Set_Cursor(1, 6);
    Lcd4_Write_String(buffer);
  }
}
