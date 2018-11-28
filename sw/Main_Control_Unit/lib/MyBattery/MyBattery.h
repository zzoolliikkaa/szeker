#include <Battery.h>

#define BATTERY_PIN A0

extern Battery battery;
extern uint8_t battery_percentage;
extern char battery_percentage_formated[18];


uint8_t Battery_Setup();
uint8_t Battery_Acq();
uint8_t Battery_Mng();
