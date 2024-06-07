Projeto de Monitoramento da Qualidade da Água

Link do projeto no wokwi: https://wokwi.com/projects/399790774483378177

Descrição do Projeto
  - Este projeto visa criar um sistema de monitoramento da qualidade da água utilizando sensores de temperatura, pH, condutividade elétrica (CE) e oxigênio dissolvido (OD). O sistema lê os dados dos sensores, processa essas informações e exibe os resultados em um     
    display LCD I2C e no monitor serial. O projeto é ideal para uso em qualquer ambiente onde a qualidade da água seja crucial.

Componentes Utilizados
  - Sensor de Temperatura e Umidade DHT22: Mede a temperatura e a umidade do ambiente.
  - Sensores Analógicos para pH, CE e OD: Medem o pH, a condutividade elétrica e o oxigênio dissolvido na água.
  - Display LCD I2C 16x2: Exibe as leituras dos sensores.
  - Arduino: Controla e programa os sensores e o display.

Bibliotecas Necessárias
  Para compilar e executar este projeto, você precisará das seguintes bibliotecas:
    - `LiquidCrystal_I2C`: Biblioteca para controle de displays LCD através da interface I2C.
    - `DHT`: Biblioteca para leitura de sensores de temperatura e umidade da família DHT (DHT11, DHT21, DHT22).

Configuração dos Sensores e Pinos
  - DHT22
    - Pino de Dados: `DHTPIN 2`
  - Sensores Analógicos
    - pH: `PH_PIN 13`
    - Condutividade Elétrica (CE): `CE_PIN 12`
    - Oxigênio Dissolvido (OD): `OD_PIN 11`

Variáveis de Calibração
  - pH
    - Tensão para solução ácida: `942.0`
    - Tensão para solução neutra: `1650.0`
  - Condutividade Elétrica
    - Calibração: `calibracaoCE = 1.0`
    - Tensão de Calibração: `CAL1_V = 1600`
    - Temperatura de Calibração: `CAL1_T = 25`

Tabela de Saturação de Oxigênio
  Valores de saturação de oxigênio em função da temperatura (0 a 40 graus Celsius). Os valores são multiplicados por 1000 para manter a consistência com os valores originais.

Tecnologias Utilizadas
  - C++

Instruções para Compilação e Execução
  1. Instale as bibliotecas necessárias (`DHT` e `LiquidCrystal_I2C`) via Arduino Library Manager.
  2. Conecte os sensores de acordo com os pinos definidos no código.
  3. Carregue o código no Arduino.
  4. Abra o monitor serial para visualizar os dados.
  5. Os resultados também serão exibidos no display LCD I2C.

Link do vídeo explicativo:
  https://www.loom.com/share/feca76f71de0454fad95e95ea852f8ab?sid=dbbcc4b5-2a58-461c-8ac5-99d5a7763e42 

Membros da Equipe
  - Jeniffer De Moraes RM: 555448
  - Maria Eduarda RM: 558457
  - Matheus Diniz RM: 555683
