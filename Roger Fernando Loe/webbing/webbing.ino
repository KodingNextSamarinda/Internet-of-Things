#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const String ssid = "hujan";
const String password = "pastidingin";

ESP8266WebServer server(80);
// ------------------------ BROWSER ----------------------------
const char DASBOARD[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard Roger</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.11.8/dist/umd/popper.min.js" integrity="sha384-I7E8VVD/ismYTF4hNIPjVp/Zjvgyol6VFvRkX/vR+Vc4jQkC+hVqc2pM8ODewa9r" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.min.js" integrity="sha384-0pUGZvbkm6XF6gxjEnlmuGrJXVbNuzT9qBBavbLwCsOGabYfZo0T0to5eqruptLy" crossorigin="anonymous"></script>
</head>
<body>
    <div class="container p-5 my-5 bg-dark text-white">
        <h1>Welcome to webserver</h1>
        <p>this website is goofy <br> this website is oonga booga</p>
        <button type="button" class="btn btn-outline-primary">turn on</button>
        <button type="button" class="btn btn-outline-danger">turn off</button>
    </div>
</body>
</html>
)=====";

void indexPage() {
  String html = DASBOARD;
  server.send(200, "text/html", html);
}

// ------------------------ BROWSER ----------------------------




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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

  server.on("/", HTTP_GET, indexPage);
  server.begin();
  Serial.println("Server is running...");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

}
