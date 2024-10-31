#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const String ssid = "hujan";
const String password = "pastidingin";
int buzzer = 14;
int led = 4;


ESP8266WebServer server(80);

void turnOnBuzzer() {
  digitalWrite(buzzer, HIGH);
  server.send(200, "text/html", "ON");
}

void turnOffBuzzer() {
  digitalWrite(buzzer, LOW);
  server.send(200, "text/html", "OFF");
}

void turnOnLed() {
  digitalWrite(led, HIGH);
  server.send(200, "text/html", "ON");
}

void turnOffLed() {
  digitalWrite(led, LOW);
  server.send(200, "text/html", "OFF");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  delay(1000);

//  connect to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/on", HTTP_GET, turnOnBuzzer);
  server.on("/off", HTTP_GET, turnOffBuzzer);
  server.on("/ledon", HTTP_GET, turnOnLed);
  server.on("/ledoff", HTTP_GET, turnOffLed);

  server.begin();
  Serial.println("Server is running...");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

}