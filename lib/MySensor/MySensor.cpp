/**
 * @file C:\Arduino\Szeker\lib\Sensor\Sensor.cpp
 * @author Balint Zoltan
 * @date 21 Nov 2017
 * @copyright 2017 Balint Zoltan
 * @brief <brief>
 *
 */
#include <Arduino.h>
#include <MySensor.h>

union Sensor
{
        struct
        {
                uint8_t b0 : 1;
                uint8_t b1 : 1;
                uint8_t b2 : 1;
                uint8_t b3 : 1;
                uint8_t b4 : 1;
        } Sensor_Bits;
        uint8_t Data;
};

float Sensor_Value = 0;
uint8_t Sensor_Data_Old = 0;

union Sensor S1;

uint8_t Sensor_Setup()
{
        pinMode(DIST_SENSOR_0_PIN, INPUT);
        pinMode(DIST_SENSOR_1_PIN, INPUT);
        return 0;
}

void Sensor_Acq()
{
        S1.Sensor_Bits.b0 = digitalRead(DIST_SENSOR_0_PIN);
        S1.Sensor_Bits.b1 = digitalRead(DIST_SENSOR_1_PIN);
        Sensor_Mng();
}
uint8_t Sensor_Mng()
{
        if(S1.Sensor_Bits.b0 == HIGH)
        {
              Sensor_Value = Sensor_Value + 0.02;
        }
        if(S1.Sensor_Bits.b1 == HIGH)
        {
              Sensor_Value = Sensor_Value - 0.02;
        }

#ifdef DEBUG_SENSOR
                        Serial.print(" Sensor :  ");
                        Serial.print(S1.Sensor_Bits.b0);
                        Serial.print(S1.Sensor_Bits.b1);
                        Serial.print(" = ");
                        Serial.println(Sensor_Value);
#endif
      //Sensor_Value = Sensor_Value / 100;

      return 0;
}

uint8_t Sensor_Act()
{

        return 0;
}
