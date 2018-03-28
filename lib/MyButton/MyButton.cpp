/**
 * @file C:\Arduino\Szeker\lib\Task_Acq\MyButton.cpp
 * @author Balint Zoltan
 * @date 20 Nov 2017
 * @copyright 2017 Balint Zoltan
 * @brief <brief>
 *
 */

#include <Button.h>
#include <MyButton.h>

Button b_M_ft(BUTTON_M_FT_PIN, PULLUP, INVERT, DEBOUNCE_MS); //Declare the button
Button b_SM(BUTTON_SM_PIN, PULLUP, INVERT, DEBOUNCE_MS); //Declare the button
Button b_RM(BUTTON_RM_PIN, PULLUP, INVERT, DEBOUNCE_MS); //Declare the button
Button b_CLR(BUTTON_CLR_PIN, PULLUP, INVERT, DEBOUNCE_MS); //Declare the button
Button b_ON_OFF(BUTTON_ON_OFF_PIN, PULLUP, INVERT, DEBOUNCE_MS); //Declare the button

uint8_t b_M_ft_State;
uint8_t b_SM_State;
uint8_t b_RM_State;
uint8_t b_CLR_State;
uint8_t b_ON_OFF_State;
uint8_t Clear_All_Button;

uint8_t Button_Setup()
{
        b_M_ft_State = OLD;
        b_M_ft_State = OLD;
        b_SM_State = OLD;
        b_RM_State = OLD;
        b_CLR_State = OLD;
        b_ON_OFF_State = OLD;
        return 0;
}

uint8_t Button_Acq()
{
        b_M_ft.read();
        b_SM.read();
        b_RM.read();
        b_CLR.read();
        b_ON_OFF.read();
        return 0;
}

uint8_t Button_Mng()
{

        if (b_M_ft.isPressed())
        {
                b_M_ft_State = 1;
        }
        if ((b_M_ft.isReleased()) && (b_M_ft_State == 1))
        {
                b_M_ft_State = 0;
        }

        if (b_SM.isPressed())
        {
                b_SM_State = 1;
        }
        if ((b_SM.isReleased()) && (b_SM_State == 1))
        {
                b_SM_State = 0;
        }

        if (b_RM.isPressed())
        {
                b_RM_State = 1;
        }
        if ((b_RM.isReleased()) && (b_RM_State == 1))
        {
                b_RM_State = 0;
        }

        if (b_CLR.isPressed())
        {
                b_CLR_State = 1;
        }
        if ((b_CLR.isReleased()) && (b_CLR_State == 1))
        {
                b_CLR_State = 0;
        }

        if (b_ON_OFF.isPressed())
        {
                b_ON_OFF_State = 1;
        }
        if ((b_ON_OFF.isReleased()) && (b_ON_OFF_State == 1))
        {
                b_ON_OFF_State = 0;
        }
        if (1 == Clear_All_Button)
        {
                b_M_ft_State = OLD;
                b_M_ft_State = OLD;
                b_SM_State = OLD;
                b_RM_State = OLD;
                b_CLR_State = OLD;
                b_ON_OFF_State = OLD;
                Clear_All_Button = 0;
        }
        return 0;
}
