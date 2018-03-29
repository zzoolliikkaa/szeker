#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Page.h>
#include <MyStateMachine.h>
#include <MyChar.h>

LiquidCrystal_I2C lcd(0x3F,20,4); // Set the LCD I2C address
uint8_t Act_Page = 0;
uint8_t Req_Page = 0;
uint8_t Lcd_State = LCD_ON;

void Page_Setup()
{
        lcd.init();                // initialize the lcd
        lcd.createChar(0,bar1);
        lcd.createChar(1,bar2);
        lcd.createChar(2,bar3);
        lcd.createChar(3,bar4);
        lcd.createChar(4,bar5);
        lcd.createChar(5,bar6);
        lcd.createChar(6,bar7);
        lcd.createChar(7,bar8);
        lcd.backlight();
        Req_Page = MEASURE_X;
        Act_Page = 0;
}

void Page_Act(uint8_t Req_Page)
{
        if ((Act_Page != Req_Page) && (LCD_ON == Lcd_State))
        {
                lcd.clear();
                switch (Req_Page)
                {
                case 1: {
                        Page_1();
                        Act_Page = 1;
                        break;
                }
                case 2: {
                        Page_2();
                        Act_Page = 2;
                        break;
                }
                case 3: {
                        Page_3();
                        Act_Page = 3;
                        break;
                }
                case 4: {
                        Page_4();
                        Act_Page = 4;
                        break;
                }
                default: {
                        //Page_1();
                        break;
                }
                }
        }
        if (LCD_OFF == Lcd_State)
        {
          lcd.noDisplay();
          lcd.noBacklight();
        }
        if (LCD_ON == Lcd_State)
        {
          lcd.display();
          lcd.backlight();
        }
}

void Page_1()
{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Darab");
        BigNumberColumn = 6;
        printLine();
        lcd.setCursor(7,0);
        lcd.print("  Hosszusag");
}
void Update_Page_1(float Length,uint8_t Nr)
{
        BigNumberRow_0 = 1;
        BigNumberRow_1 = 2;
        BigNumberColumn = 4;
        BigNumberNr = 2;
        printBigNumber(Nr,0);

        BigNumberRow_0 = 1;
        BigNumberRow_1 = 2;
        BigNumberColumn = 17;
        BigNumberNr = 4;
        printBigNumber(Length,1);
}
void Page_2()
{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Darab");
      BigNumberColumn = 6;
      printLine();
      lcd.setCursor(7,0);
      lcd.print("  Szelesseg");
}
void Update_Page_2(float Width,uint8_t Nr)
{
      BigNumberRow_0 = 1;
      BigNumberRow_1 = 2;
      BigNumberColumn = 4;
      BigNumberNr = 2;
      printBigNumber(Nr,0);

      BigNumberRow_0 = 1;
      BigNumberRow_1 = 2;
      BigNumberColumn = 17;
      BigNumberNr = 4;
      printBigNumber(Width,1);
}
void Page_3()
{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Osszeg:");
        lcd.setCursor(0,2);
        lcd.print("Darab:");
        lcd.setCursor(0,3);
        lcd.print(" Terulet:");
}
void Update_Page_3(float Area,float Sum,uint8_t Nr)
{
        BigNumberRow_0 = 0;
        BigNumberRow_1 = 1;
        BigNumberColumn = 17;
        printBigNumber(Sum,1);
        lcd.setCursor(11,2);
        lcd.print(Nr);
        lcd.setCursor(11,3);
        lcd.print(String(Area));
        lcd.setCursor(16,3);
        lcd.print("m2");
}
void Page_4()
{
        lcd.clear();
        // 1st Line
        lcd.setCursor(8,0);
        lcd.print("   RON/m2");

        // 2nd line
        lcd.setCursor(0,1);
        lcd.print("     SM: +10 bani");

        //3 line
        lcd.setCursor(0,2);
        lcd.print("     RM: -10 bani");

        //4 line
        lcd.setCursor(0,3);
        lcd.print("     M/Ft: Mentes ");
}
void Update_Page_4(float Rate)
{
        lcd.setCursor(5,0);
        lcd.print(String(Rate));
}
