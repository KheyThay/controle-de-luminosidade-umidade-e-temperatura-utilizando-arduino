#include <LiquidCrystal.h>

// Definição de constantes para os estados de luminosidade
int ESCURO   = 0;
int MEIA_LUZ = 1;
int CLARO    = 2;
int luz = ESCURO;

// Definição de constantes para os estados de temperatura
int TEMP_OK = 0;
int FRIO    = 1;
int QUENTE  = 2;
int temperaturaAmbiente = TEMP_OK;

// Definição de constantes para os estados de umidade
int UMID_OK    = 0;
int UMID_BAIXA = 1;
int UMID_ALTA  = 2;
int umidadeAmbiente = UMID_OK;

// Tempo de exibição do display LCD
int tempoMostrarDisplay = 1000; //5000;

// Constantes para os tipos de dados a serem mostrados no display LCD
int const MOSTRA_LUZ  = 0;
int const MOSTRA_TEMP = 1;
int const MOSTRA_UMID = 2;
int estadoDisplay = MOSTRA_LUZ;

// Definição dos pinos dos componentes
int ledVermelhoPin = 11;  // LED vermelho no pino 9
int ledAmareloPin  = 12;  // LED amarelo no pino 10
int ledVerdePin    = 13;  // LED verde no pino 11
int ldrPin         = A1;  // LDR no pino A0
int buzzerPin      = 10;   // Buzzer no pino 7
int sensorTempPin  = A2;  // Sensor de temperatura no pino A2
int sensorUmidPin  = A0;  // Sensor de umidade no pino A1

// Inicialização do LCD nos pinos especificados
LiquidCrystal LCD (9,8,7,6,5,4); // LCD nos pinos 13, 12, 5, 4, 3 e 2

// Variáveis para armazenamento dos valores dos sensores e cálculo de médias
int   valorLDR    = 0;
float temperatura = 0;
int   umidade     = 0;

int millisDisplayAgora = 0;
int millisDisplayAnterior = 0;

int   contadorMedia = 0;
float somaTemperatura = 0;
int   somaUmidade = 0;

float mediaTemperatura = 0;
int   mediaUmidade = 0;

// Configuração inicial do sistema 
void setup(){
    // Inicialização do LCD
	LCD.begin(16,2);
	// Configuração dos pinos dos componentes
	pinMode (ledVermelhoPin, OUTPUT);  
	pinMode (ledAmareloPin, OUTPUT);
	pinMode (ledVerdePin, OUTPUT);
	pinMode (ldrPin, INPUT);
	pinMode (buzzerPin, OUTPUT);
	pinMode (sensorUmidPin, INPUT);
	// Inicialização da comunicação serial
	Serial.begin(9600);
}

// Loop principal do programa
void loop(){
	// Função para ler os sensores
	ler_sensores();
	// Função para verificar os estados dos sensores
	verifica_sensores();
	// Função para acionar os alarmes conforme os estados dos sensores
	aciona_alarmes();
	// Função para exibir mensagens no display LCD
	mostra_mensagem();
}

// Função para ler os valores dos sensores
void ler_sensores(){
    // Leitura do sensor de luminosidade (LDR)
	valorLDR = analogRead (ldrPin); 
	Serial.print("LDR: ");   
	Serial.println(valorLDR);
   
	// Leitura do sensor de temperatura
	int valorSensorTemp = analogRead (sensorTempPin);
	
	float tensao = valorSensorTemp * 5;
	tensao /= 1024;
	
	temperatura = (tensao - 0.5) * 100;

   	Serial.print("Temperatura: ");
	Serial.println(temperatura);
	
	// Leitura do sensor de umidade
	int valorSensorUmi = analogRead(sensorUmidPin); 
	
	umidade = map(valorSensorUmi, 0, 1023, 0, 100); 
	Serial.print("Umidade: ");
	Serial.println(umidade);
}

// Função para verificar os estados dos sensores
void verifica_sensores(){
	Serial.print("Ambiente esta ");
	// Verificação do estado de luminosidade
	if(valorLDR <= 700){
		luz = ESCURO;
		Serial.println("Escuro");
	} 
	else if(valorLDR > 700 && valorLDR <= 900){
		luz = MEIA_LUZ;
		Serial.println("Meia Luz");
	}
	else if(valorLDR > 900){
		luz = CLARO;
		Serial.println("Claro");
	}
	
	Serial.print("Temperatura esta ");
	// Verificação do estado de temperatura
	if(temperatura < 10){
		temperaturaAmbiente = FRIO;
		Serial.println("fria");
	}
	else if(temperatura > 15){
		temperaturaAmbiente = QUENTE;
		Serial.println("quente");
	}
	else {
		temperaturaAmbiente = TEMP_OK;
		Serial.println("OK");
	}
	
	Serial.print("Umidade esta ");
	// Verificação do estado de umidade
	if(umidade < 50){
		umidadeAmbiente = UMID_BAIXA;
		Serial.println("baixa");
	}
	else if(umidade > 70){
		umidadeAmbiente = UMID_ALTA;
		Serial.println("alta");
	}
	else {
		umidadeAmbiente = UMID_OK;
		Serial.println("OK");
	}
}

