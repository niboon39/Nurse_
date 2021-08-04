#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int sensor1 = A1 ; // sensor_1
int sensor2 = A2 ; // sensor_2
int sensor3 = A3 ; // sensor_3

int buzzer = 2 ; // Buzzer
int led    = 3 ; // Led
int count1 = 0 , count2 = 0 , count3 = 0 ;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensor_IR(int sensor) {
  int val = analogRead(sensor);
  return val ;
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600) ;
  lcd.init();
  lcd.backlight();

  pinMode(buzzer , OUTPUT) ;
  pinMode(led , OUTPUT) ;
  digitalWrite(buzzer, HIGH);

}



void loop() {

  // put your main code here, to run repeatedly:
  int value_sen1 = sensor_IR(sensor1) ;
  int value_sen2 = sensor_IR(sensor2) ;
  int value_sen3 = sensor_IR(sensor3) ;
  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.setCursor(3, 0);
  lcd.print(count1) ;

  lcd.setCursor(8, 0);
  lcd.print("S2:");
  lcd.setCursor(11, 0);
  lcd.print(count2) ;

  lcd.setCursor(0, 1);
  lcd.print("LED:");
  lcd.setCursor(4, 1);
  lcd.print("Off") ;

  lcd.setCursor(8, 1);
  lcd.print("Buz:");
  lcd.setCursor(12, 1);
  lcd.print("Off") ;


  if ( value_sen1 > 600 && value_sen2 > 600 ) {
    Serial.println("ETT & Tracheostomy : On") ;
    Serial.print("Sensor_1 : ");
    Serial.println(value_sen1) ;
    Serial.print("Sensor_2 : ");
    Serial.println(value_sen2) ;
    Serial.print("Sensor_3 : ");
    Serial.println(value_sen3) ;
    count1 = 0 ;
    count2 = 0 ;
    delay(900);
    digitalWrite(led , LOW) ;
  }
  else if ((value_sen1 < 55 && value_sen3 < 60) || (value_sen2 < 70 && value_sen3 < 60)) {
    lcd.clear();
    count1++ ;
    count2++ ;
    digitalWrite(led , HIGH) ;

    lcd.setCursor(0, 0);
    lcd.print("S1:");
    lcd.setCursor(3, 0);
    lcd.print(count1) ;

    lcd.setCursor(8, 0);
    lcd.print("S2:");
    lcd.setCursor(11, 0);
    lcd.print(count2) ;

    lcd.setCursor(0, 1);
    lcd.print("LED:");
    lcd.setCursor(5, 1);
    lcd.print("On") ;

    lcd.setCursor(8, 1);
    lcd.print("Buz:");
    lcd.setCursor(12, 1);
    lcd.print("Off") ;



    Serial.print("Count sensor 1 : ") ;
    Serial.println(count1) ;
    Serial.print("Count sensor 2 : ") ;
    Serial.println(count2) ;
    delay(1000);


    if (count1 == 10 || count2 == 10) {
      count1 = 0 ;
      count2 = 0 ;
      digitalWrite(buzzer , LOW) ;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("S1:");
      lcd.setCursor(3, 0);
      lcd.print(count1) ;

      lcd.setCursor(8, 0);
      lcd.print("S2:");
      lcd.setCursor(11, 0);
      lcd.print(count2) ;

      lcd.setCursor(0, 1);

      lcd.print("LED:");
      lcd.setCursor(5, 1);
      lcd.print("On") ;

      lcd.setCursor(8, 1);
      lcd.print("Buz:");
      lcd.setCursor(12, 1);
      lcd.print("On") ;

      delay(2000) ;
      digitalWrite(buzzer , HIGH) ;

      lcd.print("LED:");
      lcd.setCursor(5, 1);
      lcd.print("Off") ;
      lcd.setCursor(8, 1);
      lcd.print("Buz:");
      lcd.setCursor(12, 1);
      lcd.print("Off") ;
      digitalWrite(led , LOW) ;
      lcd.clear();
    }
  }

  else {
    Serial.println("Not found sensor") ;
  }
}
