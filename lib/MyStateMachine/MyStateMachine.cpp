/**
 * @file C:\Arduino\Szeker\lib\MyStateMachine\MyStateMachine.cpp
 * @author Balint Zoltan
 * @date 27 Nov 2017
 * @copyright 2017 Balint Zoltan
 * @brief <brief>
 *
 */
#include <Arduino.h>
#include <EEPROM.h>
#include <avr\Sleep.h>
#include <MyStateMachine.h>
#include <Page.h>
#include <MyButton.h>
#include <MySensor.h>

#define MEASURE_Y       2
#define SUMMARY         3
#define SETTINGS        4
#define PRE_SLEEP        5
#define SLEEP           6
#define WAKE_UP         7

void WakeUpNow();

uint8_t StateMachine = 0;
uint8_t OldStateMachine = 0;
uint8_t OldReqPage = 0;
uint8_t Nr = 1;
float Length = 0;
float Width = 0;
float Area = 0;
float AreaSum = 0;
float Rate = 0;
float Rate_old = 0;
uint16_t SleepCounter = 0;

void StateMachine_Setup()
{
        uint8_t Rate_Integer, Rate_Decimal;
        StateMachine = MEASURE_X;
        Rate_Integer = EEPROM.read(RATE_ADDRESS);
#ifdef DEBUG_STATE_MACHINE
        Serial.print(" EEPROM : Rate (RAW):");
        Serial.println( Rate_Integer);
#endif
        if (0 == Rate_Integer)
        {
                StateMachine = SETTINGS;
                Req_Page = 3;
        }
        else
        {
                Rate_Decimal = Rate_Integer % 10;
                Rate_Integer = Rate_Integer / 10;
                Rate = (float) (Rate_Decimal);
                Rate = Rate / 10;
                Rate = Rate + Rate_Integer;
                Rate_old = Rate;
#ifdef DEBUG_STATE_MACHINE
                Serial.print(" EEPROM : Rate :");
                Serial.println( Rate);
#endif
                Req_Page = 1;
        }

        pinMode(WAKE_UP_PIN, INPUT_PULLUP);
        pinMode(SENSOR_PIN, INPUT);
        SleepCounter = 0;
        if (MEASURE_X == StateMachine)
        {
                attachInterrupt(digitalPinToInterrupt(SENSOR_PIN),Sensor_Acq, CHANGE);
        }
}


