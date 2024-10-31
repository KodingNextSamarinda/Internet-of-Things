#include "DHT.h"
#define DHTPIN D7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup(){
  Serial.begin(115200);
  dht.begin();
}
void loop()
{ 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("  Temperature: ");
  Serial.print(t);
  Serial.print("°C ");
  delay(2000);
}
