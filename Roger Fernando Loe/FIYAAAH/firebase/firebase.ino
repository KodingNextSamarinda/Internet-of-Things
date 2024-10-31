#include <DHT.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Pin Definitions
int DHTPIN = 13;
int RedLed = 15;
int GreenLed = 4;
int buzzer = 2;

// DHT Sensor
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// WiFi and Firebase credentials
#define WIFI_SSID "hujan"
#define WIFI_PASSWORD "pastidingin"
#define FIREBASE_HOST "https://dht-roger-tempt-check-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "2ZgsW9WalSAVv1fHJQW0gNsVoHUdL6fzD9Gp9h4L"

ESP8266WebServer server(80);

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth firebaseAuth;
FirebaseConfig firebaseConfig;

// WiFi connection function
void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// LED and Buzzer control functions
void redledon() {
  Serial.println("Status RedLed : ON");
  digitalWrite(RedLed, HIGH);
  server.send(200, "text/html", "Red LED ON");
}

void redledoff() {
  Serial.println("Status RedLed : OFF");
  digitalWrite(RedLed, LOW);
  server.send(200, "text/html", "Red LED OFF");
}

void greenledon() {
  Serial.println("Status GreenLed : ON");
  digitalWrite(GreenLed, HIGH);
  server.send(200, "text/html", "Green LED ON");
}

void greenledoff() {
  Serial.println("Status GreenLed : OFF");
  digitalWrite(GreenLed, LOW);
  server.send(200, "text/html", "Green LED OFF");
}

void buzzeron() {
  Serial.println("Status buzzer : ON");
  digitalWrite(buzzer, HIGH);
  server.send(200, "text/html", "Buzzer ON");
}

void buzzeroff() {
  Serial.println("Status buzzer : OFF");
  digitalWrite(buzzer, LOW);
  server.send(200, "text/html", "Buzzer OFF");
}

void setup() {
  Serial.begin(9600);

  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  connectToWiFi();

  // Firebase configuration
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Initialize Firebase
  Firebase.begin(&firebaseConfig, &firebaseAuth);

  dht.begin();

  // Define server routes
  server.on("/buzzeron", HTTP_GET, buzzeron);
  server.on("/buzzeroff", HTTP_GET, buzzeroff);
  server.on("/redledon", HTTP_GET, redledon);
  server.on("/greenledon", HTTP_GET, greenledon);
  server.on("/redledoff", HTTP_GET, redledoff);
  server.on("/greenledoff", HTTP_GET, greenledoff);

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (Firebase.setFloat(firebaseData, "/Hasil_Pembacaan/Humidity", humidity)) {
    Serial.println("Humidity data sent successfully");
  } else {
    Serial.println("Failed to send humidity data");
    Serial.println("Error: " + firebaseData.errorReason());
  }

  if (Firebase.setFloat(firebaseData, "/Hasil_Pembacaan/Temperature", temperature)) {
    Serial.println("Temperature data sent successfully");
  } else {
    Serial.println("Failed to send temperature data");
    Serial.println("Error: " + firebaseData.errorReason());
  }

  delay(2000); // Adjust the delay as needed A fatal esptool.py error occurred: Failed to connect to ESP8266: Timed out waiting for packet header
}
