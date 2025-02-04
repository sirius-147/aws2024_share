#include <DHT.h>

#define DHTPIN 8       // DHT22 ������ ����� �� ��ȣ
#define DHTTYPE DHT22  // DHT ���� ����: DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  // �ø��� ��� ����
  dht.begin();         // DHT ���� �ʱ�ȭ
}

void loop() {
  float temperature = dht.readTemperature(); // ���� �µ� �б�
  float humidity = dht.readHumidity();       // ���� �б�

  // ���� �бⰡ �������� ��� ������ ����
  if (!isnan(temperature) && !isnan(humidity)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" , Humidity: ");
    Serial.print(humidity);
    Serial.println(" ");
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }

  delay(60000); // 5��(300,000ms) ���
}
