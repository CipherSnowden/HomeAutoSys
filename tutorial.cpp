/*
 * Tutorial.cpp
 *
 * Created: 20-01-2019 21:59:33
 * Author : Chetanya Saxena
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0b11111111;
    while (1)
    {
	    for(int i=1; i<=128; i=i+i)
	    {
			PORTB = i;
			_delay_ms(500);
	    }
    }
}
//Bye
