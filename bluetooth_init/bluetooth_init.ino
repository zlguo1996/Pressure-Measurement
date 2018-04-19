#include <SoftwareSerial.h>

// Pin10为RX，接HC05的TXD
// Pin11为TX，接HC05的RXD
SoftwareSerial BT(10, 11);
char val;

void setup() {
  Serial.begin(9600); 
  Serial.println("BT is ready!");
  
  // HC06
  BT.begin(9600);
}

void loop() {
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }

  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }
}

