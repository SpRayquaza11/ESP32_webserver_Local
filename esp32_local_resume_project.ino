
  #include <WiFi.h>
  //need to install this library
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>


const char* ssid = "your ssid";
const char* password = "your password";

// Create AsyncWebServer object at port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <img src="resume">
</body>  
</html>)rawliteral";


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  //please note your image must alread be present in the local esp32 flash please use SPIFFS to upload the image
  server.on("/resume", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/resume.jpg", "image/jpg");
  });
  // Start server
  server.begin();
}
 
void loop(){
  
}
