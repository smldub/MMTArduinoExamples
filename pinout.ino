/*
How to activate a pin on the ESP32
This is a comment, and is ignored by the microcontroller
*/
// This is also a comment

// Loading other code that allows us to control the microcontroller
#include <iostream>

// While named 'pin4' here, you can call the variable whatever you
// want as long as you change it throughout the rest of the code
// This is the pin on the microcontroller board that we want
// to turn on and off
const int pin4 = 4; 

// This function only happens once write after we compile 
// the code on the device. It sets everything up hence the name
void setup() {
    // Defining pin 4 as our output
    pinMode(pin4,OUTPUT);
}

// This function happens over and over again after setup is finished
void loop() {
    delay(500);              // A 500ms wait before next command
    digitalWrite(pin4,HIGH); // Telling the pin to turn on (HIGH)
    delay(2000);             // Keeping pin on for 2 seconds
    digitalWrite(pin4,LOW);  // Turning off (LOW) the pin
}
    
