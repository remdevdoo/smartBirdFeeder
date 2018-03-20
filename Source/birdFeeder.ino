// Platform, Sensors and Communication.

#include <MKRWAN.h>

LoRaModem modem;

#include "arduino_secrets.h"

// Defines constant variables, pins
#define TRIG_PIN 0
#define ECHO_PIN 1

// defines variables
float duration;
float distance;

void setup() {

// Put your setup code here, to run once:

pinMode(LED_BUILTIN, OUTPUT);
pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input

    Serial.begin(115200);
 // while (!Serial);
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
// Join The Things Network
  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
   digitalWrite(LED_BUILTIN, HIGH); 
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
 //   while (1) {}
  }

  // Set poll interval to 60 secs.
  modem.minPollInterval(60);
  // NOTE: independently by this setting the modem will
  // not allow to send more than one message every 2 minutes,
  // this is enforced by firmware and can not be changed.
  
}

void loop() {

  // Start distance measurement.
  // Clears the trigPin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);

// Calculating the distance
  distance = (duration/2) / 29.1;

// Determine message by the distance and send message
  byte msg = 0;

  if(distance > 0 && distance <= 10.00){
    msg = 100;
    Serial.print("Bird feeder is vol (100%) ");
    Serial.print(distance); 
    Serial.println();
  }
  else if(distance > 10.00 && distance <= 11.30){
    msg = 90;  
    Serial.print("Bird feeder is 90%  ");
    Serial.print(distance); 
    Serial.println();
   }
   else if(distance > 11.30 && distance <= 12.60){
    msg = 80;
    Serial.print("Bird feeder is 80%  ");
    Serial.print(distance); 
    Serial.println();
  }
  else if(distance > 12.60 && distance <= 13.90){
    msg = 70;
    Serial.print("Bird feeder is 70%  ");
    Serial.print(distance); 
    Serial.println();
}
  else if(distance > 13.90 && distance <= 15.20){
    msg = 60;
    Serial.print("Bird feeder is 60%  ");
    Serial.print(distance); 
    Serial.println();
}
  else if(distance > 15.20 && distance <= 16.50){
    msg = 50;  
    Serial.print("Bird feeder is 50%  ");
    Serial.print(distance); 
    Serial.println(" ");
}
  else if(distance > 16.50 && distance <= 17.80){
    msg = 40;
    Serial.print("Bird feeder is 40%  ");
    Serial.print(distance); 
    Serial.println(" ");

}
  else if(distance > 17.80 && distance <= 19.10){
    msg = 30;
    Serial.print("Bird feeder is 30%  ");
    Serial.print(distance); 
    Serial.println(" ");

}
  else if(distance > 19.10 && distance <= 20.40){
    msg = 20;
    Serial.print("Bird feeder is 20%  ");
    Serial.print(distance); 
    Serial.println(" ");

}
  else if(distance > 20.40 && distance < 23.00){
    msg = 10;
    Serial.print("Bird feeder is 10%  ");
    Serial.print(distance); 
    Serial.println(" ");

}
  else{
    msg = 0;
    Serial.print("Bird feeder is leeg  ");
    Serial.print(distance); 
    Serial.println();
}
    //Call send message function.
    sendMessage(msg);
    //Loop every hour.
    delay(3600000);
}


// send message to The Things Network in bytes.
void sendMessage(byte msg){
  modem.beginPacket();
  modem.write(msg);
  int err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!"); 
  } else {
    Serial.println("Error sending message :(("); 
  }
}


