#include <p32xxxx.h>
#include "lcd.h"
#include "LEDs.h"

void initLED(void){
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISAbits.TRISA6 = 0;
    TRISAbits.TRISA7 = 0;
}

void AllLEDsOn(void){
        LATAbits.LATA0 = 1;
        LATAbits.LATA1 = 1;
        LATAbits.LATA2 = 1;
        LATAbits.LATA3 = 1;
        LATAbits.LATA4 = 1;
        LATAbits.LATA5 = 1;
        LATAbits.LATA6 = 1;
        LATAbits.LATA7 = 1;
}
void AllLEDsOff(void){
        LATAbits.LATA0 = 0;
        LATAbits.LATA1 = 0;
        LATAbits.LATA2 = 0;
        LATAbits.LATA3 = 0;
        LATAbits.LATA4 = 0;
        LATAbits.LATA5 = 0;
        LATAbits.LATA6 = 0;
        LATAbits.LATA7 = 0;
}

void LEDBlink(void){
    int i;
    for(i = 0; i > 5;i++){
        delay_ms(1);
        AllLEDsOn();
        delay_ms(1);
        AllLEDsOff();
        delay_ms(1);
    }
}

void LEDtrail(void){
        LATAbits.LATA0 = 1;
        delay_us(700);
        LATAbits.LATA0 = 0;
        LATAbits.LATA1 = 1;
        delay_us(700);
        LATAbits.LATA1 = 0;
        LATAbits.LATA2 = 1;
        delay_us(700);
        LATAbits.LATA2 = 0;
        LATAbits.LATA3 = 1;
        delay_us(700);
        LATAbits.LATA3 = 0;
        LATAbits.LATA4 = 1;
        delay_us(700);
        LATAbits.LATA4 = 0;
        LATAbits.LATA5 = 1;
        delay_us(700);
        LATAbits.LATA5 = 0;
        LATAbits.LATA6 = 1;
        delay_us(700);
        LATAbits.LATA6 = 0;
        LATAbits.LATA7 = 1;
        delay_us(700);
        LATAbits.LATA7 = 0;
}

void LEDOddOrder(void){
        LATAbits.LATA5 = 1;  //5,7,0,2,4,6,1
        delay_us(700);
        LATAbits.LATA5 = 0;
        LATAbits.LATA7 = 1;
        delay_us(700);
        LATAbits.LATA7 = 0;
        LATAbits.LATA0 = 1;
        delay_us(700);
        LATAbits.LATA0 = 0;
        LATAbits.LATA2 = 1;
        delay_us(700);
        LATAbits.LATA2 = 0;
        LATAbits.LATA4 = 1;
        delay_us(700);
        LATAbits.LATA4 = 0;
        LATAbits.LATA6 = 1;
        delay_us(700);
        LATAbits.LATA6 = 0;
        LATAbits.LATA1 = 1;
        delay_us(700);
        LATAbits.LATA1 = 0;
        LATAbits.LATA3 = 1;
        delay_us(700);
        LATAbits.LATA3 = 0;
}

void ToggleLED(int caseNo, int mode){ // var1: LED No 0-7, var2: On(1)/off(0)
    switch(caseNo){
        case 0: LATAbits.LATA0 = mode;
        break;
        case 1: LATAbits.LATA1 = mode;
        break;
        case 2: LATAbits.LATA2 = mode;
        break;
        case 3: LATAbits.LATA3 = mode;
        case 4: LATAbits.LATA4 = mode;
        break;
        case 5: LATAbits.LATA5 = mode;
        break;
        case 6: LATAbits.LATA6 = mode;
        break;
        case 7: LATAbits.LATA7 = mode;
        break;
        default: AllLEDsOn();
    }
}

