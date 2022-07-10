# include <p32xxxx.h>
#include "lcd.h"

void delay_ms(int a)
{
    int i,j;
    for (i=0; i<a;i++)
    {
        for (j=0; j<10000;j++);
    }
} 

void delay_us(int b){
        int i,j;
    for (i=0; i<b;i++)
    {
        for (j=0; j<10;j++);
    }
}

void initLCD(void)
{
    PMCON=0x83BF;  // enable PMP, long wait
    PMMODE=0x03FF; //master mode 
    PMAEN=0x0001;  //PMA0 enabled
    T1CON= 0x8070;    //TMR1 sets to 256 Tpb (i.e. 8 us))
    TMR1=0; while (TMR1<5000); //wait for ~35 ms 
    
   PMADDR = LCDCMD;          // command register (ADDR = 0) 
   PMDATA = 0x38;            // set: 8-bit interface, 2 lines, 5x7 
   TMR1=0; while (TMR1<10);  //set ~50 us second waiting
   
   PMDATA = 0x0c; // ON, no cursor, no blink 
   TMR1 = 0; while( TMR1<10); // 7 x 7 us = 49 us 
   PMDATA = 0x01; // clear display  1011
   TMR1 = 0; while( TMR1<1000); //  260x 7 us ~ 1.8 ms 
 
  PMDATA = 0x06; // increment cursor, no shift 
   TMR1 = 0; while( TMR1<1000);  // 260 x 7 us = 1.8 ms 
    
}

char readLCD( int addr) 
   { 
 int dummy; 
  while( PMMODEbits.BUSY); // wait for PMP to be available 
  PMADDR = addr; // select the command address 
  dummy = PMDATA; // init read cycle, dummy read 
  while( PMMODEbits.BUSY); // wait for PMP to be available 
  return( PMDATA); // read the status register     
  } // readLCD

void writeLCD( int addr, char c) 
   {  
    while (busyLCD());
  while( PMMODEbits.BUSY);   // wait for PMP to be available 
  PMADDR = addr; 
  PMDATA = c;       
  TMR1 = 0; while( TMR1<100); // 7 x 7 us = 49 us 

} // writeLCD     

void putsLCD( char *s) 
   { 
  while( *s) 
  putLCD( *s++); 
   }//putsLCD

void secondLine(void){
    cmdLCD( 0x80 | 0x40); 
}