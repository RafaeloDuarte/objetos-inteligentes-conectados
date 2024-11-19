# **Projeto de Monitoramento de Umidade e Temperatura com Arduino**
## Análise e Desenvolvimento de Sistemas - Universidade Presbiteriana Mackenzie
## Objetos Inteligentes Conectados

Este projeto utiliza um Arduino para monitorar a umidade e temperatura do ambiente usando o sensor DHT11, exibindo os valores em um display LCD 16x2 com interface I2C. O projeto também inclui um relé que pode ser acionado automaticamente com base nos níveis de umidade configurados.

---

## **Componentes Utilizados**
- **Arduino Uno (ou compatível)**
- **Sensor DHT11**
- **Display LCD 16x2 com módulo I2C (HD44780)**
- **Módulo Relé**
- **Resistor de 10kΩ (se necessário para o sensor DHT11)**
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

#define DHTPIN 2        // Pino onde o DHT11 está conectado
#define DHTTYPE DHT11   // Defina o tipo de sensor DHT
#define RELAY_PIN 3     // Pino de controle do relé

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(RELAY_PIN, OUTPUT);  // Configura o pino do relé como saída
  lcd.begin(16, 2);            // Inicializa o LCD
  lcd.backlight();             // Liga o backlight do LCD
  dht.begin();                 // Inicializa o sensor DHT11
}

void loop() {
  float humidity = dht.readHumidity();   // Lê a umidade
  float temperature = dht.readTemperature(); // Lê a temperatura

  // Verifica se a leitura foi bem-sucedida
  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Erro de leitura");
    return;
  }

  // Exibe os valores no LCD
  lcd.setCursor(0, 0);
  lcd.print("Umidade: ");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");

  // Aciona o relé com base na umidade
  if (humidity < 40) {
    digitalWrite(RELAY_PIN, HIGH);  // Liga o relé
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Desliga o relé
  }

  delay(2000); // Atualiza os valores a cada 2 segundos
}
```

---

## **Funcionamento**
1. **Leitura de Dados**
   O sensor DHT11 lê a temperatura e umidade do ambiente.
2. **Exibição no LCD**
   O LCD exibe os valores em tempo real.
3. **Controle do Relé**
   - Se a umidade estiver abaixo de 40%, o relé será ativado.
   - Caso contrário, o relé será desligado.

---

## **Ajustes Finais**
- **Configuração do Relé**: Conecte o dispositivo controlado (ex.: umidificador) aos terminais do relé, seguindo as orientações do fabricante.
- **Ajuste da Umidade**: Modifique o limite de umidade no código (linha `if (humidity < 40)`).

---

## **Licença**
Este projeto é de código aberto e pode ser usado, modificado e compartilhado livremente. 😊
