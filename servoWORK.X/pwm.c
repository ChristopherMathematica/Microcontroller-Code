# include <p32xxxx.h>

void initWheels(void)
{
    TRISDbits.TRISD9=0;
    LATDbits.LATD9=1;
    TRISDbits.TRISD11=0;
    RPD11R=11; //set RPD11 as OC4
    
    PR3=18000;
    TMR3=0;
    T3CON=0x0000;
    OC4R=100;
    OC4RS=12100;
    OC4CON=0x800d; //TMR3 as basis and output compare mode
    
    TRISCbits.TRISC14=0;
    LATCbits.LATC14=0;
    TRISDbits.TRISD0=0;
    RPD0R=12; //RPD0R to OC1
    OC1R=100;
    OC1RS=12100;
    OC1CON=0x800d; //TMR3 as basis and output compare mode
    
}
