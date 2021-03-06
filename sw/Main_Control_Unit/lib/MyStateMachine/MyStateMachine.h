/**
* @file C:\Arduino\Szeker\lib\MyStateMachine\MyStateMachine.h
* @author Balint Zoltan
* @date 27 Nov 2017
* @copyright 2017 Balint Zoltan
* @brief <brief>
*
*/
#define MEASURE_X       1
#define SLEEP_TIMER     400    /* Real Time = SLEEP_TIMER * 300 ms ( Task cycle) */
//#define WAKE_UP_PIN     2
#define SENSOR_PIN_1      3
#define SENSOR_PIN_2      2
#define HEART_BEAT_LED_PIN       13

#define RATE_ADDRESS    1
#define DEBUG_STATE_MACHINE
void StateMachine_Setup();
void MyStateMachine_Mng();
