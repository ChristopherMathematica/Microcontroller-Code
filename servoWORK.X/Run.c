# include <p32xxxx.h>
# include <xc.h>
#include <sys/attribs.h>
# include "config_bits.h"   
#include "strain_gauge.h"
#include "lcd.h"
#include "CoinFunctionality.h"
#include "pushbutton.h"
#include "servo.h"
#include "LEDs.h"
#include "SWTCH.h"
#include "RGBLED.h"
#include "Prompts.h"

void InitPeriphals(void){ //Initalizes all device periphals
Init_gauge();
initLCD();
InitTricoloredLED();
InitButton();
initSwitch();
initLED();
  
}

void run(void){
InitPeriphals();
OpeningPrompt(); // "Do you want to start?"
AllLEDsOn();
int counter=0;  //counter of coins starts at 0
do{
    delay_ms(1);
} while(!buttonValue(0)); //Press button 0 to continue
clrLCD();
AllLEDsOff(); //All LEDs from the opening menu shut off
while (1){
counter = SortCoin(GetGaugeValue()) + counter; //Nested function to keep track of
char String10[18];                             //how many coins were counted.

    if(buttonValue(1)){
        ExitingPrompt(); //"Do you want to exit?"
        delay_ms(100);
        clrLCD();
    }

        if(buttonValue(1)){ //Hit button 1 again to break the infinite loop
           ThankYouPrompt(); //"Thank you for using!"
           delay_ms(200);
           break;
        }
      if(buttonValue(2)){ 
        CalibratePrompt(); //"Do you want to calibrate the motor?"
        delay_ms(200);
        clrLCD();
        while(buttonValue(2)){
            AllLEDsOn();
            tricolorled(6);  //Button 2 for continously spinning the 
            ShortMotorCCW(); //servo counterclockwise
            AllLEDsOff();
        }
      }
    if(SwitchValue(0)){ //Switch 0 causes the motor to
    LEDOddOrder();      //rotate 180 degrees CW and CCW
    LEDOddOrder();      //And the LEDs to flash in sporadic order
    WiperPrompt();
    delay_ms(50);
    clrLCD();
    WiperMode();
    }
if(SwitchValue(1)){ //Switch 1 enables the LCD to display
clrLCD();           //the number of coins counted
sprintf(String10," No. of Coins: %d ",counter);
putsLCD(String10);
}
if(SwitchValue(2)){ //Display an RGB light show every loop
    LightShow();    // if switch 2 is on
}
}
}