// Função para acionar os alarmes conforme os estados dos sensores
void aciona_alarmes(){
	// Acionamento do LED verde se estiver escuro
	if(luz == ESCURO){
		digitalWrite(ledVerdePin, HIGH);
	}
	else{
		digitalWrite(ledVerdePin, LOW);
	}
	
	// Acionamento do LED amarelo e buzzer se estiver em meia luz ou temperatura não estiver OK
	if(luz == MEIA_LUZ || temperaturaAmbiente != TEMP_OK){
		digitalWrite(ledAmareloPin, HIGH);		
		if(temperaturaAmbiente != TEMP_OK){
			digitalWrite(buzzerPin, HIGH);
		}
	}
	else{
		digitalWrite(ledAmareloPin, LOW);
		
		if(umidadeAmbiente == UMID_OK){
			digitalWrite(buzzerPin, LOW);
		}		
	}
	
	// Acionamento do LED vermelho e buzzer se estiver claro ou umidade não estiver OK
	if(luz == CLARO || umidadeAmbiente != UMID_OK){
		digitalWrite(ledVermelhoPin, HIGH);
		
		digitalWrite(buzzerPin, HIGH);
	}
	else{
		digitalWrite(ledVermelhoPin, LOW);
		
		if(temperaturaAmbiente == TEMP_OK){
			digitalWrite(buzzerPin, LOW);
		}
	}
}

// Função para exibir mensagens no display LCD
void mostra_mensagem(){
	millisDisplayAgora = millis();
	
    somaTemperatura = somaTemperatura + temperatura;
    somaUmidade = somaUmidade + umidade;
	contadorMedia++;
	
	if(millisDisplayAgora - millisDisplayAnterior > tempoMostrarDisplay){
	    LCD.clear();
		LCD.setCursor(0,0); 
	   
		switch(estadoDisplay){
			case (MOSTRA_LUZ):
				if(luz == ESCURO){
					LCD.print("Luz Ambiente OK");
				}
				else if(luz == MEIA_LUZ){
					LCD.print("Ambiente a");
					LCD.setCursor(0,1);
					LCD.print("meia luz");
				}
				else{
					LCD.print("Ambiente");
					LCD.setCursor(0,1);
					LCD.print("muito claro");
				}
				estadoDisplay = MOSTRA_TEMP;
			break;
			
			case(MOSTRA_TEMP):
				mediaTemperatura = somaTemperatura / contadorMedia;
				
				if(temperaturaAmbiente == TEMP_OK){
					LCD.print("Temperatura OK");
					LCD.setCursor(0,1);
					LCD.print("Temp. = "); LCD.print(mediaTemperatura); LCD.print("C");
				}
				else if(temperaturaAmbiente == FRIO){
					LCD.print("Temp. Baixa");
					LCD.setCursor(0,1);
					LCD.print("Temp. = "); LCD.print(mediaTemperatura); LCD.print("C");
				}
				else{
					LCD.print("Temp. Alta");
					LCD.setCursor(0,1);
					LCD.print("Temp. = "); LCD.print(mediaTemperatura); LCD.print("C");
				}
			estadoDisplay = MOSTRA_UMID;
			break;
			
			case(MOSTRA_UMID):
				mediaUmidade = somaUmidade / contadorMedia;
			
				if(umidadeAmbiente == UMID_OK){
					LCD.print("Umidade OK");
					LCD.setCursor(0,1);
					LCD.print("Umidade = "); LCD.print(mediaUmidade); LCD.print("%");
				}
				else if(umidadeAmbiente == UMID_BAIXA){
					LCD.print("Umidade Baixa");
					LCD.setCursor(0,1);
					LCD.print("Umidade = "); LCD.print(mediaUmidade); LCD.print("%");
				}
				else{
					LCD.print("Umidade Alta");
					LCD.setCursor(0,1);
					LCD.print("Umidade = "); LCD.print(mediaUmidade); LCD.print("%");
				}
			
			estadoDisplay = MOSTRA_LUZ;
			break;
			
			default:
				estadoDisplay = MOSTRA_LUZ;
			break;
		}
      
		somaTemperatura = 0;
		somaUmidade = 0;
		contadorMedia = 0;
		
		millisDisplayAnterior = millis();
	}
}
