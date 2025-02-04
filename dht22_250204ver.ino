#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

// DHT Sensor
#define DHTPIN 8     
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

//BMP280 Sensor
#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)
Adafruit_BMP280 bmp; //I2C

void setup() {
  Serial.begin(9600); 
  dht.begin();         // DHT 
  unsigned status = bmp.begin();

  if (!status) {
    Serial.println(F("Could not find a vaild BMP280 sensor, check wiring or try a different address!!"));
    while (1) delay(10);
  }

  // BMP280 default settings
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, 
            Adafruit_BMP280::SAMPLING_X2, 
            Adafruit_BMP280::SAMPLING_X16
            Adafruit_BMP280::FILTER_X16, 
            Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  // Wait 2 seconds between measurements
  delay(2000);
  
  //Reading data from DHT22 & BMP280
  float temperature = dht.readTemperature(); 
  float humidity = dht.readHumidity();       
  float pressure = bmp.readPressure();


  // ���� �бⰡ �������� ��� ������ ����
  if (!isnan(temperature) && !isnan(humidity) && !isnan(pressure)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" , Humidity: ");
    Serial.print(humidity);
    Serial.print(" , Pressure: ");
    Serial.print(pressure)
    Serial.println(" ")
  } else {
    Serial.println("Failed to read from DHT22 and BMP280!");
  }

  delay(60000); // 5��(300,000ms) ���
}
