/**
 * @file C:\Arduino\Szeker\lib\Task_Acq\MyButton.h
 * @author Balint Zoltan
 * @date 20 Nov 2017
 * @copyright 2017 Balint Zoltan
 * @brief <brief>
 *
 */

#define BUTTON_CLR_PIN        4
#define BUTTON_NEXT_PIN       5 //next
#define BUTTON_SUMM_PIN       6 //SUM
#define BUTTON_SETTINGS_PIN   7 //SETTINGS
#define PULLUP true        //To keep things simple, we use the Arduino's internal pullup resistor.
#define INVERT true        //Since the pullup resistor will keep the pin high unless the
                           //switch is closed, this is negative logic, i.e. a high state
                           //means the button is NOT pressed. (Assuming a normally open switch.)
#define DEBOUNCE_MS 20     //A debounce time of 20 milliseconds usually works well for tactile button switches.

#define PRESSED   1
#define RELEASED  0
#define OLD       3

extern uint8_t b_SETTINGS_State;
extern uint8_t b_SUMM_State;
extern uint8_t b_NEXT_State;
extern uint8_t b_CLR_State;
extern uint8_t Clear_All_Button;

uint8_t Button_Setup();
uint8_t Button_Acq();
uint8_t Button_Mng();
