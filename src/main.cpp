/**
 * @file C:\Arduino\Szeker\src\main.cpp
 * @author Balint Zoltan
 * @date 20 Nov 2017
 * @copyright 2017 Balint Zoltan
 * @brief <brief>
 *
 */

#include <Arduino.h>
#include <main.h>
#include <jm_Scheduler.h>
#include <Page.h>
#include <MyButton.h>
#include <MySensor.h>
#include <MyStateMachine.h>

void Task_10ms();
void Task_100ms();
void Task_300ms();

jm_Scheduler Sch_10ms;
jm_Scheduler Sch_100ms;
jm_Scheduler Sch_300ms;
uint8_t Heart_Beat_LED = 0;

/**
 * @brief General Setup function for Arduino <brief>
 * @param [None]
 * @return Void
 * @details LCD Init <br>
          Task Scheduler Start <br>
          Global State Machine Start <br>
          EEPROM Read
 */
void setup()
{
  #ifdef DEBUG_MAIN
        Serial.begin(19200);
        Serial.println(" DEBUG Mode: ON " );
  #endif
        Button_Setup();
        Page_Setup();
        Sensor_Setup();
        StateMachine_Setup();
        Sch_10ms.start(Task_10ms,10000);    // 10 msec
        Sch_100ms.start(Task_100ms,100000);   // 100 msec
        Sch_300ms.start(Task_300ms,300000);   // 300 msec
  #ifdef DEBUG_MAIN
        Serial.println(" Setup end. " );
  #endif
        pinMode(HEART_BEAT_LED_PIN, OUTPUT);
}

/**
 * @brief General Loop function for Arduino  <brief>
 * @param [None]
 * @return Void
 * @details The Main function
 */
void loop()
{
        jm_Scheduler::cycle();
}

/**
 * @brief The aquisition function <brief>
 * @param [None]
 * @return Void
 * @details Read and store all input signals.
           Read and verify the button states.
           Read and verify the position sensor.
 */
void Task_10ms()
{

        /*
         #ifdef DEBUG_MAIN
              Serial.print(" Task_10ms start. " );
              Serial.println(millis());
         #endif
         */
        Button_Acq();   //  ~ 1 ms

        Sensor_Mng();   //  ~ 1 - 2 ms

}

/**
 * @brief The Management function <brief>
 * @param [None]
 * @return Void
 * @details  The main function of the State Machine
 */
void Task_100ms()
{
        /*
         #ifdef DEBUG_MAIN
              Serial.print(" Task_100ms start. " );
              Serial.println(millis());
         #endif
         */
        Button_Mng();
}

void Task_300ms()
{
/*
 #ifdef DEBUG_MAIN
        Serial.print(" Task_300ms start. " );
        Serial.println(millis());
 #endif
 */
        Page_Act(Req_Page);
        MyStateMachine_Mng();
        Heart_Beat_LED = ! Heart_Beat_LED;
        digitalWrite(HEART_BEAT_LED_PIN, Heart_Beat_LED);
}

/*
unsigned long Start,Stop;
Start = millis();


        Stop = millis();

        Serial.print(" Task_10ms start:  " );
        Serial.print(Stop);
        Serial.print(" - " );
        Serial.print(Start);
        Serial.print(" =  ");
        Serial.println((Stop - Start));
*/
