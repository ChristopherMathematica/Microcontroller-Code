# include <p32xxxx.h>
# include <xc.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
#include <sys/attribs.h>
# include "config_bits.h"   //note the quote sign -- configuration is important for the device to operate correctly
#include "strain_gauge.h"
#include "lcd.h"
#include <stdbool.h>
# include "adc.h"
# include "serial.h"
#include "pushbutton.h"
#include "CoinFunctionality.h"
#include "RGBLED.h"
#include "i2c.h"
#include "acl.h"
#include "config.h"
# define TurnTimer2On T2CON=0x8000 //Timer is initalized to high
void Run(void); //Function Prototype
void Run1(void);
unsigned long int count=0;
int flag=0;
char m[120];
void __ISR (12, IPL7SRS) T3Interrupt(void)
{
    flag=1;
    count++;
   LATAbits.LATA0^=1;
  IFS0bits.T3IF=0;   
}


void main(void){
    Run();
  }


void Run1(void){
    float rgACLGVals[3];   
    unsigned int baseCnt = 0;
    ACL_Init();
     while(1){
       //perform ACL readings only once in a while, to be able to visualize the results
        if(++baseCnt == 400000)
       {
            baseCnt = 0;        
            ACL_ReadGValues(rgACLGVals);
            //display on the LCD screen the X values, first row
            sprintf(m,"X: %6.3f", rgACLGVals[0]);
            putsLCD(m);   
        }
    }  
}






















void Run(void){
    Init_gauge();
    initLCD();
    InitTricoloredLED();
    InitButton();

while (1){
   //DisplayGaugeValue();
SortCoin(GetGaugeValue());    
//memset(s, 0, sizeof(s));
 if(BTN_GetValue(0)){
     //char u[120];
     //sprintf(u,"HHHow are you?");
    // putsLCD(u);
     MultiColored();
     delay_ms(100);
     //clrLCD();
}
}
}

