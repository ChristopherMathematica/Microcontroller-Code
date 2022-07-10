#include <p32xxxx.h>
#define NO_DIGITS sizeof(hexDigits)/sizeof(hexDigits[0])
const unsigned char hexDigits[] = {
   0b1000000,
   0b1111001,
   0b0100100,
   0b0110000,
   0b0011001,
   0b0010010,
   0b0000010,
   0b1111000,
   0b0000000,
   0b0010000
   };
   
unsigned char digits[4];
   
void InitSSD(void){
TRISGbits.TRISG12 = 0;
TRISAbits.TRISA14 = 0;
TRISDbits.TRISD6 = 0;
TRISGbits.TRISG13 = 0; 
TRISGbits.TRISG15 = 0;
TRISDbits.TRISD7 = 0;
TRISDbits.TRISD13 = 0;
TRISGbits.TRISG14 = 0; 
TRISBbits.TRISB12 = 0;
TRISBbits.TRISB13 = 0;
TRISAbits.TRISA9 = 0;
TRISAbits.TRISA10 = 0; 
ANSELBbits.ANSB12 = 0;
ANSELBbits.ANSB13 = 0;
PMCONbits.ON = 0; 

PR1 = (int)(((float)(0.003 *40000000) / 256) + 0.5); //set period register, generates one interrupt every 3 ms	
TMR1 = 0; // initialize count to 0
T1CONbits.TCKPS = 2; // 1:64 prescale value
T1CONbits.TGATE = 0; // not gated input (the default)
T1CONbits.TCS = 0; // PCBLK input (the default)
T1CONbits.ON = 1; // turn on Timer1
IPC1bits.T1IP = 7; // priority
IPC1bits.T1IS = 3; // subpriority
IFS0bits.T1IF = 0; // clear interrupt flag
IEC0bits.T1IE = 1; // enable interrupt

unsigned int val = 0; \
asm volatile("mfc0 %0,$13":"=r"(val)); \
val |= 0x00800000; \
asm volatile("mtc0 %0,$13" : "+r"(val)); \
INTCONbits.MVEC = 1; \
__builtin_enable_interrupts();
}

unsigned char SSD_GetDigitSegments(unsigned char d)
{
    unsigned char bResult = -1;
    if(d < NO_DIGITS)
    {
        bResult = hexDigits[d];
    }
    return bResult;
}

void SSD_WriteDigits(unsigned char d1, unsigned char d2, unsigned char d3, unsigned char d4, \
        unsigned char dp1, unsigned char dp2, unsigned char dp3, unsigned char dp4)
{
      T1CONbits.ON = 0;                   // turn off Timer1
    digits[0] = SSD_GetDigitSegments(d1);
    digits[1] = SSD_GetDigitSegments(d2);
    digits[2] = SSD_GetDigitSegments(d3);
    digits[3] = SSD_GetDigitSegments(d4);
    
    if(!dp1)
    {
        digits[0] |= 0x80;
    }
    if(!dp2)
    {
        digits[1] |= 0x80;
    }
    if(!dp3)
    {
        digits[2] |= 0x80;
    }
    if(!dp4)
    {
        digits[3] |= 0x80;
    }    
  T1CONbits.ON = 1;         //t1 on
}
