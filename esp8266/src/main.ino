#include <Arduino.h>
#include <ESP8266WiFi.h>  // ESP8266 için Wi-Fi kütüphanesi
#include "lib/server/websocket.h"

// Wi-Fi bilgileri
const char* ssid = "Qwerty_asggsvsvsgz";
const char* password = "ThisLANisMyLAN";

// WebSocket sunucu bilgileri
const char* serverIp = "192.168.0.123";
const int serverPort = 8094;
const char* serverPath = "/";

void setup() {
    Serial.begin(115200);  // Seri haberleşmeyi başlat

    // WebSocket URL'sini oluştur
    String serverUrl = "ws://" + String(serverIp) + ":" + String(serverPort) + String(serverPath);
    
    // WebSocket bağlantısını kur
    setupWebSocket(ssid, password, serverUrl.c_str());

    // Sensörleri başlat
    setupBMP();
    setupGyro();
    setupDHT();
}

void loop() {
    sendData();            // Sensör verilerini topla ve gönder
    webSocket.poll();      // WebSocket olaylarını yönet
    delay(2000);           // 2 saniye bekle
}