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
