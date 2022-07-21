/* Name: Christopher Yonek
 * Course: ELEG298
 * Assignment: Final Project IoT
 * Date: 5/1/2022
 */
#include "Arduino.h"
#include <SoftwareSerial.h>             //Allows us to use two GPIO pins for a second UART
#include<Wire.h>                        //Allows for communication with MCP9808
#define Addr 0x18                       // MCP9808 I2C address is 0x18(24)
String espData(String, const int, boolean);
SoftwareSerial espSerial(11,10);        //Create software UART to talk to the ESP8266
String IO_USERNAME = "cyonek";          //paste your Adafruit IO username here
String IO_KEY = "aio_qqNV03iFjscqTJcmhGvWw1l9ZMbN"; //paste your Adafruit IO key here
String WIFI_SSID = ":)";      //Only need to change if using other network, eduroam won't work with ESP8266
String WIFI_PASS = "howdoutypethisface";                //Blank for open network
float num = 1.0;                        //Counts up to show upload working

void setup()
{
  Serial.begin(9600);   // set up serial monitor with 9600 baud rate 
  espSerial.begin(9600);    // set up software UART to ESP8266 @ 9600 baud rate
  Serial.println("setting up");
  String resp = espData("get_macaddr",2000,true); //get MAC address of 8266
  resp = espData("wifi_ssid="+WIFI_SSID,2000,true); //send Wi-Fi SSID to connect to
  resp = espData("wifi_pass="+WIFI_PASS,2000,true); //send password for Wi-Fi network
  resp = espData("io_user="+IO_USERNAME,2000,true); //send Adafruit IO info
  resp = espData("io_key="+IO_KEY,2000,true);
  resp = espData("setup_io",15000,true);      //setup the Adafruit IO connection
  if(resp.indexOf("connected") < 0) {
     Serial.println("\nAdafruit IO Connection Failed");
    while(1);
  }
  resp = espData("setup_feed=1,Temperature",2000,false); //start the data feed

  Wire.begin(); // Start I2C default baud rate 9600
  Wire.beginTransmission(Addr); // Configure to I2C address
  Wire.write(0x01); // Continuous conversion mode, Power-up default
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission(); // Stop I2C 
  
  Wire.beginTransmission(Addr); // Start I2C
  Wire.write(0x08); // Write to resolution rgister
  Wire.write(0x03); // Resolution = 2^-4 / C
  Wire.endTransmission(); // Stop I2C
  Serial.println("------ Setup Complete ----------");
}

void loop()
{
  unsigned int rawTemp[2];
  // Starts I2C communication
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x05);
  // Stop I2C transmission
  Wire.endTransmission();
  Wire.requestFrom(Addr, 2);
  if(Wire.available() == 2){  // Read 2 bytes
 
    rawTemp[0] = Wire.read();   // temp MSB, temp LSB
    rawTemp[1] = Wire.read();
  }
  
  int fullTemp = ((rawTemp[0] & 0x1F) * 256 + rawTemp[1]);   // Convert the data to 13-bits
  if(fullTemp > 4095)
  {
    fullTemp -= 8192;
  }
  float cTemp = fullTemp * 0.0625;
  float fTemp = cTemp * 1.8 + 32;
  delay(2000);      // Wait 5 seconds between uploads
  Serial.println("The Temperature is: ");
  String respTemp = espData("send_data=1,"+String(fTemp),2000,false); //send feed to cloud
}

String espData(String command, const int timeout, boolean debug) {
  String response = "";
  espSerial.println(command); //send data to ESP8266 using serial UART
  long int time = millis();
  while ( (time + timeout) > millis()) {  //wait the timeout period sent with the command
    while (espSerial.available()) { //look for response from ESP8266
      char c = espSerial.read();
      response += c;
      Serial.print(c);  //print response on serial monitor
    }
  }
  if (debug) {
    Serial.println("Resp: "+response);
  }
  response.trim();
  return response;

}