void MyStateMachine_Mng()
{
/*
 #ifdef DEBUG_STATE_MACHINE
        Serial.print(" Area :  ");
        Serial.println(Area);
        Serial.print(" AreaSum :  ");
        Serial.println(AreaSum);
 #endif
 */
        if ((StateMachine != PRE_SLEEP) && (StateMachine != SLEEP) && (StateMachine != WAKE_UP))
        {
                SleepCounter = SleepCounter + 1;

#ifdef DEBUG_STATE_MACHINE
                Serial.print(" Sleep Counter ");
                Serial.println(SleepCounter);
#endif

        }

        if (SLEEP_TIMER == SleepCounter)
        {
                // elmentjuk az aktualis allapotokat
                OldReqPage = Req_Page;
                OldStateMachine = StateMachine;
                // PreSleep modba lepunk
                StateMachine = PRE_SLEEP;
                Lcd_State = LCD_OFF;
                // Csak egyszer hajtodik vegre az IF
                SleepCounter = SleepCounter + 1;
        }

        switch (StateMachine)
        {
        case MEASURE_X: {
/*
 #ifdef DEBUG_STATE_MACHINE
                Serial.println(" State : MEASURE_X ");
 #endif
*/
                // Csak PROBA
                if (PRESSED == b_M_ft_State)
                {
                        SleepCounter = 0;
                        b_M_ft_State = OLD;
                        Length = Length + 0.2;
                }
                if (Sensor_Value != 0)
                {
                        SleepCounter = 0;
                        if ( (Length + Sensor_Value) < 0 )
                        {
                                Length = 0;
                        }
                        else
                        {
                                Length = Length + Sensor_Value;
                                Sensor_Value = 0;
/*
                    #ifdef DEBUG_STATE_MACHINE
                                Serial.print(" Length : ");
                                Serial.println(Length);
                    #endif
*/
                        }
                }
                // Csak PROBA VEGE
                // Enter the Measure_y Page
                if (RELEASED == b_RM_State)
                {
                        SleepCounter = 0;
                        b_RM_State = OLD;
                        if (Length > 0)
                        {
                                StateMachine = MEASURE_Y;
                                Req_Page = 2;
                                Clear_All_Button = 1;
                        }
                }
                // Enter to the Settings Page
/*                if (PRESSED == b_CLR_State)
                {
                        StateMachine = SETTINGS;
                        Req_Page = 3;
                }
                break;
 */
                // Clear the actual measurement
                if (PRESSED == b_CLR_State)
                {
                        SleepCounter = 0;
                        b_CLR_State = OLD;
                        Length = 0;
                }
                Update_Page_1(Length,Nr);
                break;
        }

        case MEASURE_Y: {
                // Set Measure Page in the LCD
/*
 #ifdef DEBUG_STATE_MACHINE
                Serial.println(" State : MEASURE_Y ");
 #endif
*/
                // Csak PROBA
                if (PRESSED == b_M_ft_State)
                {
                        SleepCounter = 0;
                        b_M_ft_State = OLD;
                        Width = Width + 0.2;
                        Area = Length * Width;
                }
                // Csak PROBA VEGE

                if (RELEASED == b_RM_State)
                {
                        SleepCounter = 0;
                        b_RM_State = OLD;
                        if (Width > 0)
                        {
                                Nr = Nr + 1;
                                AreaSum = AreaSum + Area;
                                Length = 0;
                                Width = 0;
                                Area = 0;
                                StateMachine = MEASURE_X;
                                Req_Page = 1;
                                Clear_All_Button = 1;
                        }
                }
                // Enter the Summary Page
                if (RELEASED == b_SM_State)
                {
                        SleepCounter = 0;
                        b_SM_State = OLD;
                        if (Width > 0)
                        {
                                AreaSum = AreaSum + Area;
                                StateMachine = SUMMARY;
                                detachInterrupt(digitalPinToInterrupt(SENSOR_PIN));
                                Req_Page = 3;
                                Clear_All_Button = 1;
                        }
                }
                // Add the Sensor Value to the Width
                if (Sensor_Value != 0)
                {
                        SleepCounter = 0;
                        if ( (Width + Sensor_Value) < 0 )
                        {
                                Width = 0;
                        }
                        else
                        {
                                Width = Width + Sensor_Value;
                        }
                        Area = Length * Width;
                        Sensor_Value = 0;
/*
                    #ifdef DEBUG_STATE_MACHINE
                        Serial.print(" Width : ");
                        Serial.println(Width);
                    #endif
*/
                }
                // Clear the actual measurement
                if (RELEASED == b_CLR_State)
                {
                        SleepCounter = 0;
                        b_CLR_State = OLD;
                        Width = 0;
                        Area = 0;
                }
                Update_Page_2(Width,Nr);
                break;
        }
        case SUMMARY: {
                // Set Summary Page in the LCD
/*
 #ifdef DEBUG_STATE_MACHINE
                Serial.println(" State : SUMMARY ");
 #endif
*/
                if (RELEASED == b_CLR_State)
                {
                        SleepCounter = 0;
                        b_CLR_State = OLD;
                        Nr = 1;
                        Length = 0;
                        Width = 0;
                        Area = 0;
                        AreaSum = 0;
                        StateMachine = MEASURE_X;
                        attachInterrupt(digitalPinToInterrupt(SENSOR_PIN),Sensor_Acq, CHANGE);
                        Req_Page = 1;
                        Clear_All_Button = 1;
                }
                Update_Page_3(AreaSum,(float)(AreaSum * Rate),Nr);
                break;
        }

        case SETTINGS: {
                // Set page in the LCD
/*
 #ifdef DEBUG_STATE_MACHINE
                Serial.println(" State : SETTINGS ");
 #endif
*/
                // Increment Rate value
                if ((PRESSED == b_SM_State) && (Rate < 25.4) )
                {
                        SleepCounter = 0;
                        b_SM_State = OLD;
                        Rate = Rate + 0.1;
                }
                // Decrement Rate value
                if ( (PRESSED == b_RM_State) && (Rate > 0.1) )
                {
                        SleepCounter = 0;
                        b_RM_State = OLD;
                        Rate = Rate - 0.1;
                }
                // Save new Rate value to the EEProm
                if (RELEASED == b_M_ft_State)
                {
                        SleepCounter = 0;
                        b_M_ft_State = OLD;
                        if (Rate != Rate_old)
                        {
 #ifdef DEBUG_STATE_MACHINE
                                Serial.print(" EEPROM : New Rate :");
                                Serial.println( Rate);
 #endif
                                EEPROM.update(RATE_ADDRESS, (uint8_t)(Rate*10));
                        }
                        StateMachine = MEASURE_X;
                        attachInterrupt(digitalPinToInterrupt(SENSOR_PIN),Sensor_Acq, CHANGE);
                        Req_Page = 1;
                        Clear_All_Button = 1;
                }
/*
        // Reset the Rate value to 0
        if (b_CLR.pressedFor(5000) )
        {
                EEPROM.update(RATE_ADDRESS, 0);
                StateMachine = MEASURE_X;
                Req_Page = 1;
        }
 */
                Update_Page_4(Rate);
                break;
        }
        case PRE_SLEEP: {
#ifdef DEBUG_STATE_MACHINE
                Serial.println(" State : PRESLEEP ");
#endif
                digitalWrite(HEART_BEAT_LED_PIN, 0);
                /* Preparing to the SLEEP Mode */
//                Lcd_State = LCD_OFF;
                StateMachine = SLEEP;
                break;
        }
        case SLEEP: {
#ifdef DEBUG_STATE_MACHINE
                Serial.println(" State : SLEEP ");
                //delay(1000);
#endif
                set_sleep_mode(SLEEP_MODE_PWR_DOWN);
                sleep_enable();
                attachInterrupt(digitalPinToInterrupt(WAKE_UP_PIN),WakeUpNow, RISING);
                /* Entering to the SLEEP Mode */
                sleep_mode();

                /*ZZZzzzzzzzz........*/

                /* Exiting from the SLEEP Mode */
                sleep_disable();
                detachInterrupt(digitalPinToInterrupt(WAKE_UP_PIN));

                StateMachine = WAKE_UP;

                break;
        }
        case WAKE_UP: {
#ifdef DEBUG_STATE_MACHINE
                Serial.println(" State : WAKE UP ");
#endif
                Lcd_State = LCD_ON;

                /* Restoring the Previous State */
                StateMachine = OldStateMachine;
                SleepCounter = 0;
                break;
        }
        }
}


void WakeUpNow()
{

}
