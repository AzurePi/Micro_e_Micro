#include "asmfunc.h"

#define CHAVE1 2
#define CHAVE2 3
#define CHAVE3 4

typedef struct chaves {
  int b1, b2, b3;
} Chaves;

Chaves atual;
Chaves prev;

void setup() {
  Serial.begin(9600);

  pinMode(CHAVE1, INPUT);
  pinMode(CHAVE2, INPUT);
  pinMode(CHAVE3, INPUT);

  _setup_pwm();
}

void loop() {
  atual.b1 = digitalRead(CHAVE1);
  atual.b2 = digitalRead(CHAVE2);
  atual.b3 = digitalRead(CHAVE3);

  if (atual.b1 != prev.b1 || atual.b2 != prev.b2 || atual.b3 != prev.b3) {
    Serial.print("Estado das chaves: ");
    Serial.print(atual.b1);
    Serial.print(atual.b2);
    Serial.println(atual.b3);

    if (atual.b3 == HIGH) {
      Serial.println("Velocidade 3");
      _vel3();
    } else if (atual.b2 == HIGH) {
      Serial.println("Velocidade 2");
      _vel2();
    } else if (atual.b1 == HIGH) {
      Serial.println("Velocidade 1");
      _vel1();
    } else {
      Serial.println("Motor parado");
      _stop();
    }
  }

  prev = atual;

  delay(200);
}
