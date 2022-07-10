#include <p32xxxx.h>
#include <xc.h>
#include <sys/attribs.h>
#include "pushbutton.h"
#include "prompts.h"
#include "LEDs.h"

void InitButton(void){
    // Configure digital inputs
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB0 = 1;
    TRISFbits.TRISF0 = 1;
    TRISBbits.TRISB8 = 1;
    // Disable analog
    ANSELBbits.ANSB1 = 0;
    ANSELBbits.ANSB0 = 0;
    ANSELBbits.ANSB8 = 0;
}

unsigned char buttonValue(unsigned char buttonNo)
{
    unsigned button = 0xFF;
    
    switch (buttonNo)
    { 
        case 0:
            button = PORTBbits.RB1; //BTN0 high
            break;
        case 1:
            button = PORTBbits.RB0; //BTN1 high
            break;
        case 2:
            button = PORTFbits.RF0; //BTN2 high
            break; 
        case 3:
            button = PORTBbits.RB8; //BTN3 high
            break;
        case 4:
            button = PORTAbits.RA15; //BTN4 high
            break;
    }

    return button;
}

void clearButtons(void){
    // Disable digital inputs.
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB0 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB8 = 0;
    // Enable analog 
    ANSELBbits.ANSB1 = 1;
    ANSELBbits.ANSB0 = 1;
    ANSELBbits.ANSB8 = 1;
}

