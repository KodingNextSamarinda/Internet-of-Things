#include <Servo.h>

Servo myservo;

#define buzzer 12

#define redlightpin 5
#define yellowlightpin 4
#define greenlightpin 0

#define Soil_sensor A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(2);  

  pinMode(buzzer, OUTPUT);

  pinMode(redlightpin, OUTPUT);
  pinMode(yellowlightpin, OUTPUT);
  pinMode(greenlightpin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(0);
  Serial.println("servo at 0 Degree");
  digitalWrite(buzzer,HIGH);
  digitalWrite(greenlightpin,HIGH);
  digitalWrite(yellowlightpin,LOW);
  digitalWrite(redlightpin,LOW);  

  tone(buzzer, 100, 100);
  delay(1000);

  myservo.write(90);
  Serial.println("servo at 90 Degree");
  digitalWrite(buzzer,LOW);
  tone(buzzer, 100, 100);
  digitalWrite(greenlightpin,LOW);
  digitalWrite(yellowlightpin,HIGH);
  digitalWrite(redlightpin,LOW);  
  delay(1000);

  myservo.write(180);
  Serial.println("servo at 180 Degree");
  digitalWrite(buzzer,HIGH);
  digitalWrite(greenlightpin,LOW);
  digitalWrite(yellowlightpin,LOW);
  digitalWrite(redlightpin,HIGH);  
  tone(buzzer, 100, 100);
  delay(1000);

  float moisture_percentage;
  moisture_percentage = (100.00 - ((analogRead(Soil_sensor)/1023.00) * 100.00));
  Serial.print("soil moisture(%)= ");
  Serial.print(moisture_percentage);
  Serial.println(" %");
  delay(1000);
}
