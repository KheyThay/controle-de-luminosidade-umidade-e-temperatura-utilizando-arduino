# controle-de-luminosidade-umidade-e-temperatura-utilizando-arduino
Projeto que apresenta um sistema inteligente de controle de luminosidade, umidade e temperatura utilizando um Arduino Uno e componentes eletrônicos simples.

## Introdução
Este é um projeto de sistema de monitoramento de ambiente desenvolvido utilizando um Arduino Uno e diversos sensores. O sistema é capaz de monitorar a luminosidade, temperatura e umidade do ambiente e exibir as informações em um display LCD. Além disso, aciona alarmes visuais e sonoros conforme os valores dos sensores.

## Componentes utilizados:

- Arduino Uno
- Fotoresistor (LDR - Light Dependent Resistor)
- Display LCD
- Potenciômetro
- Sensor de temperatura
- LEDs (verde, amarelo e vermelho)
- Buzzer
- Resistores
- Protoboard
- Jumpers
- 
## Montagem do circuito

- Conectar o fotoresistor (LDR) ao pino A1 do Arduino.
- Conectar o display LCD aos pinos 9, 8, 7, 6, 5 e 4 do Arduino.
- Conectar o LED vermelho ao pino 11, o LED amarelo ao pino 12 e o LED verde ao pino 13 do Arduino.
- Conectar o buzzer ao pino 10 do Arduino.
- Conectar o sensor de temperatura ao pino A2 do Arduino.
- Conectar o sensor de umidade ao pino A0 do Arduino.
- Conectar os componentes à protoboard conforme necessário, utilizando resistores conforme especificado pelos componentes.

[Modo de montagem no protoboard (Placa de ensaio)]
<br>https://www.tinkercad.com/things/2fZEaZmqrea-sensor-de-luminosidade-umidade-e-temperatura/editel?returnTo=%2Fthings%2F2fZEaZmqrea-cp2&sharecode=wkTjx8u0WSW2ZLIUtaeLoir9VaCEhY8Xy6Jv8dWAXMg

# Funcionamento do código

### Luminosidade:

ESCURA 

    (Se o LDR <= 700) O LED verde é ligado para indicar que o ambiente está escuro e a "Luminosidade OK!"
    
MEIA LUZ 

    (Se LDR entre 701 e 900): O LED amarelo e o buzzer são ligados para indicar que o ambiente está em meia luz ou que a temperatura não está OK.
    
CLARA 

    (valor do LDR > 900): O LED vermelho e o buzzer são ligados para indicar que o ambiente está claro ou que a umidade ou temperatura não está OK.

### Temperatura:

FRIA 

    (temperatura < 10°C) O estado da temperatura é definido como "FRIO", mensagem "Temp. Baixa" junto com a temperatura média.
    
QUENTE 

    (temperatura > 15°C) O estado da temperatura é definido como "QUENTE", mensagem "Temp. Alta" junto com a temperatura média.
    
TEMPERATURA OK 

    (temperatura entre 10°C e 15°C) O estado da temperatura é definido como "OK", mensagem "Temperatura OK" junto com a temperatura média.
    
### Umidade:

BAIXA 

    (umidade < 50%) O estado da umidade é definido como "UMID_BAIXA", mensagem no LCD "Umidade Baixa" junto com a umidade média.
    
ALTA 

    (umidade > 70%) O estado da umidade é definido como "UMID_ALTA", mensagem "Umidade Alta" junto com a umidade média.
    
UMIDADE OK 

    (umidade entre 50% e 70%) O estado da umidade é definido como "UMID_OK", mensagem "Umidade OK" junto com a umidade média.


- Configuração Inicial:
<br>O código começa com a inclusão da biblioteca LiquidCrystal.h, que permite o uso do display LCD.
<br>São definidas diversas constantes que representam os diferentes estados de luminosidade, temperatura e umidade, bem como o tempo de exibição do display LCD.
<br>Os pinos dos componentes são definidos e inicializados, incluindo os pinos para os LEDs, LDR (sensor de luminosidade), buzzer, sensor de temperatura e sensor de umidade.
<br>O LCD é inicializado nos pinos especificados.

- Loop Principal (loop()):
<br>O programa entra no loop principal, onde quatro funções são chamadas sequencialmente: ler_sensores(), verifica_sensores(), aciona_alarmes() e mostra_mensagem().

- Leitura dos Sensores (ler_sensores()):
<br>Nesta função, os valores dos sensores de luminosidade, temperatura e umidade são lidos.
<br>O valor do LDR é lido usando analogRead() e armazenado na variável valorLDR.
<br>O valor do sensor de temperatura é lido e convertido para graus Celsius usando uma fórmula de conversão.
<br>O valor do sensor de umidade é lido e mapeado para a faixa de 0 a 100%.

- Verificação dos Estados dos Sensores (verifica_sensores()):
<br>Nesta função, os estados de luminosidade, temperatura e umidade são verificados com base nos valores lidos dos sensores.
<br>O estado de luminosidade é determinado comparando o valor do LDR com limites pré-definidos.
<br>O estado de temperatura é determinado com base em limites pré-definidos.
<br>O estado de umidade é determinado com base em limites pré-definidos.

- Acionamento dos Alarmes (aciona_alarmes()):
<br>Nesta função, os LEDs e o buzzer são acionados de acordo com os estados dos sensores.
<br>O LED verde é ligado se estiver escuro, o LED amarelo e o buzzer são ligados se estiver em meia luz ou a temperatura não estiver OK, e o LED vermelho e o buzzer são ligados se <br>estiver claro ou a umidade não estiver OK.

- Exibição de Mensagens no Display LCD (mostra_mensagem()):
<br>Nesta função, as mensagens são exibidas no display LCD com base nos estados dos sensores.
<br>A função atualiza o conteúdo do display LCD a cada intervalo de tempo especificado.
<br>São mostradas mensagens indicando o estado da luminosidade, temperatura e umidade, juntamente com os valores médios desses parâmetros.

- Observações:
<br>A comunicação serial é utilizada para depuração, exibindo os valores lidos dos sensores no monitor serial.
<br>O tempo de exibição do display LCD e os limites para acionamento dos alarmes podem ser ajustados conforme necessário.

# Considerações finais

Este projeto oferece uma solução prática e eficiente para monitorar não apenas a iluminação de um ambiente, mas também a temperatura e a umidade. Utilizando sensores de temperatura e umidade, juntamente com o fotoresistor para detectar luminosidade, o sistema é capaz de oferecer um controle completo das condições ambientais. A inclusão do buzzer proporciona um meio adicional de alerta em casos de temperaturas extremas ou umidade fora dos limites aceitáveis. Com este guia, entusiastas e iniciantes em eletrônica podem criar facilmente seu próprio sistema de monitoramento ambiental utilizando um Arduino e componentes acessíveis.

## Projeto desenvolvido por:

<br>Gabriel Miranda de F. Carpino - RM: 559102
<br>Kheyla Thais Q. Paucara - RM: 558434


<h5>1ESPK - CheckPoint 2 || máteria de Edge computing e computer systems</h5>
