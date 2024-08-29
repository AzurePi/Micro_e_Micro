/*
https://www.tinkercad.com/things/icc1oYgM7SO-semaforo?sharecode=htCfAmEQ_1atIqv5uM-J3PQkB830lT4Li7f-lKZhTMY
*/

#define LEDverdeA 13
#define LEDamareloA 12
#define LEDvermelhoA 11
#define LEDverdeB 5
#define LEDamareloB 4
#define LEDvermelhoB 3


void setup()
{
  pinMode(LEDverdeA, OUTPUT);
  pinMode(LEDamareloA, OUTPUT);
  pinMode(LEDvermelhoA, OUTPUT);
  pinMode(LEDverdeB, OUTPUT);
  pinMode(LEDamareloB, OUTPUT);
  pinMode(LEDvermelhoB, OUTPUT);
}

void loop()
{
  digitalWrite(LEDverdeA, HIGH);
  digitalWrite(LEDamareloA, LOW);
  digitalWrite(LEDvermelhoA, LOW);
  digitalWrite(LEDverdeB, LOW);
  digitalWrite(LEDamareloB, LOW);
  digitalWrite(LEDvermelhoB, HIGH);
  delay(4000);
  
  digitalWrite(LEDverdeA, LOW);
  digitalWrite(LEDamareloA, HIGH);
  digitalWrite(LEDvermelhoA, LOW);
  delay(1500);
  
  digitalWrite(LEDverdeA, LOW);
  digitalWrite(LEDamareloA, LOW);
  digitalWrite(LEDvermelhoA, HIGH);
  digitalWrite(LEDverdeB, HIGH);
  digitalWrite(LEDamareloB, LOW);
  digitalWrite(LEDvermelhoB, LOW);
  delay(4000);
  
  digitalWrite(LEDverdeB, LOW);
  digitalWrite(LEDamareloB, HIGH);
  digitalWrite(LEDvermelhoB, LOW);
  delay(1500);
}