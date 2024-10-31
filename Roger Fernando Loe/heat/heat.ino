#define PIR_SENSOR 13

#include <Servo.h>

Servo myservo;

#define buzzer 12

#define redlightpin 5
#define yellowlightpin 4
#define greenlightpin 0

#define Soil_sensor A0

void BuzzerOn() {
  digitalWrite(buzzer, HIGH);
  tone(buzzer,50,50);
  digitalWrite (redlightpin, HIGH);
  digitalWrite (greenlightpin, LOW);
  Serial.println("there's a Motion Detected");
  delay(500);
}

void BuzzerOff () {
  digitalWrite(buzzer, LOW);
  tone(buzzer,50,50);
  digitalWrite (greenlightpin, HIGH);
  digitalWrite (redlightpin, LOW);
  Serial.println("there's NO Motion Detected");
  delay(500);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(2);  

  pinMode(PIR_SENSOR,INPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(redlightpin, OUTPUT);
  pinMode(yellowlightpin, OUTPUT);
  pinMode(greenlightpin, OUTPUT);

}

void loop() {

  // put your main code here, to run repeatedly:
  long Status = digitalRead(PIR_SENSOR);
  if (Status == HIGH){
    BuzzerOn();
  }
  else{
    BuzzerOff();
  }
  
  myservo.write(0);
  Serial.println("servo at 0 Degree");
  digitalWrite(yellowlightpin,LOW);

  delay(1000);

  myservo.write(90);
  Serial.println("servo at 90 Degree");
  digitalWrite(yellowlightpin,HIGH);
  delay(1000);



  float moisture_percentage;
  moisture_percentage = (100.00 - ((analogRead(Soil_sensor)/1023.00) * 100.00));
  Serial.print("soil moisture(%)= ");
  Serial.print(moisture_percentage);
  Serial.println(" %");
  delay(1000);
}
