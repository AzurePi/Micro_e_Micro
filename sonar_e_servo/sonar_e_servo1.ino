/*
https://www.tinkercad.com/things/aBm3HaNyCaY-sonar-e-servo?sharecode=f2m7PCVqPZJqfj5dih7fgkXsdNAIe6eEVUkdQ-8IUT4
*/

#include <Servo.h>

int trig = 4; // Define o pino trig do sensor ultrassônico
int echo = 5; // Define o pino echo do sensor ultrassônico
int servoPin = 9; // Pino do servo
Servo meuServo; // Crie um objeto Servo

float distancia; // Variável para armazenar a distância medida pelo sensor ultrassônico

void setup()    
{
  pinMode(trig, OUTPUT); // Configura o pino trig como saída
  pinMode(echo, INPUT); // Configura o pino echo como entrada
  //pinMode(servoPin, OUTPUT); // Define o pino do LED como saída
  Serial.begin(9600); // Inicializa a comunicação serial com taxa de transmissão de 9600 bps
  meuServo.attach(9); // Anexe o servo ao pino 9
}

void loop()
{
  digitalWrite(trig, LOW); // Envie um pulso LOW no pino trig
  delayMicroseconds(2); // Aguarde 2 microssegundos
  digitalWrite(trig, HIGH); // Envie um pulso HIGH no pino trig
  delayMicroseconds(10); // Aguarde 10 microssegundos
  digitalWrite(trig, LOW); // Envie um pulso LOW no pino trig
 
  distancia = pulseIn(echo, HIGH); // Meça o tempo de resposta do echo
  distancia = distancia / 58; // Converta o tempo em distância (em centímetros)

  Serial.println(distancia); // Imprima a distância medida no monitor serial

  // Verifica se a distância é menor ou igual a 20cm
  if(distancia <= 70) {
   // digitalWrite(servoPin, HIGH); // Acende o LED
    meuServo.write(90); // Gira o servo para 90 graus
  } else {
    //digitalWrite(servoPin, LOW); // Apaga o LED
    meuServo.write(0); // Gira o servo para 0 graus
  }
}