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

// Limite para identificar um vazamento
const float leakThreshold = 4.0;  // Taxa acima disso é considerada vazamento

// Pinos virtuais
const int leakAlertLed = V3;  // LED de alerta visual
const int valveControlPin = V4;  // Switch para controle da válvula
const int leakSimulationPin = V2;  // Switch para simular vazamento

// Variável para estado da válvula
bool valveClosed = false;

// Funções para controlar os estados pelo Blynk
BLYNK_WRITE(V1) {                   // Botão para alta taxa de consumo
  highConsumption = param.asInt();  // Ativado quando o botão está pressionado
}

BLYNK_WRITE(V2) {           // Switch para simular vazamento
  gasLeak = param.asInt();  // Ativado quando o switch está ligado
  if (gasLeak) {
    Serial.println("Simulação de vazamento ativada!");
    closeValve();  // Fecha a válvula automaticamente
    Blynk.virtualWrite(leakSimulationPin, 0);  // Desliga o switch do vazamento
  }
}

BLYNK_WRITE(V4) {  // Switch no painel para controle manual da válvula
  valveClosed = param.asInt();
  if (valveClosed) {
    Serial.println("Válvula fechada manualmente.");
  } else {
    Serial.println("Válvula aberta manualmente.");
    gasLeak = false;  // Certifica-se de que o estado de vazamento é desativado
  }
}

// Função para piscar o LED de alerta
void blinkLeakAlert() {
  for (int i = 0; i < 5; i++) {
    Blynk.virtualWrite(leakAlertLed, 255);  // Liga o LED
    delay(500);                            // Aguarda 500 ms
    Blynk.virtualWrite(leakAlertLed, 0);   // Desliga o LED
    delay(500);                            // Aguarda 500 ms
  }
}

// Função para fechar a válvula
void closeValve() {
  if (!valveClosed) {  // Fecha a válvula somente se ainda estiver aberta
    valveClosed = true;
    Blynk.virtualWrite(valveControlPin, 1);  // Atualiza o estado do switch no painel
    Serial.println("Válvula fechada automaticamente devido a vazamento!");
    blinkLeakAlert();  // Pisca o LED de alerta
  }
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

  // Verifica se o intervalo passou
  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();

    // Determina a taxa de consumo com base no estado
    float currentRate = consumptionRate;

    if (valveClosed) {
      currentRate = 0;  // Consumo para quando a válvula está fechada
    } else if (highConsumption) {
      currentRate *= 3;  // Aumenta o consumo 3 vezes
    } else if (gasLeak) {
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
