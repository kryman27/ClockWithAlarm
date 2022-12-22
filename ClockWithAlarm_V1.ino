#include <LiquidCrystal.h>
#include <TimeLib.h>

//screen pins
const byte lcdRs = 2;
const byte lcdEn = 3;
const byte lcdD4 = 4;
const byte lcdD5 = 5;
const byte lcdD6 = 6;
const byte lcdD7 = 7;
const byte scrRows = 2;
const byte scrColumns = 16;

//buttons pins
const byte buttonChange = 10;
const byte buttonUp = 11;
const byte buttonDown = 9;

const byte buzzer = 8;

int delayTime = 1000;

//"lcd" display declaration with proper arguments
LiquidCrystal lcd(lcdRs, lcdEn, lcdD4, lcdD5, lcdD6, lcdD7);

void setup() {
  pinMode(buttonChange, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  lcd.begin(scrColumns, scrRows);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Screen init."));
  lcd.setCursor(0, 1);
  lcd.print(F("Timer init."));
  delay(delayTime * 2);
  
  while(digitalRead(buttonChange) == HIGH){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("Set Clock"));
  }

  delay(delayTime * 2);
 

}

void loop() {
//Purpose of V1 is to check connections and if hardware behaves as wanted  
  while(digitalRead(buttonChange) == LOW){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("change"));
    delay(delayTime / 20);
  }

  while(digitalRead(buttonUp) == LOW){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("UP UP UP"));
    delay(delayTime / 20);
  }
  
  while(digitalRead(buttonDown) == LOW){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(F("DOWN DOWN"));
    delay(delayTime / 20);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("hello world!"));
  
  //buzzer linia nizej, dziala
  //tone(buzzer, 488, 200);
  delay(delayTime / 5);
}

//planned functions
// void setClock(){}
// void setAlarm(){}
// void alarm(){}
