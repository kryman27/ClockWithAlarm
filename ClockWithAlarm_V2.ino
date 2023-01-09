#include <LiquidCrystal.h>
#include <TimeLib.h>

//screen pins declaration
const byte lcdRs = 2;
const byte lcdEn = 3;
const byte lcdD4 = 4;
const byte lcdD5 = 5;
const byte lcdD6 = 6;
const byte lcdD7 = 7;
const byte scrRows = 2;
const byte scrColumns = 16;

const byte buttonSet = 10;
const byte buttonUp = 11;
const byte buttonDown = 9;

const byte buzzer = 8;

int delayTime = 1000;
byte clockHours = 0;
byte clockMinutes = 0;
byte clockSeconds = 0;
bool setting = false;
time_t readedTime;

byte alarmTimeHour = 0;
byte alarmTimeMinute = 0;
bool settingAlarm = false;
bool alarmOn = false;

byte alarmTriggerHour = 0;
byte alarmTrriggerMinute = 0;

byte customChar1[] = {  //custom character1 declaration
  B00001,
  B00011,
  B00111,
  B00111,
  B01111,
  B11111,

  B00011,
  B00001
};
byte customChar2[] = {  //custom character2 declaration
  B10000,
  B11000,
  B11100,
  B11100,
  B11110,
  B11111,
  B11000,
  B10000
};

//set LCD pins
LiquidCrystal lcd(lcdRs, lcdEn, lcdD4, lcdD5, lcdD6, lcdD7);

