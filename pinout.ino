/*
* How to activate a pin on the ESP32
*/
#include <iostream>
const int pin4 = 4; //While named 'pin4' here, you can call the variable whatever you want as long as you change it throughout the rest of the code

/*This function only happens once write after we compile the code on the device. It sets everything up hence the name*/
void setup() {
    /*Defining pin 4 as our output*/ 
    pinMode(pin4,OUTPUT);
}

/*This function happens over and over again after setup is finished*/
void loop() {
    delay(500); // A 500ms wait before next command
    digitalWrite(pin4,HIGH); //Telling the pin to turn on
    delay(2000);// Keeping pin on for 2 seconds
    digitalWrite(pin4,LOW); //Turning off the pin
}
    
