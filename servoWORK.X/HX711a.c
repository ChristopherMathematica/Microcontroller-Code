#include <p32xxxx.h>
#include "HX711a.h"
#include "HX711a.h"

void InitSG(void){
    TRISCbits.TRISC4 = 1; //Data
    ANSELGbits.ANSG6 = 0; //Output
    TRISGbits.TRISG6 = 0; //Send out clock
}
    
unsigned long ReadCount(void){
  unsigned long Count;
  unsigned char i;
  
  LATGbits.LATG6 = 0; 
  Count=0;
 // while(PORTCbits.RC4); //Sending 26 clock pulses  
  for(i=0;i<24;i++){ //Wait for data to change high to low
        LATGbits.LATG6 = 1; 
        Count=Count<<1;
        LATGbits.LATG6 = 0; 
      if(PORTCbits.RC4) Count++;
  }
  LATGbits.LATG6=1;
  Count=Count^0x800000;
  LATGbits.LATG6=0;
  return(Count);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               