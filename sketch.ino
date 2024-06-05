#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define o pino e o tipo do sensor (DHT)
#define DHTPIN 2     
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE); // Inicializa o sensor DHT

LiquidCrystal_I2C LCD(0x27, 16, 2); // Inicializa o display

// Define os pinos para sensores de pH, CE e OD
float tensaoAcido = 942.0;    
float tensaoNeutra = 1650.0;    

// variaveis de calibração
#define PH_PIN 13
#define CE_PIN 12
#define OD_PIN 11

// Variáveis de armazenamento das leituras dos sensores
float temperatura, pH, condutividadE, oxigenioD;

// variaveis de calibração
float calibracaoCE = 1.0;
float CAL1_V = 1600; 
float CAL1_T = 25;  

// tabela de valores de saturação de oxigênio em função da temperatura (de 0 a 40 graus)
// src: https://www.engquimicasantossp.com.br/2020/10/dbo-demanda-bioquimica-de-oxigenio.html
// Os valores na tabela foram multiplicados por 1000 para manter a consistência com os valores originais
const float OxigenioDissolvido_tabela[41] = {
  14600, 14190, 13810, 13440, 13090, 12750, 12430, 12120, 11830, 11550,
  11290, 11030, 10780, 10550, 10320, 10100,  9890,  9680,  9480,  9290,
   9100,  8920,  8740,  8560,  8400,  8240,  8090,  7940,  7800,  7670,
   7540,  7410,  7280,  7160,  7040,  6930,  6820,  6710,  6610,  6500,
   6400
};


void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
  dht.begin(); // Inicializa o sensor DHT
  LCD.init(); // Inicializa o display LCD
  LCD.backlight(); // Ativa a luz de fundo do LCD
  delay(1000); // Atraso
}

void loop() {
  qualidadeAgua (); // Chama a função para medir a qualidade da água
  delay(1000); // Atraso 
}

void qualidadeAgua () {
  // Lê a umidade e a temperatura do sensor DHT
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Verifica se leitura está correta
  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }

  temperatura = t; // Armazena a temperatura

  // Leitura e cálculo do valor de PH
  float leituraPH = analogRead(PH_PIN);
  float tensaoPH = leituraPH * (3300.0/4096.0);
  float declive = (7.0-4.0)/((tensaoNeutra-1500.0)/3.0 - (tensaoAcido-1500.0)/3.0);  
  float intercept = 7.0 - declive*(tensaoNeutra-1500.0)/3.0;
  pH = declive * (tensaoPH - 1500.0) / 3.0 + intercept;

  // Leitura e cálculo da condutividade elétrica (CE)
  float leituraCE = analogRead(CE_PIN);
  float tensaoCE = leituraCE * (3.3/4096.0);
  condutividadE = (tensaoCE / (1.0 + 0.0185 * (temperatura - 25.0))) * calibracaoCE; 

  // Leitura e cálculo do oxigênio dissolvido (OD)
  float leituraOD = analogRead(OD_PIN);
  float tensaoOD = leituraOD * (3300.0/4096.0);
  uint8_t temperaturaInteira = static_cast<uint8_t>(round(temperatura));
  float V_saturacao = CAL1_V + 35 * temperaturaInteira - CAL1_T * 35;
  oxigenioD = (tensaoOD * OxigenioDissolvido_tabela[temperaturaInteira] / V_saturacao) / 1000;

  // Exibe os valores na serial
  Serial.print(F("Temperatura: ")); Serial.print(temperatura, 2); Serial.println(" °C");
  Serial.print(F("pH: ")); Serial.println(pH, 2);
  Serial.print(F("CE: ")); Serial.print(condutividadE, 4); Serial.println(" mS/cm");
  Serial.print(F("OD: ")); Serial.print(oxigenioD, 2); Serial.println(" mg/L");

  // Printando valores no display
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Temp: "); LCD.print(temperatura, 1); LCD.print("C");
  LCD.setCursor(0, 1);
  LCD.print("pH: "); LCD.print(pH, 1);
  delay(2000);

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("CE: "); LCD.print(condutividadE, 2); LCD.print("mS/cm");
  LCD.setCursor(0, 1);
  LCD.print("OD: "); LCD.print(oxigenioD, 1); LCD.print("mg/L");
  delay(2000);
}
