# **Projeto de Monitoramento de Umidade e Temperatura com Arduino**
## Análise e Desenvolvimento de Sistemas - Universidade Presbiteriana Mackenzie
## Objetos Inteligentes Conectados

Este projeto utiliza um Arduino para monitorar a umidade e temperatura do ambiente usando o sensor DHT11, exibindo os valores em um display LCD 16x2 com interface I2C. O projeto também inclui um relé que pode ser acionado automaticamente com base nos níveis de umidade configurados.

---

## **Componentes Utilizados**
- **Arduino Uno (ou compatível)**
- **Modulo / Sensor Dht11 Temperatura E Umidade - Arduino**
- **Display LCD 16x2 com módulo I2C (HD44780)**
- **Módulo Relé**
- **Jumpers e Protoboard**
- **Fonte de alimentação (via USB ou externa para o Arduino)**

---

## **Especificações**
- **Sensor DHT11**: Mede temperatura e umidade com saída digital.
- **Display LCD**: Exibe os valores de umidade e temperatura em tempo real.
- **Relé**: Pode ser usado para acionar dispositivos, como um umidificador ou ventilador, com base nos níveis de umidade.

---

## **Conexões**
### **Sensor DHT11**
| Pino DHT11 | Conexão Arduino |
|------------|-----------------|
| VCC        | 5V             |
| GND        | GND            |
| DATA       | Pino digital D2|

### **Display LCD com I2C**
| Pino I2C | Conexão Arduino |
|----------|-----------------|
| VCC      | 5V             |
| GND      | GND            |
| SDA      | A4             |
| SCL      | A5             |

### **Módulo Relé**
| Pino Relé | Conexão Arduino |
|-----------|-----------------|
| VCC       | 5V             |
| GND       | GND            |
| IN        | Pino digital D3|

---

## **Instalação**
1. **Bibliotecas Necessárias**
   Certifique-se de instalar as seguintes bibliotecas no Arduino IDE:
   - [**DHT sensor library**](https://github.com/adafruit/DHT-sensor-library)
   - [**Adafruit Unified Sensor**](https://github.com/adafruit/Adafruit_Sensor)
   - [**New LiquidCrystal**](https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/)

   Para instalar:
   - Abra o Arduino IDE.
   - Vá em **Sketch > Include Library > Manage Libraries...**.
   - Pesquise pelas bibliotecas mencionadas e clique em **Install**.

2. **Carregar o Código**
   Copie o código abaixo no Arduino IDE e faça o upload para o seu Arduino.

---

## **Código**
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Configuração do LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Substitua "0x27" pelo endereço correto

// Configuração do DHT11
#define DHTPIN 2          // Pino onde está conectado o DHT11
#define DHTTYPE DHT11     // Tipo do sensor
DHT dht(DHTPIN, DHTTYPE);

// Configuração do Relé
#define RELAYPIN 3        // Pino do relé
#define UMIDADE_LIMITE 50 // Limite mínimo de umidade desejado

void setup() {
  // Inicializa o LCD
  lcd.init();           // Inicializa o módulo I2C do LCD
  lcd.backlight();      // Ativa a luz de fundo do LCD
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(2000);          // Exibe mensagem inicial por 2 segundos

  // Inicializa o DHT11
  dht.begin();

  // Configuração do pino do relé
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW); // Relé desligado inicialmente

  // Inicia comunicação serial
  Serial.begin(9600);
  Serial.println("Sistema Iniciado");
}

void loop() {
  delay(2000); // Aguarda 2 segundos entre leituras

  // Lê os valores do DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Verifica se a leitura é válida
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erro ao ler o sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro no sensor!");
    return;
  }

  // Exibe valores no Monitor Serial
  Serial.print("Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Exibe valores no LCD
  lcd.clear();
  lcd.setCursor(0, 0); // Linha 1
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");

  lcd.setCursor(0, 1); // Linha 2
  lcd.print("Umid: ");
  lcd.print(humidity);
  lcd.print("%");

  // Controle do relé
  if (humidity < UMIDADE_LIMITE) {
    digitalWrite(RELAYPIN, HIGH); // Liga o relé
    Serial.println("Relé: LIGADO");
    lcd.setCursor(11, 1);
    lcd.print("ON ");
  } else {
    digitalWrite(RELAYPIN, LOW); // Desliga o relé
    Serial.println("Relé: DESLIGADO");
    lcd.setCursor(11, 1);
    lcd.print("OFF");
  }
}
```

---

## **Funcionamento**
1. **Leitura de Dados**
   O sensor DHT11 lê a temperatura e umidade do ambiente.
2. **Exibição no LCD**
   O LCD exibe os valores em tempo real.
3. **Controle do Relé**
   - Se a umidade estiver abaixo de 50%, o relé será ativado.
   - Caso contrário, o relé será desligado.

---

## **Ajustes Finais**
- **Configuração do Relé**: Conecte o dispositivo controlado (ex.: umidificador ou sinalizador) aos terminais do relé, seguindo as orientações do fabricante.
- **Ajuste da Umidade**: Modifique o limite de umidade no código (linha `if (humidity < 50)`).

---

## **Licença**
Este projeto é de código aberto e pode ser usado, modificado e compartilhado livremente.
