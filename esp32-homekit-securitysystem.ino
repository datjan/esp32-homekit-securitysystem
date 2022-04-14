/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2020 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/
/*
 * 
ESP32 -> Potential free contact (state away)
3V3 -> Potential free contact
GPIO16 -> Potential free contact
GPIO16 -> 10kOhm -> GND

ESP32 -> Potential free contact (state triggered)
3V3 -> Potential free contact
GPIO17 -> Potential free contact
GPIO17 -> 10kOhm -> GND

ESP32 -> Potential free contact (state night)
3V3 -> Potential free contact
GPIO18 -> Potential free contact
GPIO18 -> 10kOhm -> GND

ESP32 -> Potential free contact (state stay)
3V3 -> Potential free contact
GPIO19 -> Potential free contact
GPIO19 -> 10kOhm -> GND

*/

#include "HomeSpan.h"         // https://github.com/datjan/HomeSpan  (fork from https://github.com/HomeSpan/HomeSpan)
#include "DEV_Identify.h"  
#include "DEV_SecuritySystems.h"  

// Pins
int pinStatusAway = 16;
int pinStatusTriggered = 17;
int pinStatusNight = 18;
int pinStatusStay = 19;



void setup() {                // Your HomeSpan code should be placed within the standard Arduino setup() function
 
  Serial.begin(115200);       // Start a serial connection so you can receive HomeSpan diagnostics and control the device using HomeSpan's Command-Line Interface (CLI)

  // Pins to Input
  pinMode(pinStatusAway, INPUT_PULLDOWN); // Default state LOW
  pinMode(pinStatusTriggered, INPUT_PULLDOWN); // Default state LOW
  pinMode(pinStatusNight, INPUT_PULLDOWN); // Default state LOW
  pinMode(pinStatusStay, INPUT_PULLDOWN); // Default state LOW
  

  homeSpan.begin(Category::SecuritySystems,"ESP32 Security");   // initializes a HomeSpan device named "HomeSpan Lightbulb" with Category set to Lighting
      
  new SpanAccessory();                                                          
    new DEV_Identify("Security System","DATJAN","datjan.esp32.001","esp32-homekit-securitysystem","1.0",0);
    new Service::HAPProtocolInformation();
      new Characteristic::Version("1.1.0");
    new DEV_SecuritySystem(); 

} // end of setup()

//////////////////////////////////////

void loop(){

  // The code in setup above implements the Accessory Attribute Database, but performs no operations.  HomeSpan itself must be
  // continuously polled to look for requests from Controllers, such as the Home App on your iPhone.  The poll() method below is all that
  // is needed to perform this continuously in each iteration of loop()
  
  homeSpan.poll();         // run HomeSpan!
  
} // end of loop()

// Congratulations!  You've created your first HomeSpan sketch, ready to be uploaded to your ESP32 board and paired with HomeKit.
//
//
