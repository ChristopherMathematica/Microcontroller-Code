# include <p32xxxx.h>
# include "RGBLED.h"
# include "LEDs.h"
void delay(int a){
    int i,j;
    for (i=0; i<a;i++)
    {
        for (j=0; j<10000;j++);
    }
}
void InitTricoloredLED(void){
    TRISAbits.TRISA0=0;
    LATAbits.LATA0=0;
    TRISAbits.TRISA5=0;
    LATAbits.LATA5=0;
    TRISFbits.TRISF3=1;
  //  ANSELBbits.ANSB11=0;
    TRISBbits.TRISB11=1;
    
    ANSELDbits.ANSD2=0;
    ANSELDbits.ANSD3=0;
    TRISDbits.TRISD2=0;
    TRISDbits.TRISD3=0;
    TRISDbits.TRISD12=0; 
    LATDbits.LATD2=0;
    LATDbits.LATD3=0;
    LATDbits.LATD12=0;
    
}

void tricolorled(int a){
    switch (a)
    {
        case 0:
            LATDbits.LATD2=0;
            LATDbits.LATD12=0;
            LATDbits.LATD3=0;
            
            break;
        case 1:
            LATDbits.LATD2=0;
            LATDbits.LATD12=0;
            LATDbits.LATD3=1;
            break;
        case 2:
            LATDbits.LATD2=0;
            LATDbits.LATD12=1;
            LATDbits.LATD3=0;
            break;
        case 3:
            LATDbits.LATD2=0;
            LATDbits.LATD12=1;
            LATDbits.LATD3=1;
            break;
        case 4:
           LATDbits.LATD2=1;
            LATDbits.LATD12=0;
            LATDbits.LATD3=0;
            break;
        case 5:
            LATDbits.LATD2=1;
            LATDbits.LATD12=0;
            LATDbits.LATD3=1;
            break;
        case 6:
           LATDbits.LATD2=1;
            LATDbits.LATD12=1;
            LATDbits.LATD3=0;
            break;
        case 7:
           LATDbits.LATD2=1;
            LATDbits.LATD12=1;
            LATDbits.LATD3=1;
            break;
    }
}

void MultiColored(void){
    int i;
    int count = 0;
   while(count < 8){
    i=count%8;
    tricolorled(i);
    delay_ms(10);
    count++;  
   } 
}
void LightShow(void){ //This function initializes LEDs from left to right
    tricolorled(0);   //In between each LED, the tricolored LED will light
    ToggleLED(7, 1);  // starting from red
    delay_ms(8);
    tricolorled(1);
    ToggleLED(7,0);
    ToggleLED(6, 1);
    delay_ms(8);
    tricolorled(2);
    ToggleLED(6,0);
    ToggleLED(5, 1);
    delay_ms(8);
    tricolorled(3);
    ToggleLED(5, 0);
    ToggleLED(4,1);
    delay_ms(8);
    tricolorled(4);
    ToggleLED(4, 0);
    ToggleLED(3,1);
    delay_ms(8);
    tricolorled(5);
    ToggleLED(3, 0);
    ToggleLED(2,1);
    delay_ms(8);
    tricolorled(6);
    ToggleLED(2, 0);
    ToggleLED(1,1);
    delay_ms(8);
    tricolorled(7);
    ToggleLED(1, 0);
    ToggleLED(0,1);
    delay_ms(8);
    AllLEDsOff();
}