#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int DHTPIN = 13;

int LED1 = 15;

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const String ssid = "hujan";
const String password = "pastidingin";

ESP8266WebServer server(80);
// ------------------------ BROWSER ----------------------------
const char DASBOARD[] PROGMEM = R"=====(
<!doctype html>
<html lang="en">
  <head>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>


    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">

    <title>Hello, world!</title>
  </head>
  <body>
    <div class="position-relative overflow-hidden p-3 p-md-5 m-md-3 text-center bg-light">
      <div class="col-md-5 p-lg-5 mx-auto my-5">
        <h1 class="display-4 fw-normal">DHT11 Sensor</h1>
        <p class="lead fw-normal">sponsored by the IPC.</p>

        <h3>Temperature : <span class = "celcius">0</span> °C </h3>
        <h3>humidity : <span class = "humidity">0</span> % </h3>


      </div>
      <div class="product-device shadow-sm d-none d-md-block"></div>
      <div class="product-device product-device-2 shadow-sm d-none d-md-block">
      </div>
      <div class="container p-5 my-5 bg-dark text-white">
        <h1>LED </h1>
        <p>Control The LED <br> ~kuru kuru ... kururin~ </p>
        <a href="LEDON"><button id = "ledon" type="button" class="btn btn-primary"type="button" class="btn btn-primary">Turn On</button></a>
        <a href="LEDOFF"><button id = "ledoff" type="button" class="btn btn-danger">Turn Off</button></a>
    </div>
    </div>
    <script>
    //  Javascript for catch triggered from button and execute the instruction.
  <script>
      $("#ledon").click(function() {
        $.post("/LEDON", function(data, status){
          alert(status);
        });
      });
      $("#ledoff").click(function() {
        $.post("/LEDOFF", function(data, status){
          alert(status);
        });
      });
      setInterval(function() {
        $.get("/gettemperature", function(data, status){
          $(".celcius").text(data);
        });
      }, 2000);
      setInterval(function() {
        $.get("/gethumidity", function(data, status){
          $(".humidity").text(data);
        });
      }, 2000);
    </script>
  </body>
</html>
)=====";

void indexPage() {
  String html = DASBOARD;
  server.send(200, "text/html", html);
}

// ------------------------ BROWSER ----------------------------
void temp_check(){
  float temp = dht.readTemperature();
  Serial.print(" Temperature : ");
  Serial.print(temp);
  Serial.println("°c");
  server.send(200, "text/plain", String(temp,2));
}
void humid_check(){
  float humid = dht.readHumidity();
  Serial.print("humid : ");
  Serial.print(humid);
  Serial.println("%");
  server.send(200, "text/plain", String(humid,2));
}
void LEDon(){
  Serial.println("Status LED : ON");
  digitalWrite(LED1, HIGH);
  server.send(200, "text/html", "ON");
  
}

void LEDoff(){
  Serial.println("Status LED : OFF");
  digitalWrite(LED1, LOW);
  server.send(200, "text/html", "OFF");
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);

  pinMode(LED1, OUTPUT);
  delay(1000);

//  connect to wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

   dht.begin();

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  

  server.on("/", HTTP_GET, indexPage);
  server.on("/gettemperature", HTTP_GET, temp_check);
  server.on("/gethumidity", HTTP_GET, humid_check);
  server.on("/LEDON", HTTP_GET, LEDon);
  server.on("/LEDOFF", HTTP_GET, LEDoff);
  server.begin();
  Serial.println("Server is running...");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

}