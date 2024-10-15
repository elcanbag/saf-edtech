#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "lib/server/websocket.h"

const char* ssid = "Qwerty_asggsvsvsgz";
const char* password = "ThisLANisMyLAN";

const char* serverIp = "192.168.0.148";
const int serverPort = 8094;
const char* serverPath = "/";

void setup() {
    Serial.begin(115200);

    String serverUrl = "ws://" + String(serverIp) + ":" + String(serverPort) + String(serverPath);
    
    setupWebSocket(ssid, password, serverUrl.c_str());

    setupBMP();
    setupGyro();
    setupDHT();
}

void loop() {
    sendData();
    webSocket.poll();
    delay(2000);
}
