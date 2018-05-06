#include <SoftwareSerial.h>
#include <SerialCommand.h>

int fsrPin = 17;
int fsrReading;

int voltage = 5000; // 5V
int resistance = 10000; // 10K

SerialCommand SCmd;

// 计算压力
long calcForce(int val){
  int fsrVoltage;
  unsigned long fsrResistance;
  unsigned long fsrConductance;
  long fsrForce;
  
  // 获得电阻的电压
  fsrVoltage = map(val, 0, 1023, 0, voltage);

  // 计算传感器电阻
  // The voltage = Vcc * R / (R + FSR)
  // => FSR = ((Vcc - V) * R) / V
  fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
  fsrResistance *= 10000;                // 10K resistor
  fsrResistance /= fsrVoltage;

  // 计算电导率
  fsrConductance = 1000000;           // we measure in micromhos so 
  fsrConductance /= fsrResistance;

  // 近似计算压力
    if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;    
    } else {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;         
    }

    return fsrConductance;
}

// 处理串口数据
void setVoltage(){
  char* arg;
  arg = SCmd.next();
  if(arg!=NULL){
    int number = atoi(arg);
    voltage = number;
    Serial.print("set voltage: ");
    Serial.println(number);
  }
}
void setResistance(){
  Serial.println("hi");
  char* arg;
  arg = SCmd.next();
  if(arg!=NULL){
    int number = atoi(arg);
    resistance = number;
    Serial.print("set resistance: ");
    Serial.println(number);
  }
}
void unrecognized()
{
  Serial.println("What?"); 
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  SCmd.addCommand("setV", setVoltage);
  SCmd.addCommand("setR", setResistance);
  SCmd.addDefaultHandler(unrecognized);
}

void loop() {
  fsrReading = analogRead(fsrPin);
  Serial.println(calcForce(fsrReading));
  
  SCmd.readSerial();
}
