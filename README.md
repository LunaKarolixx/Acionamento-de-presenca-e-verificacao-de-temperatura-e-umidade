# Acionamento de Presença e verificação de temperatura e umidade

Este projeto, desenvolvido para matéria Plataforma de Hardware em IoT do curso de Tecnologia da Informação, estabelece um sistema de monitoramento ambiental básico e eficaz. Utilizamos o microcontrolador ESP32 para coletar dados de **presença**, **temperatura** e **umidade**, e a arquitetura **MQTT** para comunicação e a plataforma **Node-RED** para processamento de lógica de alarme e visualização em Dashboard.

---

## Arquitetura do Projeto

O sistema opera em uma estrutura de publicação, garantindo comunicação assíncrona:

1.  **Sensores:** Os sensores DHT11 e HC-SR501 coleta de dados.
2.  **Microcontrolador (Publish):** O ESP32 lê os sensores e publica os dados via MQTT.
3.  **Mosquitto Broker:** Gerencia a comunicação, recebendo e distribuindo as mensagens.
4.  **Node-RED:** Recebe as mensagens, aplica a lógica de alarme e exibe o Dashboard.

---

## Hardware e Componentes

| Componente | Função | Modelo | Característica |
| :--- | :--- | :--- | :--- |
| **Sensor de Presença** | Detecção de movimento. | **HC-SR501** | Saída Digital (1/0). |
| **Sensor T/H** | Medição de Temperatura e Umidade. | **DHT11** | Temperatura $0^\circ C - 50^\circ C$, Umidade $20\% - 90\%$. |
| **Microcontrolador** | Processamento e Conectividade. | **ESP32** | Conexão Wi-Fi e Cliente MQTT. |

---

## Execução

Para executar o projeto, você precisará:

* **Mosquitto Broker:** Servidor MQTT em execução.
* **Node-RED:** Plataforma de programação visual ('npm install -g --
unsafe-perm node-red' , 'node-red').
* **Node-RED Dashboard:** Pacote de nós instalado na paleta ('npm install node-red-dashboard').
* **Firmware:** Código para o microcontrolador (ex: Arduino IDE com bibliotecas para MQTT e DHT).

---

## Comunicação MQTT

O Node-RED deve se inscrever nos seguintes tópicos para receber os dados:

| Dado | Tópico | Formato |
| :--- | :--- | :--- |
| Presença | iot/casa/presenca | 1 (Movimento) ou 0 (Parado) |
| Temperatura | iot/casa/temperatura | 23.5 (Float) |
| Umidade | iot/casa/umidade | 62 (Int) |

---

## Lógica de Alarme no Node-RED

A lógica de alerta é implementada principalmente em nós function no Node-RED e exibida nos nós do Dashboard.

### 1. Alarme de Detecção de Presença (HC-SR501)

* **Condição:** Formato igual a **1** (movimento).
* **Ação:** Exibir **"PRESENÇA DETECTADA!"** no Dashboard.

### 2. Alarme de Alta ou Baixa Temperatura (DHT11)

* **Alerta Baixo:** Temperatura **$< 20^\circ C$**.
* **Alerta Alto:** Temperatura **$> 25^\circ C$**.
* **Ação:** Exibir o alerta correspondente **"TEMP. ALTA"** ou **"TEMP. BAIXA"**).

### 3. Alarme de Umidade Elevada (DHT11)

* **Condição:** Umidade **$> 50\%$**.
* **Ação:** Exibir **"UMIDADE ALTA"**.
