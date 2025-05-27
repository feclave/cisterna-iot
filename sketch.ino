#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic_nivel = "cisterna/nivel";
const char* mqtt_topic_qualidade = "cisterna/qualidade";

WiFiClient espClient;
PubSubClient client(espClient);

// Pinos
const int TRIG_PIN = 12;
const int ECHO_PIN = 14;
const int TDS_PIN = 34;
const int BOMBA_PIN = 26;
const int VALVULA_PIN = 27;

void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Erro: ");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

long medirNivel() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duracao = pulseIn(ECHO_PIN, HIGH);
  long distancia = duracao * 0.034 / 2;
  return distancia;
}

int lerTDS() {
  int valor = analogRead(TDS_PIN);
  return map(valor, 0, 4095, 0, 1000); // simulação ppm
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BOMBA_PIN, OUTPUT);
  pinMode(VALVULA_PIN, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Tempo Sensor de Nível
  unsigned long startNivel = millis();
  long nivel = medirNivel();
  char nivel_str[8];
  sprintf(nivel_str, "%ld", nivel);
  client.publish(mqtt_topic_nivel, nivel_str);
  unsigned long endNivel = millis();
  Serial.print("Tempo sensor de nível (ms): ");
  Serial.println(endNivel - startNivel);

  // Tempo Sensor TDS
  unsigned long startTDS = millis();
  int tds = lerTDS();
  char tds_str[8];
  sprintf(tds_str, "%d", tds);
  client.publish(mqtt_topic_qualidade, tds_str);
  unsigned long endTDS = millis();
  Serial.print("Tempo sensor TDS (ms): ");
  Serial.println(endTDS - startTDS);

  Serial.print("Nível (cm): ");
  Serial.println(nivel);
  Serial.print("TDS (ppm): ");
  Serial.println(tds);

  // Tempo Atuador Bomba
  unsigned long startBomba = millis();
  if (nivel > 10 && tds < 500) {
    digitalWrite(BOMBA_PIN, HIGH);
  } else {
    digitalWrite(BOMBA_PIN, LOW);
  }
  unsigned long endBomba = millis();
  Serial.print("Tempo atuador bomba (ms): ");
  Serial.println(endBomba - startBomba);

  // Tempo Atuador Válvula
  unsigned long startValvula = millis();
  if (nivel > 10 && tds < 500) {
    digitalWrite(VALVULA_PIN, HIGH);
  } else {
    digitalWrite(VALVULA_PIN, LOW);
  }
  unsigned long endValvula = millis();
  Serial.print("Tempo atuador válvula (ms): ");
  Serial.println(endValvula - startValvula);

  Serial.println("--------------------------");
  delay(5000); // 5 segundos entre leituras
}