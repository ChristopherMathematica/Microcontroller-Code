# include <p32xxxx.h>

void Init_gauge (void)
{
    TRISCbits.TRISC4=1;  //RC4 FOR DATA IN
    ANSELGbits.ANSG6=0;  //RG6 FOR SCK OUT
    TRISGbits.TRISG6=0;
    LATGbits.LATG6=0;   //init SCK low
    T5CON=0x8020; //assume that you didn't use TMR5 for other things
}

unsigned long int read_gauge(void)
{
    int i;
    unsigned long int count=0;
    
    while (PORTCbits.RC4);
    TMR5=0;
    while (TMR5<100); //wait for 1.1 us here
    LATGbits.LATG6=0;        
    for (i=0; i<24;i++)
    {
       LATGbits.LATG6=1;
       TMR5=0;
       while (TMR5<10); //wait for 0.5 us here 
       LATGbits.LATG6=0;
       count=count<<1;
       if (PORTCbits.RC4)
       {
           count++;
       }
      TMR5=0;
       while (TMR5<10); //wait for 0.5 us here  
    }
    LATGbits.LATG6=1;
    TMR5=0;
    while (TMR5<10); //wait for 0.5 us here 
    LATGbits.LATG6=0;
    TMR5=0;
    while (TMR5<10); //wait for 0.5 us here 
    return count;
}

