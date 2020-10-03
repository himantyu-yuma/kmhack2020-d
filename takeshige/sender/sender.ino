#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
 
const uint16_t kIrLed = 4;
IRsend irsend(kIrLed);
 

uint16_t rawData_ON[199] = {4386, 4442,  524, 1630,  524, 1630,  526, 552,  524, 552,  524, 552,  524, 554,  524, 1630,  524, 552,  524, 552,  524, 554,  524, 1630,  526, 1628,  526, 1628,  526, 1628,  524, 552,  524, 1630,  526, 552,  524, 1628,  524, 1630,  524, 1630,  524, 1630,  524, 554,  524, 1578,  574, 1580,  576, 1628,  524, 552,  524, 554,  524, 552,  524, 554,  522, 1630,  526, 552,  522, 554,  522, 1630,  524, 1630,  524, 1628,  524, 552,  524, 554,  522, 554,  524, 552,  524, 552,  524, 552,  524, 552,  524, 554,  524, 1630,  522, 1630,  524, 1630,  524, 1628,  524, 1578,  576, 5230,  4386, 4442,  524, 1630,  522, 1630,  524, 554,  522, 554,  522, 554,  524, 552,  522, 1632,  524, 554,  522, 554,  522, 554,  524, 1630,  524, 1578,  576, 1630,  524, 1630,  524, 554,  522, 1630,  522, 554,  522, 1630,  524, 1630,  524, 1630,  522, 1632,  526, 552,  522, 1630,  522, 1632,  522, 1584,  570, 554,  522, 554,  522, 554,  522, 554,  522, 1632,  524, 554,  522, 556,  520, 1632,  520, 1582,  574, 1582,  570, 556,  522, 554,  522, 554,  520, 556,  520, 556,  522, 556,  522, 554,  520, 556,  520, 1632,  522, 1632,  522, 1632,  522, 1578,  576, 1630,  522};  
uint16_t rawData_ON2[299]={4386, 4398,  570, 1630,  524, 1630,  526, 552,  522, 554,  522, 554,  522, 554,  520, 1632,  524, 552,  524, 554,  522, 554,  522, 1630,  526, 1628,  524, 1630,  526, 1630,  524, 552,  524, 1630,  526, 552,  522, 554,  522, 1630,  526, 1628,  524, 1630,  524, 1630,  524, 1630,  526, 1628,  526, 1628,  524, 1630,  526, 552,  524, 554,  522, 554,  522, 554,  522, 554,  522, 554,  522, 554,  524, 552,  524, 552,  522, 554,  522, 554,  522, 554,  522, 554,  522, 554,  522, 1630,  526, 1628,  526, 1628,  520, 1634,  524, 1630,  524, 1582,  572, 1580,  574, 1582,  572, 5230,  4388, 4440,  524, 1634,  520, 1630,  524, 552,  524, 554,  522, 554,  522, 554,  522, 1630,  526, 552,  524, 552,  522, 554,  522, 1630,  526, 1628,  526, 1584,  570, 1586,  568, 552,  524, 1628,  526, 552,  524, 554,  522, 1630,  524, 1630,  524, 1630,  524, 1630,  526, 1628,  526, 1628,  526, 1628,  526, 1630,  524, 552,  522, 554,  522, 554,  522, 554,  522, 556,  522, 556,  522, 554,  522, 554,  522, 554,  522, 556,  522, 554,  522, 556,  522, 554,  524, 554,  522, 1630,  526, 1628,  524, 1630,  524, 1630,  524, 1628,  526, 1628,  526, 1628,  524, 1630,  524, 5228,  4388, 4442,  524, 1628,  526, 1628,  524, 554,  522, 1630,  524, 554,  522, 1630,  526, 552,  522, 1630,  524, 554,  526, 1628,  524, 552,  522, 1632,  524, 552,  522, 554,  522, 556,  520, 556,  522, 554,  522, 554,  520, 556,  522, 556,  522, 554,  520, 556,  522, 554,  522, 554,  520, 556,  524, 554,  520, 556,  520, 1632,  524, 554,  522, 554,  522, 554,  520, 556,  522, 554,  522, 554,  520, 556,  520, 556,  520, 556,  520, 556,  522, 554,  524, 552,  520, 556,  520, 556,  520, 1632,  522, 1632,  524, 554,  522, 1630,  526, 552,  522, 1630,  524};  

void setup() {

  pinMode(4, OUTPUT); 
  

  irsend.begin();
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("Start IRsend");
  delay(10000);
}
 
void loop() {
 // Serial.println("ON");

  byte var = Serial.read();
 
   
switch (var) {
    case '1':
   irsend.sendRaw(rawData_ON, 199, 38);  // Send a raw data capture at 38kHz.
  
    case '16':
    irsend.sendRaw(rawData_ON2, 299, 38);  // Send a raw data capture at 38kHz.
}
    delay(1000); 

    
  //delay(1000);
  //if (Serial.read()=='1'){
 // irsend.sendRaw(rawData_ON, 199, 38);  // Send a raw data capture at 38kHz.
  //delay(1000);
  }
  