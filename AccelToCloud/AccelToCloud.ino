/* Name: Christopher Yonek
 * Course: ELEG298
 * Assignment: Lab 2 Gravity Acceleration
 * Date: 3/1/2022
 */
#include "LIS3DHTR.h"
#ifdef SOFTWAREWIRE
    #include <SoftwareWire.h>
    SoftwareWire myWire(3, 2);
    LIS3DHTR<SoftwareWire> LIS;       //Software I2C
    #define WIRE myWire
#else
    #include <Wire.h>
    LIS3DHTR<TwoWire> LIS;           //Hardware I2C
    #define WIRE Wire
#endif

#include "Arduino.h"
#include <SoftwareSerial.h>              //Allows us to use two GPIO pins for a second UART
SoftwareSerial espSerial(11,10);        //Create software UART to talk to the ESP8266
String IO_USERNAME = "cyonek";   //paste your Adafruit IO username here
String IO_KEY = "aio_qqNV03iFjscqTJcmhGvWw1l9ZMbN"; //paste your Adafruit IO key here
String WIFI_SSID = ":)";      //Only need to change if using other network, eduroam won't work with ESP8266
String WIFI_PASS = "how do u type this face";                //Blank for open network
float num = 1.0;                        //Counts up to show upload working

void setup() {
  Serial.begin(9600);   // set up serial monitor with 9600 baud rate
  espSerial.begin(9600);    // set up software UART to ESP8266 @ 9600 baud rate
  Serial.println("setting up");
  String resp = espData("get_macaddr",2000,true); //get MAC address of 8266
  resp = espData("wifi_ssid="+WIFI_SSID,2000,true); //send Wi-Fi SSID to connect to
  resp = espData("wifi_pass="+WIFI_PASS,2000,true); //send password for Wi-Fi network
  resp = espData("io_user="+IO_USERNAME,2000,true); //send Adafruit IO info
  resp = espData("io_key="+IO_KEY,2000,true);
  resp = espData("setup_io",15000,true);      //setup the IoT connection
  if(resp.indexOf("connected") < 0) {
    Serial.println("\nAdafruit IO Connection Failed");
    while(1);
  }
  resp = espData("setup_feed=1,Acceleration X",2000,false); //start the data feed
  resp = espData("setup_feed=2,Acceleration Y",2000,false); //start the data feed
  resp = espData("setup_feed=3,Acceleration Z",2000,false); //start the data feed
  
  Serial.println("------ Setup Complete ----------");
  

    while (!Serial) {};
    LIS.begin(WIRE, 0x19); //IIC init
    delay(100);
    LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
}

void loop() {

  // free version of Adafruit IO only allows 30 uploads/minute, it discards everything else
  delay(2000);      // Wait 5 seconds between uploads
  Serial.println("The X-GForce is: ");
  String respX = espData("send_data=1,"+String(LIS.getAccelerationX()),2000,false); //send feed to cloud
    Serial.println("The Y-GForce is: ");
  String respY = espData("send_data=2,"+String(LIS.getAccelerationY()),2000,false); //send feed to cloud
    Serial.println("The Z-GForce is: ");
  String respZ = espData("send_data=3,"+String(LIS.getAccelerationZ()),2000,false); //send feed to cloud
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
