# include <p32xxxx.h>

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

