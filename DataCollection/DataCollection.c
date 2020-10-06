 // Subroutine Declarations
#include <pic18.h>
// Subroutines
#include "lcd_portd.c"
#include "log.c"

unsigned int A2D_Read(unsigned char c)
{
 unsigned int result;
 unsigned char i;
 c = c & 0x0F;
 ADCON0 = (c << 2) + 0x01;
 for (i=0; i<20; i++);
 GODONE = 1;
 while(GODONE);
 return(ADRES);
 }
// Main Routine
void main(void)
{
 int A2D; // raw A/D readings
 int LUX; // TEMP Reading in Celsius
 unsigned int i, j;

LCD_Init();

// Turn on the serial port for 9600 baud
 TRISC = TRISC | 0xC0;
 TXIE = 0;
 RCIE = 0;
 BRGH = 1;
 BRG16 = 1;
 SYNC = 0;
 SPBRG = 255;
 TXSTA = 0x22;
 RCSTA = 0x90;

// Turn on the A/D
 TRISA = 0xFF;
 TRISE = 0x0F;
 ADCON2 = 0x85;
 ADCON1 = 0x07;
 ADCON0 = 0x01;
 i = 0;

 while(1) {
 A2D = A2D_Read(1);
 LUX = ( (1023.0 - A2D) / A2D ) * 1000;
LCD_Move(1,0);
LCD_Out(LUX,3,0);
 SCI_Out(LUX, 3, 0);
 SCI_CRLF(); // send carriage return line feed
 Wait_ms(100);
 }
 }