/**
 * @file C:\Arduino\Szeker\lib\Task_Acq\MyButton.cpp
 * @author Balint Zoltan
 * @date 20 Nov 2017
 * @copyright 2017 Balint Zoltan
 * @brief <brief>
 *
 */

#include <JC_Button.h>
#include <MyButton.h>

Button b_SETTINGS(BUTTON_SETTINGS_PIN, PULLUP, INVERT, DEBOUNCE_MS); //Declare the button
Button b_SUMM(BUTTON_SUMM_PIN, PULLUP, INVERT, DEBOUNCE_MS); //Declare the button
Button b_NEXT(BUTTON_NEXT_PIN, PULLUP, INVERT, DEBOUNCE_MS); //Declare the button
Button b_CLR(BUTTON_CLR_PIN, PULLUP, INVERT, DEBOUNCE_MS); //Declare the button

uint8_t b_SETTINGS_State;
uint8_t b_SUMM_State;
uint8_t b_NEXT_State;
uint8_t b_CLR_State;
uint8_t Clear_All_Button;

uint8_t Button_Setup()
{
        b_SETTINGS_State = OLD;
        b_SETTINGS_State = OLD;
        b_SUMM_State = OLD;
        b_NEXT_State = OLD;
        b_CLR_State = OLD;
        return 0;
}

uint8_t Button_Acq()
{
        b_SETTINGS.read();
        b_SUMM.read();
        b_NEXT.read();
        b_CLR.read();
        return 0;
}

uint8_t Button_Mng()
{

        if (b_SETTINGS.isPressed())
        {
                b_SETTINGS_State = 1;
        }
        if ((b_SETTINGS.isReleased()) && (b_SETTINGS_State == 1))
        {
                b_SETTINGS_State = 0;
        }

        if (b_SUMM.isPressed())
        {
                b_SUMM_State = 1;
        }
        if ((b_SUMM.isReleased()) && (b_SUMM_State == 1))
        {
                b_SUMM_State = 0;
        }

        if (b_NEXT.isPressed())
        {
                b_NEXT_State = 1;
        }
        if ((b_NEXT.isReleased()) && (b_NEXT_State == 1))
        {
                b_NEXT_State = 0;
        }

        if (b_CLR.isPressed())
        {
                b_CLR_State = 1;
        }
        if ((b_CLR.isReleased()) && (b_CLR_State == 1))
        {
                b_CLR_State = 0;
        }


        if (1 == Clear_All_Button)
        {
                b_SETTINGS_State = OLD;
                b_SETTINGS_State = OLD;
                b_SUMM_State = OLD;
                b_NEXT_State = OLD;
                b_CLR_State = OLD;
                Clear_All_Button = 0;
        }
        return 0;
}
