#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <elapsedMillis.h>
#include <EEPROM.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define CLK 10
#define DT 11
#define SW 12

#define DHTTYPE DHT22

#define DHTPIN 7

//when click is 1 should counter reset back to 0?
elapsedMillis debouce;

elapsedMillis reading;

uint8_t currentCLK;

uint8_t lastCLK;

int8_t counter = 0;

uint8_t buttonState;

uint8_t lastButtonState = 0;

uint8_t debouceDelay = 50;

uint8_t click = 0;

uint8_t menuLocation = 0;

uint8_t menuLength = 10;

uint8_t selectedSpool = 0;

uint8_t currentSpool = 0;

float temp = 0;
float humidity = 0;

DHT dht (DHTPIN, DHTTYPE);

uint8_t maxSpools = 20;

uint16_t readingDelay = 3000;

struct spool
{

  char name[16];
  uint16_t weight;

};

spool storedSpools[20];


#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)----------------------CHANGE 4 to -1 -----------
#define SCREEN_ADDRESS 0x3c ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32--------------CHANGE 0x3D to 0X3c-------
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void setup() {
scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  
  //Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

    pinMode(CLK, INPUT_PULLUP);

    pinMode(DT, INPUT_PULLUP);

    pinMode(SW, INPUT_PULLUP);

    lastCLK = digitalRead(CLK);

    reading = 0;

    dht.begin();
    display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();        

}

void loop() {

  if(menuLocation == 0) {

    menuLength = 10;

    if(reading >= readingDelay) {

      Serial.println("Readings:");

      temp = dht.readTemperature(true);

      humidity = dht.readHumidity();
      display.setTextSize(1);             // Normal 1:1 pixel scale
      display.setTextColor(SSD1306_WHITE);        // Draw white text
      display.setCursor(10,0);             //(0, 0) = Start at top-left corner (0,10) = center
        
      if (scale.is_ready()) {
        long reading = (scale.read()-122600)/(-1080);

        display.clearDisplay();
        Serial.print("HX711 reading before if statements: ");
        Serial.println(reading);
        //--------------MAKING THE DISPLAY ONLY SHOW A MAX OF 1000g-------------------
        //this code is still incomplete (need to hard code extra weight of the stand and the spool thats not the pla cylinder
        int spoolStand = 86;
        int spoolCyl = 0;
        reading = reading - (spoolStand + spoolCyl);
        if (reading > 1000){//to catch if the reading is reading over 1000g
          int extra = reading - 1000;
          reading = reading - extra;
          }
        if(reading <= 0){//to catch if there's a negative value as the reading
            reading = 0;
          }
        //--------------------------------------------------------------------------

        display.print(F("Spool Weight: "));
        display.print(reading);
        display.println(F("g"));
        
        display.setCursor(10,10);
        display.print(F("Temp: "));
        display.print(temp);
        display.println(F("F: "));

        display.setCursor(10,20);
        display.print(F("Humidity: "));
        display.print(humidity);
        display.print(F("%: "));

      } else {
        Serial.println("HX711 not found.");
      }

      reading = 0;

    }

    if(click == 1) {

      menuLocation = 1;

      counter = 0;

      click = 0;

    }

  } else if (menuLocation == 1) {

    menuLength = maxSpools + 1;

    if(counter != (menuLength - 1)) {

      display.clearDisplay();

      display.setCursor(0, 10);
      display.print("Spool ");
      display.print(counter);

    } else {

      display.clearDisplay();
      display.setCursor(0, 10);
      display.print("Back");

    }

    if((counter == (menuLength - 1)) && (click == 1)){

      menuLocation = 0;

      counter = 0;

      click = 0;

    } else if(click == 1) {

      currentSpool = counter;

      menuLocation = 2;

      counter = 0;

      click = 0;

    }

  } else if (menuLocation == 2) {

    menuLength = 3;

    if(counter == 0) {

      display.clearDisplay();

      display.setCursor(0, 10);
      display.print("Set as default");

    } else if (counter == 1) {

      display.clearDisplay();

      display.setCursor(0, 10);
      display.print("Calibrate");

    } else {

      display.clearDisplay();

      display.setCursor(0, 10);
      display.print("Back");

    }

    if((counter == (menuLength - 1)) && (click == 1)) {

      menuLocation = 1;

      counter = 0;

      click = 0;

    } else if((counter == 1) && (click == 1)) {

      menuLocation = 3;

      counter = 0;

      click = 0;

    } else if ((counter == 0) && (click == 1)) {

      selectedSpool = currentSpool;

      click = 0;

    }

  } else if (menuLocation == 3) {

    menuLength = 3;

    if(counter == 0) {

      display.clearDisplay();
      display.setCursor(0, 10);
      display.print("Full spool cali");

    } else if (counter == 1) {

      display.clearDisplay();
      display.setCursor(0, 10);
      display.print("Empty Spool cali");

    } else {

      display.clearDisplay();
      display.setCursor(0, 10);
      display.print("Back");

    }


    if((counter == (menuLength - 1)) && (click == 1)) {

      menuLocation = 1;

      counter = 0;

      click = 0;

    } else if ((counter == 0) && (click == 1)) {

      delay(100);

      long reading = (scale.read()-122600)/(-1080);

      delay(100);

      storedSpools[currentSpool].weight = reading - 1000;

    } else if ((counter == 1) && (click == 1)) {

      delay(100);

      long reading = (scale.read()-122600)/(-1080);

      delay(100);

      storedSpools[currentSpool].weight = reading;
      
    }

  }

  

  currentCLK = digitalRead(CLK);

  if((currentCLK != lastCLK) && currentCLK == 1) {

    if(digitalRead(DT) == currentCLK) {

      counter++;

    } else {

      counter--;

    }

  }

  if(counter >= menuLength) {

      counter = 0;

  } else if (counter < 0) {

      counter = menuLength;

  }



  buttonState = !digitalRead(SW);

  if(buttonState != lastButtonState) {

      debouce = 0;

  }

  if(buttonState != lastButtonState) {

    if(buttonState == 1){

      click = 1;

    }
      

  }

  lastButtonState = buttonState;

  lastCLK = currentCLK;


  display.display();
  //delay(1000);

}
