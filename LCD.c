#include<xc.h>
#include"config.h"
void Init_LCD(void);
void LCD_sendCW(char);
void LCD_sendData(char);

#define LCD_DATA PORTA
#define LCD_RS PORTAbits.RA0
#define LCD_E PORTBbits.RA1
#define SET LCD_sendCW(0b00111000)
#define D1C1 LCD_sendCW(0b00001100)
#define ENTRY LCD_sendCW(0b00000110)
#define CLEAR LCD_sendCW(0b00000001)
#define HOME LCD_sendCW(0b00000010)

char MESS[][] = {
				{"PRESS C TO FLY STRAIGHT"},
				{"INPUT TILT SIMULATION"},
				{"TILT CORRECTED"},
				{"SELECT TURN DIRECTION"},
				{"TURNING RIGHT"},
				{"TURNING LEFT"},
				{"INVALID INPUT"}
				}

void lcdmessage()
{
	unsigned char i;
	int m=1;
	ADCON1=0x0F;
	TRISA=0b11111100;
	TRISC=0b00000000;
	Init_LCD();
	m= PORTC & 0xf;
	TRISC=m;
	for(i=0;MESS[m][i]!=0;i++)
		LCD_sendData(MESS[m][i]);
}

void Init_LCD() //initialize
{
	SET;
	_delay(1);
	D1C1;
	_delay(1);
	ENTER;
	_delay(1);
	CLEAR;
	_delay(1);
	HOME:
	_delay(1);
}

void LCD_sendCW(char x)
{
	LCD_RS=0;
	LCD_E=1;
	LCD_DATA=x;
	LCD_E;
	_delay(1000);
}

void LCD_sendData(char x)
{
	LCD_RS=0;
	LCD_E=1;
	LCD_DATA=x;
	LCD_E=0;
	_delay(500);
}
