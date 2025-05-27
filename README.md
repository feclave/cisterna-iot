
# Sistema de Coleta e Reuso de Águas Pluviais com ESP32 e MQTT

Este projeto apresenta a simulação de um sistema inteligente para coleta e reuso de águas pluviais armazenadas em cisternas, utilizando sensores conectados a um ESP32 com comunicação em tempo real via protocolo MQTT. O objetivo é permitir o monitoramento remoto do nível e da qualidade da água, além do acionamento automático de bomba e válvula para distribuição da água captada.

---

## 🧪 Funcionalidade

- Leitura do **nível da água** por sensor ultrassônico (HC-SR04)
- Leitura da **qualidade da água** (simulada via potenciômetro como TDS)
- Envio dos dados para a internet usando **Wi-Fi + MQTT**
- Ativação de **bomba e válvula** de acordo com regras de qualidade e volume
- Visualização em tempo real via ferramentas como **MQTT Explorer** e **HiveMQ WebSocket Client**

---

## 💻 Como usar

1. Clone o repositório:
   ```
   git clone https://github.com/SEU_USUARIO/seu-repo.git
   ```

2. Acesse a plataforma de simulação [Wokwi](https://wokwi.com/) e carregue o projeto ou use o código `sketch.ino` diretamente em seu ambiente com ESP32.

3. Certifique-se de estar conectado à internet e use um broker MQTT como:
   - `broker.hivemq.com`, porta 1883 (sem autenticação)

4. Visualize os dados publicados com:
   - [MQTT Explorer](https://mqtt-explorer.com/)
   - [HiveMQ WebSocket Client](https://www.hivemq.com/demos/websocket-client/)

---

## 📂 Estrutura do repositório

```
├── sketch.ino                # Código-fonte principal
├── diagram.json              # Diagrama do circuito Wokwi (se aplicável)
├── README.md                 # Esta documentação
└── imagens/                  # Capturas de tela e figuras (opcional)
```

---

## 🧱 Hardware Utilizado

| Componente                 | Função                                           |
|----------------------------|--------------------------------------------------|
| ESP32 DevKit V1            | Microcontrolador com Wi-Fi                      |
| Sensor Ultrassônico HC-SR04| Medição do nível de água                       |
| Potenciômetro              | Simula sensor de qualidade da água (TDS)       |
| LED Vermelho (Pino 26)     | Simula bomba submersível                       |
| LED Azul (Pino 27)         | Simula válvula solenóide                       |

> Observação: todos os testes foram realizados no ambiente virtual Wokwi.

---

## 🔌 Protocolos e Comunicação

- **MQTT** (Message Queuing Telemetry Transport)
  - Broker: `broker.hivemq.com`
  - Tópicos utilizados:
    - `cisterna/nivel`
    - `cisterna/qualidade`
  - Publicações a cada 5 segundos, sem autenticação, QoS 0

- **Wi-Fi TCP/IP**
  - A conexão é feita automaticamente na rede `Wokwi-GUEST`
  - Em ambiente físico, a rede pode ser substituída no código

---

## 📷 Demonstração

📺 Vídeo completo da simulação e funcionamento:  
[🔗 YouTube (não listado)](https://youtu.be/YNYTJI5WWQ8)

---

## 👨‍🔬 Autor

Desenvolvido por Felipe Jost Clavé, aluno da Universidade Presbiteriana Mackenzie. Projeto final da disciplina de Objetos Inteligentes Conectados.

---

## 📘 Licença

Este projeto é de uso acadêmico e pode ser adaptado livremente com os devidos créditos ao autor.
