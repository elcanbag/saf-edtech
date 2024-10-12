#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include "lib/sensors/bmp.h"
#include "lib/sensors/gyro.h"
#include "lib/sensors/temperature.h"

using namespace websockets;

WebsocketsClient webSocket;

// Wi-Fi'ye bağlanma fonksiyonu
void connectToWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Wi-Fi'ye bağlanılıyor...");
    }
    Serial.println("Wi-Fi'ye bağlanıldı");
}

// WebSocket sunucusuna bağlanma fonksiyonu
void connectWebSocket(const char* serverUrl) {
    if (webSocket.connect(serverUrl)) {
        Serial.println("WebSocket bağlandı!");
    } else {
        Serial.println("WebSocket bağlantısı başarısız!");
    }
}

// WebSocket kurulumu
void setupWebSocket(const char* ssid, const char* password, const char* serverUrl) {
    connectToWiFi(ssid, password);  // Wi-Fi'ye bağlan
    connectWebSocket(serverUrl);    // WebSocket sunucusuna bağlan
}

// Sensör verilerini WebSocket üzerinden gönderme ve aynı zamanda seri monitöre yazdırma
void sendData() {
    // Sensör verilerini oku
    float humidity = readHumidity();
    float temperature = readTemperature();
    float pressure = readPressure();
    sensors_event_t accel = readGyroAcceleration();

    // WebSocket üzerinden verileri gönder ve aynı zamanda seri monitöre yazdır
    if (webSocket.available()) {
        String hum = "hum:" + String(humidity, 2);
        String temp = "temp:" + String(temperature, 2);
        String press = "pressure:" + String(pressure, 2);
        String accelX = "x:" + String(accel.acceleration.x, 2);
        String accelY = "y:" + String(accel.acceleration.y, 2);
        String accelZ = "z:" + String(accel.acceleration.z, 2);
        String lat = "lat:42.6448998";
        String longg = "longg:42.6448998";
        String date = "date:10/02/2024";
        String internalTemp = "internalTemp:25";

        // WebSocket üzerinden gönder
        webSocket.send(hum);
        webSocket.send(temp);
        webSocket.send(press);
        webSocket.send(accelX);
        webSocket.send(accelY);
        webSocket.send(accelZ);
        webSocket.send(lat);
        webSocket.send(longg);
        webSocket.send(date);
        webSocket.send(internalTemp);

        // Seri monitöre yazdır
        Serial.println(hum);
        Serial.println(temp);
        Serial.println(press);
        Serial.println(accelX);
        Serial.println(accelY);
        Serial.println(accelZ);
        Serial.println(lat);
        Serial.println(longg);
        Serial.println(date);
        Serial.println(internalTemp);
    }
}

#endif // WEBSOCKET_H
