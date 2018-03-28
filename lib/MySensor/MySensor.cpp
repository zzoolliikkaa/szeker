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
        pinMode(DIST_SENSOR_0_PIN, INPUT_PULLUP);
        pinMode(DIST_SENSOR_1_PIN, INPUT_PULLUP);
        pinMode(DIST_SENSOR_2_PIN, INPUT_PULLUP);
        pinMode(DIST_SENSOR_3_PIN, INPUT_PULLUP);
        pinMode(DIST_SENSOR_4_PIN, INPUT_PULLUP);
        return 0;
}

void Sensor_Acq()
{
        S1.Sensor_Bits.b0 = !digitalRead(DIST_SENSOR_4_PIN);
        S1.Sensor_Bits.b1 = !digitalRead(DIST_SENSOR_1_PIN);
        S1.Sensor_Bits.b2 = !digitalRead(DIST_SENSOR_3_PIN);
        S1.Sensor_Bits.b3 = !digitalRead(DIST_SENSOR_0_PIN);
        S1.Sensor_Bits.b4 = !digitalRead(DIST_SENSOR_2_PIN);
        Sensor_Mng();
}
uint8_t Sensor_Mng()
{
        if ((S1.Sensor_Bits.b0 +
             S1.Sensor_Bits.b1 +
             S1.Sensor_Bits.b2 +
             S1.Sensor_Bits.b3 +
             S1.Sensor_Bits.b4) == 1)
        {
          // Ha a Senzorok ertekeinek ossszege = 1 akkor minden masodik valtozast veszunk figyelembe igy a felbontas 2 cm
                if (Sensor_Data_Old != S1.Data)
                {
                  // Volt Senzor ertek valtozas az utolso ellenorzes ota ?
                        if (Sensor_Data_Old < S1.Data)
                        {
                                Sensor_Value = Sensor_Value - 2;
                        }
                        if (Sensor_Data_Old > S1.Data)
                        {
                                Sensor_Value = Sensor_Value + 2;;
                        }
                        // a Kovetkezokben a valtozas erteke azert 4 mert a fenti feltetelek kozul
                        // vlmelyik mar teljesult es annak hatasat is ellensulyozni kell
                        if ((Sensor_Data_Old == 16) && (S1.Data == 1) )
                        {
                                Sensor_Value = Sensor_Value - 4;
                        }
                        if ((Sensor_Data_Old == 1) && (S1.Data  == 16))
                        {
                                Sensor_Value = Sensor_Value + 4;
                        }
                }
                // Elmentjuk az aktualis Senzor erteket
                Sensor_Data_Old = S1.Data;
        }
        return 0;
}

uint8_t Sensor_Act()
{

        return 0;
}
