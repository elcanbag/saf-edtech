#include "lib/sensors/bmp.h"
#include "lib/sensors/gyro.h"
#include "lib/sensors/temperature.h"

void setup() {
  Serial.begin(9600);  // Start serial communication

  // Initialize the sensors
  setupBMP();
  setupGyro();
  setupDHT();
}

void loop() {
  delay(2000);
  // Read and display data from the DHT11 sensor (temperature and humidity)
  float humidity = readHumidity();
  float dhtTemperature = readTemperature();
  Serial.print("DHT Temperature: ");
  Serial.print(dhtTemperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Read and display data from the BMP180 sensor (pressure and temperature)
  float pressure = readPressure();
  float bmpTemperature = readBMPTemperature();
  Serial.print("BMP Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa, BMP Temperature: ");
  Serial.print(bmpTemperature);
  Serial.println(" °C");

  // Read and display data from the MPU6050 sensor (acceleration)
  sensors_event_t accel = readGyroAcceleration();
  Serial.print("Acceleration (m/s^2): X=");
  Serial.print(accel.acceleration.x);
  Serial.print(", Y=");
  Serial.print(accel.acceleration.y);
  Serial.print(", Z=");
  Serial.println(accel.acceleration.z);

  delay(2000);  // Wait for 2 seconds before reading the values again
}
