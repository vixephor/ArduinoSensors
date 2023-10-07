#include <DHT.h>                // подключаем библиотеку датчика температуры и влажности
#define pinDHT 2                // датчик подключен к пину 2
#define typDHT22 DHT22          // хуй его знает что это
DHT mojeDHT(pinDHT, typDHT22);  // это вроде функция которая говорит библиотеке на каком пине установлен модуль и какой

#include <MQ135.h>  // библиотека для датчика газа
#define pinA A0     // Аналоговый пин
#define pinD 8      // цифровой
MQ135 senzorMQ = MQ135(pinA);

// библиотека для БМП
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#define BMP280_ADRESA (0x76)
Adafruit_BMP280 bmp;
int correction = 32; // какая то магия





void setup() {
  Serial.begin(9600);                                            // скорость передачи порта, такой же должен быть и в самой программой
  mojeDHT.begin();                                               // включаем датчик DHT
  attachInterrupt(digitalPinToInterrupt(pinD), prerus, RISING);  // подключаем датчик газа MQ
  if (!bmp.begin(BMP280_ADRESA)) {
    Serial.println("BMP280 senzor nenalezen, zkontrolujte zapojeni!");
    while (1)
      ;
  }
}
/*
float tep - температура
float vlh - влажность
float ppm - концетрация воздуха
float teplota - температура с датчика БМП
float tlak - Давление в гигапаксалях
float sensorValue - УФ сенсор
*/
void loop() {
  // DHT датчик
  float tep = mojeDHT.readTemperature();  // температура
  float vlh = mojeDHT.readHumidity();
  if (isnan(tep) || isnan(vlh)) {
    Serial.println("Какая-то ошибка при чтении инфы с датчика, проверь колёсики дебик");
  } else {
    Serial.print("температура: ");
    Serial.print(tep);
    Serial.print(" цельсий ");
    Serial.print("влажность ");
    Serial.print(vlh);
    Serial.println("  %");
    delay(1000);
  }
  /////////////////////////////////////
  // Датчик Газа
  float ppm = senzorMQ.getPPM();
  long time = millis() / 1000;
  Serial.print("Концетрация воздуха");
  Serial.println(ppm);
  delay(1000);
  /////////////////////////////////////

  // Датчик давления и температуры БМП
   float teplota = bmp.readTemperature();
   float tlak = (bmp.readPressure()/100.00) + correction;
   Serial.print("температура: ");
    Serial.print(teplota);
    Serial.print(" цельсий ");
    Serial.print("давление ");
    Serial.print(tlak);
    Serial.println("гПа");
    delay(1000);
   /////////////////////////////////////
   // УФ детектор


  float sensorVoltage; 
  float sensorValue;
 
  sensorValue = analogRead(A1);
  sensorVoltage = sensorValue/1024*5.0;
  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.print("        sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  delay(1000);
   
}
void prerus() {
  Serial.println("Detekovano prekroceni hranice!");
}
