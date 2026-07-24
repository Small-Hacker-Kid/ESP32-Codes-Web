//A seperate HTML file must be in a /data file in the directories with it all flashed for this to work
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>


const char* SSID = "ESP32";
const char* password = "password";

WebServer server(80);

void handleRoot(){
  File file = LittleFS.open("/index.html", "r");

  if(!file){
    server.send(404, "text/plain", "File not found");
    return;
  }

  server.streamFile(file, "text/html");
  file.close();
}
void off27(){
  File file = LittleFS.open("/27off.html", "r");

  server.streamFile(file, "text/html");
  file.close();

}

void setup(){
  Serial.begin(115200);

  if(!LittleFS.begin()){
    Serial.println("LittleFS failed");
    return;
  }
  WiFi.mode(WIFI_AP);
  WiFi.softAP(SSID, password);

  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/27/off", off27);
  server.begin();
  
  Serial.println("Web server started");
}

void loop(){
  server.handleClient();
}