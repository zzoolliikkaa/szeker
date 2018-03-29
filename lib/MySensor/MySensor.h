/**
 * @file C:\Arduino\Szeker\lib\Sensor\Sensor.h
 * @author Balint Zoltan
 * @date 21 Nov 2017
 * @copyright 2017 Balint Zoltan
 * @brief <brief>
 *
 */
#define DIST_SENSOR_0_PIN   7
#define DIST_SENSOR_1_PIN   8
#define DIST_SENSOR_2_PIN   9
#define DIST_SENSOR_3_PIN   10
#define DIST_SENSOR_4_PIN   11

#define DEBUG_SENSOR

extern float Sensor_Value;

uint8_t Sensor_Setup();
void Sensor_Acq();
uint8_t Sensor_Mng();
