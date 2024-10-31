#define Buzzer 14
#define led 0
#define ledy 12
#define ledx 13


void setup() {
  // put your setup code here, to run once:
  pinMode(Buzzer, OUTPUT);
  pinMode(led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Buzzer,HIGH);
  digitalWrite(led,HIGH);
  delay(2000);
  digitalWrite(Buzzer,LOW);
  digitalWrite(led,LOW);
  delay(2000);

  digitalWrite(Buzzer,HIGH);
  digitalWrite(ledy,HIGH);
  delay(2000);
  digitalWrite(Buzzer,LOW);
  digitalWrite(ledy,LOW);
  delay(2000);

  digitalWrite(Buzzer,HIGH);
  digitalWrite(ledx,HIGH);
  delay(2000);
  digitalWrite(Buzzer,LOW);
  digitalWrite(ledx,LOW);
  delay(2000);
}
