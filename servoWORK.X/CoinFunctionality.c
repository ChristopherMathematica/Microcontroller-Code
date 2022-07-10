#include "CoinFunctionality.h"
#include "lcd.h"
#include "servo.h"
#include "RGBLED.h"
#include "LEDs.h"
#include "strain_gauge.h"
#include <stdio.h>
    int count;
    
int SortCoin(unsigned long int weightVoltage){
char s[120];
if((weightVoltage > 7100) && weightVoltage < 7660 ){//Penny 
    tricolorled(3);
    FullRotationMotorCCW();
    sprintf(s,"Penny: %u",weightVoltage);
    putsLCD(s);
    delay_ms(600);
    clrLCD();
    count = 1;
    return count;
}
if((weightVoltage > 4400) && weightVoltage < 5100 ){ //Nickle
    tricolorled(6);
    FullRotationMotorCCW();
    sprintf(s,"Nickle: %u",weightVoltage);
    putsLCD(s);
    delay_ms(300);
    clrLCD();
    count = 1;
    return count;
}
if ((weightVoltage > 7700) && (weightVoltage < 8009)){ //Dime
    tricolorled(7);
    FullRotationMotorCCW();
    sprintf(s,"Dime: %u",weightVoltage);
    putsLCD(s);
    delay_ms(300);
    clrLCD();
    count = 1;
    return count;
} 
if((weightVoltage > 3500)&& (weightVoltage < 4300) ){ //Quarter
    tricolorled(5); 
    FullRotationMotorCCW();
    sprintf(s,"Quarter: %u",weightVoltage);
    putsLCD(s);
    delay_ms(300);
    clrLCD();
    count = 1;
    return count;
} 
if((weightVoltage > 9600) && (weightVoltage < 10600)){//Nothing Value 
    tricolorled(4);        //This was the best range of numbers to sort coins with
    MotorStop();
    sprintf(s,"Nothing On Plate");
    putsLCD(s);
    initLED();
    LEDtrail();;
    delay_ms(300);
    clrLCD();
} else{ //Rejects foreign coins
   MultiColored();
   FullRotationMotorCW();
   sprintf(s,"Foreign: %u",weightVoltage);
   putsLCD(s);
   delay_ms(300);
   clrLCD();
   count = 1;
    return count;
}

}
void DisplayGaugeValue(void){ //return gauge value later
        Init_gauge();
        char s[120];
        unsigned long int a;
        clrLCD();
        a=read_gauge()-710500;
        sprintf(s,"%u",a);
        putsLCD(s);
        delay_ms(50);
}

unsigned long int GetGaugeValue(void){ //Reduces the size of the unsigned long int
       Init_gauge();
       unsigned long int j = read_gauge();
       return j - 16710496;
}
