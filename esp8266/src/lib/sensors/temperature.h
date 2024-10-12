#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <DHT.h>

#define DHTPIN D5      // DHT11 is connected to pin D5
#define DHTTYPE DHT11  // We are using the DHT11 sensor

DHT dht(DHTPIN, DHTTYPE);

void setupDHT() {
    dht.begin();
}

float readHumidity() {
    return dht.readHumidity();
}

float readTemperature() {
    return dht.readTemperature();
}

#endif // TEMPERATURE_H
