#include <xc.h>
#include "lcd.h"
#include "Prompts.h"

void CalibratePrompt(void){
    char String0[19];
    sprintf(String0,"..Calibrate Motor?");
    putsLCD(String0);
}
void OpeningPrompt(void){
   char String1[11], String2[10];
   sprintf(String1,"Do you want");
   putsLCD(String1);
   secondLine();
   sprintf(String2,"to start?");
   putsLCD(String2);
}
void ExitingPrompt(void){
    char String3[11], String4[10];
    sprintf(String3,"..Press Again");
    putsLCD(String3);
    secondLine();
    sprintf(String4,"to Exit");
    putsLCD(String4);
}

void ThankYouPrompt(void){
    char String5[19], String6[19];
    sprintf(String5,"..Thank You");
    putsLCD(String5);
    secondLine();
    sprintf(String6,"For Using!");
    putsLCD(String6);
}
void WiperPrompt(void){
    char String6[19], String7[19];
    sprintf(String6,"Initiating");
    putsLCD(String6);
    secondLine();
    sprintf(String7,"Wiper Mode");
    putsLCD(String7);    
}