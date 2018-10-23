/* 
  Basic test program, send date at the BAND you seted.
  
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  www.heltec.cn
  
  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/
//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(3, 1); // RX, TX

#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
//#include "images.h"
#include "HardwareSerial.h"

#define RX2 12
#define TX2 13

HardwareSerial Serial2(2);

//OLED pins to ESP32 GPIOs via this connecthin:
//OLED_SDA -- GPIO4
//OLED_SCL -- GPIO15
//OLED_RST -- GPIO16

SSD1306  display(0x3c, 4, 15);

String RFData = "";
String SerialData = "";
int ch;

void println_oled(String txtPrint) {
  // Print to the screen
  display.setFont(ArialMT_Plain_16); // create more fonts at http://oleddisplay.squix.ch/
  display.clear();
  display.println(txtPrint);
  // Draw it to the internal screen buffer
  display.drawLogBuffer(0, 0);
  // Display it on the screen
  display.display();
  delay(500);
}

void print_oled(String txtPrint) {
  // Print to the screen
  //Serial.println(txtPrint);
  display.setFont(ArialMT_Plain_10); // create more fonts at http://oleddisplay.squix.ch/
  display.clear();
  display.print(txtPrint);
  // Draw it to the internal screen buffer
  display.drawLogBuffer(0, 0);
  // Display it on the screen
  display.display();
  delay(500);
}

void setup() {
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high
  display.init();
  display.setLogBuffer(3, 30);
  display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10); // create more fonts at http://oleddisplay.squix.ch/
  println_oled("Started...1234567890");
    
  // Open serial communications and wait for port to open:
  Serial2.begin(9600);
  Serial.begin(115200);
  //Serial.println();
  //Serial.println();
  //while (!Serial) {
    //; // wait for serial port to connect. Needed for native USB port only
  //}
  // set the data rate for the SoftwareSerial port
  delay(50);
  Serial2.println("a03HELLO");
  Serial.println("Started...1234567890");
  }

void loop() { // run over and over
   
 while (Serial2.available()) {
    //println_oled("Incoming message..");
    //Serial.println("Incoming message..");
    //delay(50); //Allows full message to arrive before we quit the loop
    ch=Serial2.read();
    if (ch!=0) RFData+=char(ch);
  }

  if (RFData != "") {
    if (RFData.length() > 12){
      println_oled(RFData.substring(0,12));  
      Serial.println(RFData.substring(0,12));
      RFData=RFData.substring(12,RFData.length());
    }
    else{
      println_oled(RFData); 
      Serial.println(RFData);
      RFData = ""; 
    }
  }
}


