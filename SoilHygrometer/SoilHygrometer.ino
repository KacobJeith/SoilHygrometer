
#include "HeepDeviceDefinitions.h"

#define WATERME_PIN 14
#define ANALOG_PIN A0

unsigned long previousMillis = 0;

void InitializeControlHardware(){
  pinMode(WATERME_PIN,INPUT);
  pinMode(ANALOG_PIN,INPUT);
}

int ReadWaterMe(){
  int currentSetting = digitalRead(WATERME_PIN);
  SetControlValueByName("DigitalWaterMe",currentSetting);
  return currentSetting;
}

int ReadAnalog(){
  int currentSetting = analogRead(ANALOG_PIN) / 10;
  SetControlValueByName("Moistness", currentSetting);

  if (currentSetting >  GetControlValueByName("TriggerValue")) {
    SetControlValueByName("AnalogWaterMe", true);
  } else {
    SetControlValueByName("AnalogWaterMe", false);
  }
  
  Serial.print("Moistness: ");
  Serial.println(currentSetting);
  
  return currentSetting;
}

void setup()
{

  Serial.begin(115200);
  InitializeControlHardware();

  std::string SSID1 = "ssid";
  std::string Password1 = "password";
  AddWiFiSettingsToMemory(&SSID1[0], SSID1.length(), &Password1[0], Password1.length(), deviceIDByte, 0);
  
  AddOnOffControl("DigitalWaterMe",HEEP_OUTPUT,0);
  AddOnOffControl("AnalogWaterMe",HEEP_OUTPUT,0);
  AddRangeControl("Moistness",HEEP_OUTPUT, 100, 0, 0);
  
  AddRangeControl("TriggerValue",HEEP_INPUT, 100, 0, 70);
  AddRangeControl("ReadFrequency",HEEP_INPUT, 100, 0, 3);
  
  StartHeep(heepDeviceName, 12);

}

void loop()
{
  PerformHeepTasks();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000 * GetControlValueByName("ReadFrequency")) {
    previousMillis = currentMillis;

    ReadWaterMe();
    ReadAnalog();
    
  }
  
  

}
