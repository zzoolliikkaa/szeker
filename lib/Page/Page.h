/**
 * @file C:\Arduino\Szeker\lib\Page\Page.h
 * @author Joe Bloggs
 * @date 19 Nov 2017
 * @copyright 2017 Joe Bloggs
 * @brief <brief>
 *
 */

#define LCD_ON        1
#define LCD_OFF       0

extern uint8_t Req_Page;
extern uint8_t Lcd_State;

void Page_Setup();
void Page_Act(uint8_t);

void Page_1();
void Update_Page_1(int,float,float,float );        // ~ 52 ms
void Page_2();
void Update_Page_2(int,float,float );             //  ~ 37 ms
void Page_3();
void Update_Page_3(float );                       // ~ 8 ms
