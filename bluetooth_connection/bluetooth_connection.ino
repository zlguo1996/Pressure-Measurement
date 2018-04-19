#include <SoftwareSerial.h>

// Pin10为RX，接HC05的TXD
// Pin11为TX，接HC05的RXD
SoftwareSerial BT(10, 11);
char val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  Serial.println("BT is ready!");
  
  // HC06
  BT.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BT.available()) {
    val = BT.read();
    BT.print(val);
  }
}
