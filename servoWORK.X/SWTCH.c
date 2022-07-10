#include <p32xxxx.h>
#include "SWTCH.h"

void initSwitch(void){
    TRISFbits.TRISF3 = 1; // Configure digital inputs
    TRISFbits.TRISF5 = 1;
    TRISFbits.TRISF4 = 1;
    TRISDbits.TRISD15 = 1;
    TRISDbits.TRISD14 = 1;
    TRISBbits.TRISB11 = 1;
    TRISBbits.TRISB10 = 1;
    TRISBbits.TRISB9 = 1;
    // disable analog
    ANSELBbits.ANSB11 = 0;
    ANSELBbits.ANSB10 = 0;
    ANSELBbits.ANSB9 = 0;
}
unsigned char SwitchValue(unsigned char bNo){
    unsigned switchEnable = 0xFF;

    switch (bNo)
    {
        case 0: 
            switchEnable = PORTFbits.RF3; //SWT0 high
            break;
        case 1: 
            switchEnable = PORTFbits.RF5; //SWT1 high
            break;
        case 2: 
            switchEnable = PORTFbits.RF4; //SWT2 high
            break;
        case 3: 
            switchEnable = PORTDbits.RD15; //SWT3 high
            break;
        case 4: 
            switchEnable = PORTDbits.RD14; //SWT4 high
            break;
        case 5: 
            switchEnable = PORTBbits.RB11; //SWT5 high
            break;
        case 6: 
            switchEnable = PORTBbits.RB10; //SWT6 high
            break;
        case 7: 
            switchEnable = PORTBbits.RB9; //SWT7 high
            break;
    }

    return switchEnable;
}
