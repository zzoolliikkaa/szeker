#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Page.h>
#include <MyStateMachine.h>

LiquidCrystal_I2C lcd(0x3F,20,4); // Set the LCD I2C address
uint8_t Act_Page = 0;
uint8_t Req_Page = 0;
uint8_t Lcd_State = LCD_ON;

void Page_Setup()
{
        lcd.init();                // initialize the lcd
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
        // 1st Line
        lcd.setCursor(0,0);
        lcd.print(" Darab:       ");

        // 2nd line
        lcd.setCursor(0,1);
        lcd.print(" Hossz:    ");
        lcd.setCursor(17,1);
        lcd.print(" m");

        //3 line
        lcd.setCursor(0,2);
        lcd.print(" Szelesseg:");
        lcd.setCursor(17,2);
        lcd.print(" m");

        //4 line
        lcd.setCursor(0,3);
        lcd.print(" Terulet: ");
        lcd.setCursor(17,3);
        lcd.print(" m2");
}

void Update_Page_1(int Nr,float Length,float Width, float Area)
{
        // 1st Line
        if (Nr > 99)
        {
                lcd.setCursor(14,0);
                lcd.print(String("Hiba !"));
                return;
        }
        else
        {
                if (Nr > 9)
                {
                        lcd.setCursor(15,0);
                }
                else
                {
                        lcd.setCursor(16,0);
                }
        }
        lcd.print(String(Nr));

        // 2nd line
        lcd.setCursor(13,1);
        lcd.print(String("     "));
        if (Length > (float)31.99)
        {
                lcd.setCursor(11,1);
                lcd.print(String("Hiba !"));
                return;
        }
        else
        {
                if (Length > (float)9.99)
                {
                        lcd.setCursor(12,1);
                }
                else
                {
                        lcd.setCursor(13,1);
                }
        }
        lcd.print(String(Length));

        //3 line
        lcd.setCursor(13,2);
        lcd.print(String("     "));
        if (Width > (float)31.99)
        {
                lcd.setCursor(11,2);
                lcd.print(String("Hiba !"));
                return;
        }
        else
        {
                if (Width > (float)9.99)
                {
                        lcd.setCursor(12,2);
                }
                else
                {
                        lcd.setCursor(13,2);
                }
        }
        lcd.print(String(Width));

        //4 line
        lcd.setCursor(13,3);
        lcd.print(String("     "));
        if (Area > (float)999.99)
        {
                lcd.setCursor(11,3);
                lcd.print(String("Hiba !"));
                return;
        }
        else
        {
                if (Area > (float)99.99)
                {
                        lcd.setCursor(11,3);
                }
                else
                {
                        if (Area > (float)9.99)
                        {
                                lcd.setCursor(12,3);
                        }
                        else
                        {
                                lcd.setCursor(13,3);
                        }
                }
        }
        lcd.print(String(Area));
}

void Page_2()
{
        lcd.clear();
        // 1st Line
        lcd.setCursor(0,0);
        lcd.print(" Darab:       ");

        // 2nd line
        lcd.setCursor(0,1);
        lcd.print(" Terulet:");
        lcd.setCursor(17,1);
        lcd.print("m2");

        //3 line
        lcd.setCursor(9,2);
        lcd.print("-----------");

        //4 line
        lcd.setCursor(0,3);
        lcd.print(" Osszeg:  ");
        lcd.setCursor(16,3);
        lcd.print(" RON");
}
void Update_Page_2(int Nr,float Area,float Sum)
{
        // 1st Line
        if (Nr > 99)
        {
                lcd.setCursor(13,0);
                lcd.print(String("Hiba !"));
                return;
        }
        else
        {
                if (Nr > 9)
                {
                        lcd.setCursor(14,0);
                }
                else
                {
                        lcd.setCursor(15,0);
                }
        }
        lcd.print(String(Nr));

        //2 line
        lcd.setCursor(11,1);
        lcd.print(String("     "));
        if (Area > (float)999.99)
        {
                lcd.setCursor(10,1);
                lcd.print(String("Hiba !"));
                return;
        }
        else
        {
                if (Area > (float)99.99)
                {
                        lcd.setCursor(10,1);
                }
                else
                {
                        if (Area > (float)9.99)
                        {
                                lcd.setCursor(11,1);
                        }
                        else
                        {
                                lcd.setCursor(12,1);
                        }
                }
        }
        lcd.print(String(Area));

        //4 line
        lcd.setCursor(10,3);
        lcd.print(String("      "));
        if (Sum > (float)999.99)
        {
                lcd.setCursor(10,3);
                lcd.print(String("Hiba !"));
                return;
        }
        else
        {
                if (Sum > (float)99.99)
                {
                        lcd.setCursor(10,3);
                }
                else
                {
                        if (Sum > (float)9.99)
                        {
                                lcd.setCursor(11,3);
                        }
                        else
                        {
                                lcd.setCursor(12,3);
                        }
                }
        }
        lcd.print(String(Sum));
}
void Page_3()
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
void Update_Page_3(float Rate)
{
        lcd.setCursor(5,0);
        lcd.print(String(Rate));
}
