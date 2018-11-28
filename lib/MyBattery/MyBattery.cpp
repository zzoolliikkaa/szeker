#include <MyBattery.h>

Battery battery(3000, 4200, A0);
uint8_t  battery_percentage = 0;
char battery_percentage_formated [18];

uint8_t Battery_Setup()
{
        battery.begin(5000, 1.0);
        battery_percentage = battery.level();
        sprintf (battery_percentage_formated, "%3i", battery_percentage);
        return 0;
}

uint8_t Battery_Acq()
{
        return 0;
}

uint8_t Battery_Mng()
{
        return 0;
}
