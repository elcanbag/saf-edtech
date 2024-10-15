#ifndef BMP_H
#define BMP_H

#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp;

void setupBMP() {
    if (!bmp.begin()) {
        Serial.println("Could not find BMP180 sensor!");
        while (1);
    }
}

float readPressure() {
    sensors_event_t event;
    bmp.getEvent(&event);
    return event.pressure;
}

float readBMPTemperature() {
    float bmpTemperature;
    bmp.getTemperature(&bmpTemperature);
    return bmpTemperature;
}

#endif
