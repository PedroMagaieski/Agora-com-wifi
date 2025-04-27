#include <ArduinoIoTCloud.h>
#include <WiFi.h>
const char SSID[]     = "Insira aqui o nome da rede wifi";
const char PASSWORD[] = "Insira aqui a senha do wifi";
#define MQ2_PIN 4 //pino do sensor
float SensorFumaca // variavel para armazenar os dados lidos no sensor

void setup() {
  //aqui leitura ddo sensor e escrita no monitor serial inicializado
  Serial.begin(9600);
  analogReadResolution(10);
  Serial.println("Sensor MQ-2 Inicializado!");
  pinMode(MQ2_PIN, INPUT);

  //aqui wifi inicializaddo
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  //aqui conexao com a cloud
  ArduinoCloud.begin(SSID, PASSWORD);
  ArduinoCloud.addProperty(SensorFumaca, READWRITE, ON_CHANGE, NULL);
  Serial.println("Conectado com Arduino Cloud ");
}

void loop() {
  //aqui armazena alertas na cloud
  SensorFumaca = analogRead(MQ2_PIN)
  if (SensorFumaca > 700) {
    digitalWrite(alertPin, HIGH);
  } else {
    digitalWrite(alertPin, LOW);
  }
  ArduinoCloud.update();

  //aqui printa no monitor serial
  Serial.print("Gas Value: ");
  Serial.println(analogRead(MQ2_PIN));
  delay(1000);
}