/*
 * BT_RC_CAR.cpp
 *
 * Created: 02-01-2019 15:04:53
 * Author : CS
 */

#define F_CPU 16000000UL				// Define CPU clock Frequency e.g. here its 16MHz.
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "lcd.h"

#define LED0 PB0
#define LED1 PB1
#define LED2 PB2
#define LED3 PB3
#define LED4 PB4
#define LED5 PB5
#define LED6 PB6
#define LED7 PB7
#define LED_PORT PORTB
#define MOTOR00 PA6
#define MOTOR01 PA7
#define MOTOR10 PD2
#define MOTOR11 PD3
#define MOTOR0_PORT PORTA
#define MOTOR1_PORT PORTD
LCD4BIT lcd;
int flag;

void checker(int flag)
{
	if (flag == 1)
	{
		lcd.clearLCD();
	}
}

int main(void)
{
	char Data_in;
	bool Motor0_CW_State = false;
	bool Motor0_CCW_State = false;
	bool Motor1_CW_State = false;
	bool Motor1_CCW_State = false;
	lcd.initLCD();
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	USART_Init(9600);						// initialize USART with 9600 baud rate.
	while(1)
	{
		Data_in = USART_RxChar();
		checker(flag);
		if (Data_in == 'q')
		{
			LED_PORT ^= (1<<LED0);
			lcd.writeString("LED0");
		}
		else if (Data_in == 'w')
		{
			LED_PORT ^= (1<<LED1);
			lcd.writeString("LED1");
		}
		else if (Data_in == 'e')
		{
			LED_PORT ^= (1<<LED2);
			lcd.writeString("LED2");
		}
		else if (Data_in == 'r')
		{
			LED_PORT ^= (1<<LED3);
			lcd.writeString("LED3");
		}
		else if (Data_in == 't')
		{
			LED_PORT ^= (1<<LED4);
			lcd.writeString("LED4");
		}
		else if (Data_in == 'y')
		{
			LED_PORT ^= (1<<LED5);
			lcd.writeString("LED5");
		}
		else if (Data_in == 'u')
		{
			LED_PORT ^= (1<<LED6);
			lcd.writeString("LED6");
		}
		else if (Data_in == 'i')
		{
			LED_PORT ^= (1<<LED7);
			lcd.writeString("LED7");
		}
		else if (Data_in == 'm')
		{
			if (Motor0_CCW_State == true)
			{
				Motor0_CCW_State = !Motor0_CCW_State;
				MOTOR0_PORT ^= (0<<MOTOR00) | (1<<MOTOR01);
			}
			MOTOR0_PORT ^= (1<<MOTOR00) | (0<<MOTOR01);
			Motor0_CW_State = !Motor0_CW_State;
			lcd.writeString("MOTOR0 -->");
			lcd.clearLCD();
		}
		else if (Data_in == 'n')
		{
			if (Motor0_CW_State == true)
			{
				Motor0_CW_State = !Motor0_CW_State;
				MOTOR0_PORT ^= (1<<MOTOR00) | (0<<MOTOR01);
			}
			MOTOR0_PORT ^= (0<<MOTOR00) | (1<<MOTOR01);
			Motor0_CCW_State = !Motor0_CCW_State;
			lcd.writeString("MOTOR0 <--");
			lcd.clearLCD();
		}
		else if (Data_in == ',')
		{
			if (Motor1_CCW_State == true)
			{
				Motor1_CCW_State = !Motor1_CCW_State;
				MOTOR1_PORT ^= (0<<MOTOR10) | (1<<MOTOR11);
			}
			MOTOR1_PORT ^= (1<<MOTOR10) | (0<<MOTOR11);
			Motor1_CW_State = !Motor1_CW_State;
			lcd.writeString("MOTOR1 <--");
			lcd.clearLCD();
		}
		else if (Data_in == '.')
		{
			if (Motor1_CW_State == true)
			{
				Motor1_CW_State = !Motor1_CW_State;
				MOTOR1_PORT ^= (1<<MOTOR10) | (0<<MOTOR11);
			}
			MOTOR1_PORT ^= (0<<MOTOR10) | (1<<MOTOR11);
			Motor1_CCW_State = !Motor1_CCW_State;
			lcd.writeString("MOTOR1 -->");
			lcd.clearLCD();
		}
		else if (Data_in == 'o')
		{
			lcd.writeString("EVERYTHING OFF.");
			PORTA = 0x00;
			PORTB = 0x00;
			PORTC = 0x00;
			PORTD = 0x00;
			Motor0_CW_State = false;
			Motor0_CCW_State = false;
			Motor1_CW_State = false;
			Motor1_CCW_State = false;
			lcd.clearLCD();
		}
		else
		{
			USART_SendString("Select Proper Option.\r");
			lcd.writeString("Select Proper");
			lcd.setCursorAt(1,0);
			lcd.writeString("Option.");
		}
		flag = 1;
	}
	return 0;
}

