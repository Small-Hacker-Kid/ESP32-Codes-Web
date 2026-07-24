#include <Arduino.h>
#include <WiFi.h>

const char* SSID = "Typfobieloops";
const char* password = "Snaponmerightnow";

unsigned long previousMillis = 0;
unsigned long interval = 7000;

/*Assign a specific static IP address to the ESP32
IPAddress local_IP(172, 20, 10, 10);
IPAddress gateway(172, 20, 10, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);*/

void initWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, password);
  Serial.print("Connecting to WiFi ..");
  while(WiFi.status() != WL_CONNECTED){
    for(int i = 0; i < 5; i++){
      Serial.print('.');
      delay(1000);
    }
    Serial.print(WiFi.status());
  }
  Serial.println(WiFi.localIP());
}

void setup(){
  /*if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)){
    Serial.println("STA failed to configure");
  }*/
  Serial.begin(115200);
  WiFi.begin(SSID, password);
  /*initWiFi();
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
  Serial.println(WiFi.subnetMask());
  Serial.println(WiFi.gatewayIP());*/
}
void loop(){
  unsigned long currentMillis = millis();
  if((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval)){
    Serial.print(millis()/1000);
    Serial.print("s");
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}



/*

Unnecessary Replaced Code

Serial.println("Scan start");

  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0){
    Serial.println("No networks found");
  } else{
    Serial.print(n);
    Serial.println(" Networks found");
    for(int i = 0; i < n; i++){
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" )");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }

See what Wifi networks ESP32 can find

int n = WiFi.scanNetworks();
  if(n == 0){
    Serial.println("No Networks found");
  } else {
    Serial.printf("%d netowrks found\n", n);
    for(int i = 0; i < n; i++){
      Serial.printf("%d: %s (%d dBm)\n",
      i + 1,
      WiFi.SSID(i).c_str(),
      WiFi.RSSI(i));
    }
  }*/