
#include "HeepDeviceDefinitions.h"

#define WATERME_PIN 14

void InitializeControlHardware(){
  pinMode(WATERME_PIN,INPUT);
}

int ReadWaterMe(){
  int currentSetting = digitalRead(WATERME_PIN);
  SetControlValueByName("WaterMe",currentSetting);
  return currentSetting;
}

void setup()
{

  Serial.begin(115200);
  InitializeControlHardware();
  AddOnOffControl("WaterMe",HEEP_OUTPUT,0);
  StartHeep(heepDeviceName, 2);

}

void loop()
{
  PerformHeepTasks();
  ReadWaterMe();

}