void setup() {
  // 设置波特率为 38400
  Serial.begin(9600);
  pinMode(11, OUTPUT);
}

void loop() {
  while(Serial.available())
  {
    char c=Serial.read();
      if(c=='1')
      {
        Serial.println("BT is ready!");
        // 返回到手机调试程序上
        Serial.write("Serial--13--high");
        digitalWrite(13, HIGH);
      }
     if(c=='2')
     {
       Serial.write("Serial--13--low");
       digitalWrite(13, LOW);
     }
  }
}
