#define BLYNK_TEMPLATE_ID "TMPL2mwuk3AIk"
#define BLYNK_TEMPLATE_NAME "Balança IOT"
#define BLYNK_AUTH_TOKEN "544-O1Z8zQnJfUDyehkjMksGstN9EUB2"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Credenciais Wi-Fi
const char* ssid = "Wifi Casa_2.4Ghz";   // Substitua por sua rede Wi-Fi
const char* pass = "boaventurabotelho";  // Substitua pela senha do Wi-Fi

unsigned long lastUpdate = 0;                // Armazena o tempo da última atualização
const unsigned long updateInterval = 10000;  // Intervalo de 10 segundos

// Variável para o nível do botijão de gás
float gasLevel = 30.0;

// Taxa de consumo padrão
float consumptionRate = 0.3;

// Estados de simulação
bool highConsumption = false;
bool gasLeak = false;

// Funções para controlar os estados pelo Blynk
BLYNK_WRITE(V1) {                   // Botão para alta taxa de consumo
  highConsumption = param.asInt();  // Ativado quando o botão está pressionado
}

BLYNK_WRITE(V2) {           // Botão para simular vazamento
  gasLeak = param.asInt();  // Ativado quando o botão está pressionado
}

void setup() {
  // Inicializa o monitor serial
  Serial.begin(9600);

  // Conecta ao Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Conectando ao Blynk...");
}

void loop() {
  // Mantém a conexão com o Blynk
  Blynk.run();

  // Verifica se 1 minuto se passou
  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();

    // Determina a taxa de consumo com base no estado
    float currentRate = consumptionRate;

    if (highConsumption) {
      currentRate *= 3;  // Aumenta o consumo 3 vezes
    }

    if (gasLeak) {
      currentRate = 5.0;  // Consumo muito rápido por vazamento
    }

    // Simula o consumo de gás
    gasLevel -= currentRate;

    // Garante que o nível não fique negativo
    if (gasLevel < 0) {
      gasLevel = 0;
    }

    // Envia o nível do gás para o pino virtual V0 no Blynk
    Blynk.virtualWrite(V0, gasLevel);

    // Exibe no monitor serial para depuração
    Serial.print("Taxa de Consumo: ");
    Serial.print(currentRate);
    Serial.print(" | Nível do Gás: ");
    Serial.println(gasLevel);
  }
}
