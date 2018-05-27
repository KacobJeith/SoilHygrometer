#include <Heep_API.h>
#include "ESP8266_HeepComms.h"
#include "ESP8266_NonVolatileMemory.h"
#include "Arduino_Timer.h" 
heepByte deviceIDByte [STANDARD_ID_SIZE] = {0xe0, 0x0e,0xd0, 0x0d};
uint8_t mac[6] = {0x0a, 0xb0, 0x0c, 0xd0, 0x0e, 0xf0};
unsigned char clearMemory = 1;
char* heepDeviceName = "SoilHygrometer";
