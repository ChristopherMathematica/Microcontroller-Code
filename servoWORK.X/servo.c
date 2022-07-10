# include <p32xxxx.h>
# include "servo.h"
# include "lcd.h"
#include <stdio.h>
#include <stdbool.h>
#include "pushbutton.h"

void initServo(void)
{
  TRISBbits.TRISB8 = 0;  
  TRISAbits.TRISA15 = 0;  
  ANSELBbits.ANSB8 = 0;  //Disable analog functionality on RB8
   RPB8R = 0x0B; // 1011 = OC5 RB8 is mapped to OC5
   RPA15R = 0x0B; // 1011 = OC4 RA15 is mapped to OC4
   OC4R=100;     //Output compare #4 100
   OC4RS=5000;
   
   OC5R=100;     //Output compare #5 100
   OC5RS=2350;

   OC4CON=0x800D;
   OC5CON=0x800D;
   T3CON=0x0040;
   PR3=45000;
   T3CON=0x8040;
}

void MotorStop(void){
   RPB8R = 0x00; // 1011 = OC5 RB8 is mapped to OC5
   RPA15R = 0x00; // 1011 = OC4 RA15 is mapped to OC4
   OC4CON=0x0000;
   OC5CON=0x0000;
   T3CON=0x0000;
   PR3=0;
   T3CON=0x0000;
   delay_ms(1);
}

void MotorCCW(void){
        delay_ms(1);
        initServo(); //Starts Servo
        OC4RS= 3750; //Output Compare set to CCW
        OC5RS= 3750;
        delay_ms(400);
        MotorStop();
}
void MotorCW(void){
        delay_ms(1);;
        initServo();
        delay_ms(400);
        MotorStop();  
}

void HalfRotationMotorCCW(void){
        initServo();
        OC4RS= 3750; //Output Compare set to CCW
        OC5RS= 3750;
        delay_ms(148);
        MotorStop();  
}
void FullRotationMotorCCW(void){
        initServo();
        OC4RS= 3750; //Output Compare set to CCW
        OC5RS= 3750;
        delay_ms(298);
        MotorStop();  
}
void HalfRotationMotorCW(void){ //Function to rotate servo 180 Degrees
    initServo();
    delay_ms(81);
    delay_us(900);
    MotorStop();
}
void FullRotationMotorCW(void){ //Function to rotate servo 360 Degrees
        initServo();
        delay_ms(185);
        MotorStop();  
}
void ShortMotorCCW(void){ //Function to turn servo in small segments 
        initServo();      //for the button to be responsive 
        OC4RS= 3750; 
        OC5RS= 3750;
        delay_ms(15);
        MotorStop();     
}

void WiperMode(void){ //Function to rotate servo back and fourth 3 times
    HalfRotationMotorCW();
    delay_ms(1);
    HalfRotationMotorCCW();
    delay_ms(1);
    HalfRotationMotorCW();
    delay_ms(1);
    HalfRotationMotorCCW();
    delay_ms(1);
    HalfRotationMotorCW();
    delay_ms(1);
    HalfRotationMotorCCW();
    delay_ms(1);
}