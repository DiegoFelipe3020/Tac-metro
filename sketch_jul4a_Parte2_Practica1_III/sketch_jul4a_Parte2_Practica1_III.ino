#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
const int HALL = 5;
const int sensorPin = 6;
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int rev = 0;
int giro = 0;
int verdadero = 0;
int pot = A2;
int potval = 0;
int time = 0;
int w = 200;
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(HALL, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("Contador de rev.");
  lcd.setCursor(0,1);
  lcd.print("No. De Rev: ");
  lcd.setCursor(0,2);
  lcd.setCursor(0, 3);
  lcd.print("rpm: ");
}
void loop() {
  while(digitalRead(sensorPin) ==  LOW){
    float rpm = (time * w);
    float rpm1 = (60/rpm)*(400/9);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(time);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(time);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(time);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(time); 
    if(digitalRead(HALL) == LOW){
      giro = 1;
      verdadero = 0;
    }else{
      verdadero = 1;
    }
    if(giro == 1&&verdadero == 1){
      giro = 0;
      verdadero = 0;
      delay(30);
      rev++;
    }
    lcd.setCursor(0,2);
    lcd.print(rev);
    potval = analogRead(pot);
    time = map(potval, 0, 1023,2 ,10);
    lcd.setCursor(5,3);
    lcd.print(rpm1);
  }
}