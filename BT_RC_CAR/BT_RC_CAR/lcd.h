/*
 *	LCD 4-Bit Library
 *	Only for 16x2 LCD
 *	Made by CS
 */

#define LCD_CMD_DDR DDRA
#define LCD_DATA_DDR DDRA
#define LCD_CMD_PORT PORTA
#define LCD_DATA_PORT PORTA
#define LCD_RS 0
#define LCD_EN 1
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

class LCD4BIT
{
	private:
		void lcdCmd(int Command)
		{
			LCD_DATA_PORT = Command;
			LCD_CMD_PORT &= ~(1<<LCD_RS);
			LCD_CMD_PORT |= (1<<LCD_EN);
			_delay_ms(5);
			LCD_CMD_PORT &= ~(1<<LCD_EN);
			_delay_ms(10);
		}		
		void lcdData(char Data)
		{
			LCD_DATA_PORT = Data;
			LCD_CMD_PORT |= (1<<LCD_RS);
			LCD_CMD_PORT |= (1<<LCD_EN);
			_delay_ms(5);
			LCD_CMD_PORT &= ~(1<<LCD_EN);
			_delay_ms(10);
		}		
	public:
		void writeCMD(int Command)
		{
			char TempCmd;
			TempCmd = Command & 0xF0;			//mask lower nibble, because PA4-PA7 pins are used.
			lcdCmd(TempCmd);					// send to LCD
			TempCmd = ((Command<<4) & 0xF0);	//shift 4-bit and mask
			lcdCmd(TempCmd);
		}
		void writeData(char Data) {
			char TempData;
			TempData = Data & 0xF0;
			lcdData(TempData);
			TempData = ((Data<<4) & 0xF0);
			lcdData(TempData);
		}		
		void initLCD()
		{
			LCD_DATA_DDR |= (1<<LCD_D4) + (1<<LCD_D5) + (1<<LCD_D6) + (1<<LCD_D7);
			LCD_CMD_DDR |= (1<<LCD_RS) + (1<<LCD_EN);
			writeCMD(0x02);
			writeCMD(0x28);
			clearLCD();
			writeCMD(0x0E);
			setCursorAt(0,0);
		}
		
		void writeString(char *StringOfData)
		{
			for(int i=0 ; StringOfData[i]!='\0' ; i++)
			{
				writeData(StringOfData[i]);
			}
		}		
		char convertIntToChar(int Integer)
		{
			char ToChar = Integer + '0';
			return ToChar;
		}		
		void setCursorAt(int Row, int Position)
		{
			Row == 0 ? writeCMD(0x80 + Position) : writeCMD(0xC0 + Position);
		}		
		void decrementCursor()
		{
			writeCMD(0x04);
		}		
		void incrementCursor()
		{
			writeCMD(0x06);
		}		
		void clearLCD()
		{
			writeCMD(0x01);
		}
};