/**
 * @file C:\Arduino\Szeker\lib\Sensor\Sensor.h
 * @author Balint Zoltan
 * @date 21 Nov 2017
 * @copyright 2017 Balint Zoltan
 * @brief <brief>
 *
 */
#define DIST_SENSOR_0_PIN   3
#define DIST_SENSOR_1_PIN   2


#define DEBUG_SENSOR

extern float Sensor_Value;

uint8_t Sensor_Setup();
void Sensor_Acq();
uint8_t Sensor_Mng();
