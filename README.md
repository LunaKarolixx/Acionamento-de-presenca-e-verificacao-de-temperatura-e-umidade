# Acionamento de Presença e verificação de temperatura e umidade

Este projeto, desenvolvido para matéria Plataforma de Hardware em IoT do curso de Tecnologia da Informação, estabelece um sistema de monitoramento ambiental básico e eficaz. Utilizamos o microcontrolador ESP32 para coletar dados de **presença**, **temperatura** e **umidade**, e a arquitetura **MQTT** para comunicação e a plataforma **Node-RED** para processamento de lógica de alarme e visualização em Dashboard.

![WhatsApp Image 2025-12-01 at 20 26 30](https://github.com/user-attachments/assets/58a9d20a-92de-43be-8ec5-0dd3364a4750)
![WhatsApp Image 2025-12-01 at 20 26 26](https://github.com/user-attachments/assets/f68d283d-0a80-4f7a-9c30-c22aeb60570d)

---

## Arquitetura do Projeto

O sistema opera em uma estrutura de publicação, garantindo comunicação assíncrona:

1.  **Sensores:** Os sensores DHT11 e HC-SR501 coleta os dados.
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

## Lógica de Alarme no Node-RED

A lógica de alerta é implementada principalmente em nós function no Node-RED e exibida nos nós do Dashboard.

### 1. Alarme de Detecção de Presença (HC-SR501)

* **Condição:** Formato igual a **1** (movimento).
* **Ação:** o velocímetro exibido no dashboard fica vermelho.

### 2. Alarme de Alta ou Baixa Temperatura (DHT11)

* **Alerta Baixo:** Temperatura **$< 20^\circ C$**.
* **Alerta Alto:** Temperatura **$> 25^\circ C$**.
* **Ação:** Se a temperatura for baixa, o velocímetro exibido no dashboard fica azul. Se for alta, o velocímetro fica vermelho.

### 3. Alarme de Umidade Elevada (DHT11)

* **Condição:** Umidade **$> 50\%$**.
* **Ação:** o velocímetro exibido no dashboard fica verde.


Projeto desenvolvido por Luana Karoline e Emilly Félix.