void setup() {
  pinMode(buttonSet, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  lcd.begin(scrColumns, scrRows);

  lcd.createChar(1, customChar1);  //create custom character1
  lcd.createChar(2, customChar2);  //create custom character2

  lcd.home();
  lcd.print(F("Set your clock  "));
  lcd.setCursor(0, 1);
  lcd.print(F("Press SET button"));

  while (digitalRead(buttonSet) == HIGH) {}
  while (digitalRead(buttonSet) == LOW) {
    setting = true;
    lcd.clear();
  }
  setClock();
  setTime(clockHours, clockMinutes, clockSeconds, 0, 0, 0);
  delay(delayTime / 2);
}


void loop() {
  //set alarm time
  while ((digitalRead(buttonSet) == LOW) && (settingAlarm == false)) {
    settingAlarm = true;
    delay(delayTime / 10);
  }
  while (settingAlarm == true) {
    lcd.clear();
    setAlarm();
    delay(delayTime / 10);
  }

  while ((digitalRead(buttonDown) == LOW) && (alarmOn == true)) {
    alarmOn = false;
    delay(delayTime / 10);
  }


  //read and display current time
  readedTime = now();
  alarmTriggerHour = hour(readedTime);
  alarmTrriggerMinute = minute(readedTime);
  lcd.setCursor(0, 0);
  if (hour(readedTime) < 10) {
    lcd.print("0");
    lcd.print(hour(readedTime));
  } else lcd.print(hour(readedTime));
  lcd.print(":");
  if (minute(readedTime) < 10) {
    lcd.print("0");
    lcd.print(minute(readedTime));
  } else lcd.print(minute(readedTime));
  lcd.print(":");
  if (second(readedTime) < 10) {
    lcd.print("0");
    lcd.print(second(readedTime));
  } else lcd.print(second(readedTime));
  lcd.setCursor(8, 0);
  lcd.print(F("        "));

  //read and display alarm time
  if (alarmOn == true) {
    lcd.setCursor(0, 1);
    lcd.print("         ");
    lcd.write(1);
    lcd.write(2);
    if (alarmTimeHour < 10) {
      lcd.print("0");
      lcd.print(alarmTimeHour);
    } else lcd.print(alarmTimeHour);
    lcd.print(":");
    if (alarmTimeMinute < 10) {
      lcd.print("0");
      lcd.print(alarmTimeMinute);
    } else lcd.print(alarmTimeMinute);
  } else if (alarmOn == false) {
    lcd.setCursor(0, 1);
    lcd.print("           --:--");
  }

  while (alarmTimeHour == alarmTriggerHour && alarmTimeMinute == alarmTrriggerMinute && alarmOn == true) {
    alarm();
  }
}

void setClock() {
  //setting up
  while (setting == true) {
    if (digitalRead(buttonUp) == LOW) {
      clockMinutes = clockMinutes + 1;
    }
    delay(delayTime / 50);
    if (clockMinutes > 59) {
      clockHours++;
      clockMinutes = 0;
    }
    if (clockHours > 23) {
      clockHours = 0;
    }
    lcd.setCursor(0, 0);
    lcd.print(F("Set Clock"));
    lcd.setCursor(0, 1);
    if (clockHours < 10) {
      lcd.print(F("0"));
      lcd.print(clockHours);
    } else lcd.print(clockHours);
    lcd.print(F(":"));
    if (clockMinutes < 10) {
      lcd.print(F("0"));
      lcd.print(clockMinutes);
    } else lcd.print(clockMinutes);

    //setting down
    if (digitalRead(buttonDown) == LOW) {
      clockMinutes = clockMinutes - 1;
    }
    delay(delayTime / 50);
    if (clockMinutes >= 255) {
      clockMinutes = 59;
      clockHours--;
    }
    if (clockHours >= 255) {
      clockHours = 23;
    }
    if (digitalRead(buttonSet) == LOW) {
      setting = false;
    }
    lcd.setCursor(0, 0);
    lcd.print(F("Set Clock"));
    lcd.setCursor(0, 1);
    if (clockHours < 10) {
      lcd.print(F("0"));
      lcd.print(clockHours);
    } else lcd.print(clockHours);
    lcd.print(F(":"));
    if (clockMinutes < 10) {
      lcd.print(F("0"));
      lcd.print(clockMinutes);
    } else lcd.print(clockMinutes);
  }
  if (digitalRead(buttonSet) == LOW) {
    setting = false;
    lcd.clear();
  }
}

void setAlarm() {
  while (settingAlarm == true) {
    if (digitalRead(buttonUp) == LOW) {
      alarmTimeMinute = alarmTimeMinute + 1;
    }
    delay(delayTime / 100);
    if (alarmTimeMinute > 59) {
      alarmTimeHour++;
      alarmTimeMinute = 0;
    }
    if (alarmTimeHour > 23) {
      alarmTimeHour = 0;
    }
   
    //setting down
    if (digitalRead(buttonDown) == LOW) {
      alarmTimeMinute = alarmTimeMinute - 1;
    }
    delay(delayTime / 100);
    if (alarmTimeMinute >= 255) {
      alarmTimeMinute = 59;
      alarmTimeHour--;
    }
    if (alarmTimeHour >= 255) {
      alarmTimeHour = 23;
    }
    delay(100);
    if (digitalRead(buttonSet) == LOW) {
      break;
    }

    lcd.setCursor(0, 0);
    lcd.print(F("Set Alarm       "));
    lcd.setCursor(0, 1);
    if (alarmTimeHour < 10) {
      lcd.print(F("0"));
      lcd.print(alarmTimeHour);
    } else lcd.print(alarmTimeHour);
    lcd.print(F(":"));
    if (alarmTimeMinute < 10) {
      lcd.print(F("0"));
      lcd.print(alarmTimeMinute);
    } else lcd.print(alarmTimeMinute);
  }
  delay(50);
  if (digitalRead(buttonSet) == LOW) {
    settingAlarm = false;
    alarmOn = true;
  }
}

void alarm() {
  lcd.home();
  lcd.print("     ALARM!     ");
  lcd.setCursor(0, 1);
  lcd.print("ALARM!    ALARM!");
  tone(buzzer, 488, 200);
  delay(100);
  noTone(buzzer);
  while (digitalRead(buttonUp) == LOW) {
    alarmOn = false;
  }
}