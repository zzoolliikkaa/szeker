#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <MyChar.h>


uint8_t BigNumberRow_0 = 0;
uint8_t BigNumberRow_1 = 0;
uint8_t BigNumberColumn = 0;
uint8_t BigNumberNr = 4;

uint8_t bar1[8] =
{
        B11100,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11110,
        B11100
};

uint8_t bar2[8] =
{
        B00111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B01111,
        B00111
};
uint8_t bar3[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
uint8_t bar4[8] =
{
        B11110,
        B11100,
        B00000,
        B00000,
        B00000,
        B00000,
        B11000,
        B11100
};
uint8_t bar5[8] =
{
        B01111,
        B00111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00011,
        B00111
};
uint8_t bar6[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111
};
uint8_t bar7[8] =
{
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00111,
        B01111
};
uint8_t bar8[8] =
{
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

void custom0(int col)
{ // uses segments to build the number 0
  lcd.setCursor(col, BigNumberRow_0);
  lcd.write(1);
  lcd.write(7);
  lcd.write(0);
  lcd.setCursor(col, BigNumberRow_1);
  lcd.write(1);
  lcd.write(5);
  lcd.write(0);
}

void custom1(int col)
{
  lcd.setCursor(col,BigNumberRow_0);
  lcd.write(32);
  lcd.write(32);
  lcd.write(0);
  lcd.setCursor(col,BigNumberRow_1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(0);
}

void custom2(int col)
{
  lcd.setCursor(col,BigNumberRow_0);
  lcd.write(4);
  lcd.write(2);
  lcd.write(0);
  lcd.setCursor(col, BigNumberRow_1);
  lcd.write(1);
  lcd.write(5);
  lcd.write(5);
}

void custom3(int col)
{
  lcd.setCursor(col,BigNumberRow_0);
  lcd.write(4);
  lcd.write(2);
  lcd.write(0);
  lcd.setCursor(col, BigNumberRow_1);
  lcd.write(6);
  lcd.write(5);
  lcd.write(0);
}

void custom4(int col)
{
  lcd.setCursor(col,BigNumberRow_0);
  lcd.write(1);
  lcd.write(5);
  lcd.write(0);
  lcd.setCursor(col, BigNumberRow_1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(0);
}

void custom5(int col)
{
  lcd.setCursor(col,BigNumberRow_0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.setCursor(col, BigNumberRow_1);
  lcd.write(6);
  lcd.write(5);
  lcd.write(0);
}

void custom6(int col)
{
  lcd.setCursor(col,BigNumberRow_0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.setCursor(col, BigNumberRow_1);
  lcd.write(1);
  lcd.write(5);
  lcd.write(0);
}

void custom7(int col)
{
  lcd.setCursor(col,BigNumberRow_0);
  lcd.write(1);
  lcd.write(7);
  lcd.write(0);
  lcd.setCursor(col, BigNumberRow_1);
  lcd.write(32);
  lcd.write(32);
  lcd.write(0);
}

void custom8(int col)
{
  lcd.setCursor(col, BigNumberRow_0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(0);
  lcd.setCursor(col, BigNumberRow_1);
  lcd.write(1);
  lcd.write(5);
  lcd.write(0);
}

void custom9(int col)
{
  lcd.setCursor(col, BigNumberRow_0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(0);
  lcd.setCursor(col, BigNumberRow_1);
  lcd.write(6);
  lcd.write(5);
  lcd.write(0);
}


void printNumber(int value, int col) {
  if (value == 0) {
    custom0(col);
  } if (value == 1) {
    custom1(col);
  } if (value == 2) {
    custom2(col);
  } if (value == 3) {
    custom3(col);
  } if (value == 4) {
    custom4(col);
  } if (value == 5) {
    custom5(col);
  } if (value == 6) {
    custom6(col);
  } if (value == 7) {
    custom7(col);
  } if (value == 8) {
    custom8(col);
  } if (value == 9) {
    custom9(col);
  }
}

void printBigFloat(float rpm, uint8_t Dot)
{
  uint8_t m , c, d, u;
  uint16_t number;
  number = uint16_t(rpm * 100 );
  if (number > 999) {
    m = (number - (number % 1000)) / 1000;
    number = number % 1000;
  } else {
    m = 0;
  }

  if (number > 99) {
    c = (number - (number % 100)) / 100;
    number = number % 100;
  } else {
    c = 0;
  }

  if (number > 9) {
    d = (number - (number % 10)) / 10;
    number = number % 10;
  } else {
    d = 0;
  }

  u = number;
  if (BigNumberNr > 3)      printNumber(m, BigNumberColumn -10);
  if (BigNumberNr > 2)      printNumber(c, BigNumberColumn -7);

  if ( 1 == Dot )
  {
    lcd.setCursor(BigNumberColumn - 4, BigNumberRow_1);
    lcd.write(0xA1);
  }
  else
  {
    BigNumberColumn = BigNumberColumn - 1;
  }
  if (BigNumberNr > 1)    printNumber(d, BigNumberColumn -3);
  if (BigNumberNr > 0)    printNumber(u, BigNumberColumn );

}
void printBigInt(uint8_t number)
{
  uint8_t x1,x10;

  x1 = number % 10;
  number = number / 10;
  x10 = number % 10;
  number = number / 10;

  printNumber(x10, BigNumberColumn -3);
  printNumber(x1, BigNumberColumn );
}

void printLine()
{
  lcd.setCursor(BigNumberColumn,0);
  lcd.write(0x7C);
  lcd.setCursor(BigNumberColumn,1);
  lcd.write(0x7C);
  lcd.setCursor(BigNumberColumn,2);
  lcd.write(0x7C);
  lcd.setCursor(BigNumberColumn,3);
  lcd.write(0x7C);
}
