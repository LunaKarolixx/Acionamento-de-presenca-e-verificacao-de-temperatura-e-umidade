#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Arduino.h>


const char* WIFI_SSID = "WIFI 2.4G";
const char* WIFI_SENHA = "";

const char* MQTT_SERVER_IP = "";
const int MQTT_PORT = 1883;

const char* MQTT_TOPIC = "/ESP32/SENSORES";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
int counter = 0;

// Função para conectar ao Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando-se ao ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_SENHA);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("Endereço IP do ESP32: ");
  Serial.println(WiFi.localIP());
}

// Função para reconectar ao MQTT (caso a conexão caia)
void reconnect() {
  // Loop até reconectar
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    
    // Crie um ID de cliente único
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // Tenta conectar
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado!");
      
      // (Opcional) Se inscrever em tópicos, se precisar
      // client.subscribe("topico/de/comando");

    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      // Espera 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
}

// Definição e iniciação do DHT11
#define pinDHT11 4
#define DHTTYPE DHT11
DHT dht(pinDHT11, DHTTYPE);

// Definição e iniciação de variável e função para detecção de movimento com sensor PIR
#define pinSensor 21
bool movimento = false;
void movimentacao() {
  movimento = true;
}


void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando dispositivo.");

  setup_wifi();
  client.setServer(MQTT_SERVER_IP, MQTT_PORT);

  pinMode(pinSensor, INPUT_PULLUP);
  attachInterrupt(pinSensor, movimentacao, RISING);

  dht.begin();

  Serial.println("Setup finalizado com sucesso.");
}

void loop() {
  delay(2000);

  // Parte do MQTT
  if (!client.connected()) {
    reconnect();
  }

  client.loop();


  // Parte do DHT11
  float temp = dht.readTemperature();
  float umid = dht.readHumidity();

  if (isnan(temp) || isnan(umid)) {
     Serial.println("Erro ao ler os dados do DHT11.");
   } else {
     Serial.print("Temperatura: ");
     Serial.println(temp);

     Serial.print("Umidade: ");
     Serial.println(umid);
   }


  // Envio da mensagem MQTT
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    counter++;

    // Cria a mensagem
    String msg = "Movimento detectado: " + String(movimento) + "\nTemperatura do comodo: " + String(temp) + "\nUmidade do comodo: " + String(umid);

    // Converte a String para char array (necessário para publish)
    char msgBuffer[100];
    msg.toCharArray(msgBuffer, 100);

    // Publica a mensagem
    client.publish(MQTT_TOPIC, msgBuffer);
    
    Serial.print("Mensagem publicada no tópico [");
    Serial.print(MQTT_TOPIC);
    Serial.print("]: ");
    Serial.println(msg);
  }


  // Reset do PIR
  if(movimento){
    movimento = false;
  }
}

