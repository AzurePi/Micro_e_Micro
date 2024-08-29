/*
https://www.tinkercad.com/things/fO3ktonWxt1-sensor-temperatura?sharecode=1IAqOoG0nrGomRxZJQaXWc2nt684-n3qp3KGmXpcOc4
*/


#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int TEMP_PIN = A0; //pino ao qual o sensor TMP está conectado
int LEDblue = 8; //pino do led azul
int LEDred = 9; //pino do led vermelho
int VENTILADOR = 13; //pino do motor do ventilador

int val;
float voltage, celsius;
int prev = -1;

void setup()
{ 
  	pinMode(TEMP_PIN, INPUT);
  	pinMode(LEDblue, OUTPUT);
  	pinMode(LEDred, OUTPUT);
  	pinMode(VENTILADOR, OUTPUT);
     
    // Texto da primeira linha do painel LCD
  	delay(100);
  	lcd.setCursor(0, 1);
    lcd.print("Temp. °C");
}

void loop()
{  
  val = analogRead(TEMP_PIN);
  voltage = val * (5.0 / 1024.0);
  celsius = (voltage - 0.5) * 100.0;
  
  if (prev != celsius) {
    lcd.clear();
  	lcd.setCursor(0, 2);
  	lcd.print(celsius);
  	lcd.print(" ºC");  
    
    if (celsius >= 40) {
    	digitalWrite(LEDred, HIGH); 
      	digitalWrite(LEDblue, LOW); 
      	digitalWrite(VENTILADOR, HIGH);
    }
    else if(celsius <= 10) {
      	digitalWrite(LEDred, LOW); 
      	digitalWrite(LEDblue, HIGH);
      	digitalWrite(VENTILADOR, LOW);
    }
    else {
      	digitalWrite(LEDred, LOW); 
      	digitalWrite(LEDblue, LOW);
      	digitalWrite(VENTILADOR, LOW);
    }
    
  }

  prev = celsius;
  delay(500);
}