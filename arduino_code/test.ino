#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define DHTPIN 8     
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP280 bmp; 

void setup() {
  Serial.begin(9600); 
  dht.begin();         

  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring or try a different address!!");
    while (1);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, 
                  Adafruit_BMP280::SAMPLING_X2, 
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16, 
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  delay(2000);
  
  float temperature = dht.readTemperature(); 
  float humidity = dht.readHumidity();       
  float pressure = bmp.readPressure();

  if (!isnan(temperature) && !isnan(humidity) && !isnan(pressure)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" , Humidity: ");
    Serial.print(humidity);
    Serial.print(" , Pressure: ");
    Serial.print(pressure);
    Serial.println(" ");
  } else {
    Serial.println("Failed to read from DHT22 and BMP280!");
  }

  delay(60000); 
}
