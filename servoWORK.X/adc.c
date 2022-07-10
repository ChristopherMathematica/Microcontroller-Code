# include <p32xxxx.h>
# include "adc.h"

void initADC(void)
{
    ANSELBbits.ANSB2=1; //RB2 is an analog input
    TRISBbits.TRISB2=1;
    AD1CON1=0x00E0;  //enable autoconversion after sampling
    AD1CON2=0; //use default reference sources and no channel scanning
    AD1CON3=0x1F3F; // adc sampling and conversion time setting 1 Tsamp= 31 Tad, 1 Tad= 128 Tpb
    AD1CON1bits.ADON=1; // turn on ADC
}

int readADC (void)
{
    AD1CHSbits.CH0SA=2; //AN2 is the input for the ADC
    AD1CON1bits.SAMP=1;
    while (!AD1CON1bits.DONE);
    return ADC1BUF0;
}

void delay(int a)
{
    int i,j;
    for (i=0; i<a;i++)
    {for (j=0; j<1000;j++);}
   
}

void initU4(void)
{
    TRISFbits.TRISF13=1;
    U4RXR=0x09;
    TRISFbits.TRISF12=0;
    RPF12R=0x02;
    U4BRG=77;
    U4MODE=0x8008;
    U4STA=0X1400;
}

int putU4 (int c)
{
    while (U4STAbits.UTXBF);
    U4TXREG=c;
    return c;
}

char getU4 (void)
{
    while (!U4STAbits.URXDA);
    return U4RXREG;
}

int putsU4(char *s)
{
    while (*s)
    {
        putU4(*s++);
    }
    putU4('\r');
    putU4('\n');
}

int string_number(char *s)
{
    int a=0;
    int i=0;
    while (*s)
    {
        a=a*10+((int)(*s++)-48);
    }
    return a;
}

char *getsU4(char *s, int len)
{
    char *p=s;
    do 
    {
        *s=getU4();
        if (*s=='\r')
            break;
        s++;
        len--;
    }while (len>0);
    *s='\0'; //null terminated is important
    return p;
}
