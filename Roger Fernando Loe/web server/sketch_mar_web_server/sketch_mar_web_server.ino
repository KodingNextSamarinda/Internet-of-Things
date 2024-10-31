#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED1 16
#define Buzzer 14


Servo myservo;


const String ssid = "hujan";
const String password = "pastidingin";

ESP8266WebServer server(80);
// ------------------------ BROWSER ----------------------------
const char DASBOARD[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <title> Introduction to Webserver </title>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
  </head>
  <body>
    <div class="container p-5 my-5 bg-dark text-white">
        <h1>Welcome to Webserver</h1>
        <p>this website will be used to control the ESP3266 <br>this website created by Mr. Ahmad </p>
        <a href="LEDON"><button id = "ledon" type="button" class="btn btn-primary"type="button" class="btn btn-primary">Turn On</button></a>
        <a href="LEDOFF"><button id = "ledoff" type="button" class="btn btn-danger">Turn Off</button></a>
    </div>

    
    <div class="container p-5 my-5 bg-dark text-white">
        <h1>SPIIIIIIINNNNNNNNN</h1>
        <p>Spin to win <br> ~kuru kuru ... kururin~ </p>
        <a href="SERVOON"><button id = "Servoon" type="button" class="btn btn-outline-primary">turn on</button></a>
        <a href="SERVOOFF"><button id = "Servooff" type="button" class="btn btn-outline-danger">turn off</button></a>
    </div>

  

        

  </body>
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
    $("#Servoon").click(function() {
      $.post("/SERVOON", function(data, status){
        alert(status);
      });
    });
    $("#Servooff").click(function() {
      $.post("/SERVOOFF", function(data, status){
        alert(status);
      });
        });

  </script>
</html>
)=====";

void indexPage() {
  String html = DASBOARD;
  server.send(200, "text/html", html);
}

// ------------------------ BROWSER ----------------------------

// ----------------------- FUNCTION -----------------------------

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

void SERVOon(){
  Serial.println("Status servo : ON");
  myservo.write(0);
  server.send(200, "text/html", "ON");
  
}

void SERVOoff(){
  Serial.println("Status servo : OFF");
  myservo.write(180);
  server.send(200, "text/html", "OFF");
  
}


// ----------------------- FUNCTION -----------------------------


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  delay(1000);

  myservo.attach(13);
  
  pinMode(Buzzer, OUTPUT);


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

  server.on("/", HTTP_GET, indexPage);
  server.on("/LEDON", HTTP_GET, LEDon);
  server.on("/LEDOFF", HTTP_GET, LEDoff);
  server.on("/SERVOON", HTTP_GET, SERVOon);
  server.on("/SERVOOFF", HTTP_GET, SERVOoff);
  


  server.begin();
  Serial.println("Server is running...");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

}
