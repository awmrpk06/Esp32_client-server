#include "WiFi.h"
#include "ESPAsyncWebServer.h"
 
const char* ssid = "esp32";
const char* password =  "12345678";
 
AsyncWebServer server(80);
 
void setup(){
  Serial.begin(115200);
 
   // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
 
    int paramsNr = request->params();
    Serial.println(paramsNr);
 
    for(int i=0;i<paramsNr;i++){
 
        AsyncWebParameter* p = request->getParam(i);
        Serial.print("Param name: ");
        Serial.println(p->name());
        Serial.print("Param value: ");
        Serial.println(p->value());
        Serial.println("------");
    }
 
    request->send(200, "text/plain", "message received");
  });
 
  server.begin();
}
 
void loop(){}
