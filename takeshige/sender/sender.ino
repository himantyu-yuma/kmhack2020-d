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
    case 'o':
   irsend.sendRaw(turn_off, 199, 38);  
   break;
   
    case 's':
    irsend.sendRaw(turn_on16, 299, 38);  
     Serial.println("The current temperature is 16 degrees.");
     break;
     
    case '9':
   irsend.sendRaw(turn_on29, 299, 38);  
   Serial.println("The current temperature is 29 degrees.");
    break;
    
    case '8':
   irsend.sendRaw(turn_on28, 299, 38); 
   Serial.println("The current temperature is 28 degrees.");
   break;
   
   case '7':
   irsend.sendRaw(turn_on27, 299, 38);  
   Serial.println("The current temperature is 27 degrees.");
    break;
    
   case '6':
   irsend.sendRaw(turn_on26, 299, 38); 
   Serial.println("The current temperature is 26 degrees.");
   break;
   
   case '5':
   irsend.sendRaw(turn_on25, 299, 38); 
   Serial.println("The current temperature is 25 degrees.");
    break;
    
    case '4':
   irsend.sendRaw(turn_on24, 299, 38); 
   Serial.println("The current temperature is 24 degrees.");
    break;
    
    case '3':
   irsend.sendRaw(turn_on23, 299, 38); 
   Serial.println("The current temperature is 23 degrees.");
    break;
}
    delay(1000); 

    
 
  }
  
