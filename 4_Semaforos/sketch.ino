#define BUTTON_BLUE 13
#define BUTTON_WHITE 12
#define BUTTON_GREY 0

//RED YELLOW GREEN
int semaforoA[] = {25, 33, 32};
int semaforoB[] = {21, 19, 18};

//RED GREEN
int semaforoC[] = {14, 27};
int semaforoD[] = {2, 15};

int travessiaC, emergency, travessiaD;

// funções auxiliares ------------------------------------------------------

void modoTravessiaC(){
  Serial.println("Modo travessia C");
  delay(4000);

  digitalWrite(semaforoA[0], HIGH);
  digitalWrite(semaforoA[1], LOW);
  digitalWrite(semaforoA[2], LOW);

  digitalWrite(semaforoB[0], LOW);
  digitalWrite(semaforoB[1], LOW);
  digitalWrite(semaforoB[2], HIGH);

  digitalWrite(semaforoC[0], LOW);
  digitalWrite(semaforoC[1], HIGH);

  digitalWrite(semaforoD[0], HIGH);
  digitalWrite(semaforoD[1], LOW);

  delay(5000);
  Serial.println("Normalizando...");
}

void modoTravessiaD() {
  Serial.println("Modo travessia D");
  delay(4000);

  digitalWrite(semaforoA[0], LOW);
  digitalWrite(semaforoA[1], LOW);
  digitalWrite(semaforoA[2], HIGH);

  digitalWrite(semaforoB[0], HIGH);
  digitalWrite(semaforoB[1], LOW);
  digitalWrite(semaforoB[2], LOW);

  digitalWrite(semaforoC[0], HIGH);
  digitalWrite(semaforoC[1], LOW);

  digitalWrite(semaforoD[0], LOW);
  digitalWrite(semaforoD[1], HIGH);

  delay(5000);
  Serial.println("Normalizando...");
}

void check() {
  travessiaC = !digitalRead(BUTTON_BLUE);
  emergency = !digitalRead(BUTTON_WHITE);
  travessiaD = !digitalRead(BUTTON_GREY);

  Serial.printf("%d, %d, %d\n", travessiaC, emergency, travessiaD);

  if (travessiaC) modoTravessiaC();
  if (travessiaD) modoTravessiaD();
}


// setup e loop ------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  // Define os pinos dos LEDs como saída
  pinMode(semaforoA[0], OUTPUT);
  pinMode(semaforoA[1], OUTPUT);
  pinMode(semaforoA[2], OUTPUT);
  
  pinMode(semaforoB[0], OUTPUT);
  pinMode(semaforoB[1], OUTPUT);
  pinMode(semaforoB[2], OUTPUT);
  
  pinMode(semaforoC[0], OUTPUT);
  pinMode(semaforoC[1], OUTPUT);
  
  pinMode(semaforoD[0], OUTPUT);
  pinMode(semaforoD[1], OUTPUT);

  // Define os pinos dos botões como entrada
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_WHITE, INPUT_PULLUP);
  pinMode(BUTTON_GREY, INPUT_PULLUP);
}

void loop() {
  check(); //-------------------------

  digitalWrite(semaforoC[0], LOW);
  digitalWrite(semaforoC[1], HIGH);

  digitalWrite(semaforoD[0], HIGH);
  digitalWrite(semaforoD[1], LOW);

  if (emergency == HIGH) {
    digitalWrite(semaforoA[0], LOW);
    digitalWrite(semaforoA[1], HIGH);
    digitalWrite(semaforoA[2], LOW);

    digitalWrite(semaforoB[0], LOW);
    digitalWrite(semaforoB[1], LOW);
    digitalWrite(semaforoB[2], LOW);

    delay(2000);
  } else {
    digitalWrite(semaforoA[0], HIGH);
    digitalWrite(semaforoA[1], LOW);
    digitalWrite(semaforoA[2], LOW);

    digitalWrite(semaforoB[0], LOW);
    digitalWrite(semaforoB[1], LOW);
    digitalWrite(semaforoB[2], HIGH);

    delay(8000);
  }

  check(); //-------------------------

  if (emergency == HIGH) {
    digitalWrite(semaforoA[0], LOW);
    digitalWrite(semaforoA[1], LOW);
    digitalWrite(semaforoA[2], LOW);

    digitalWrite(semaforoB[0], LOW);
    digitalWrite(semaforoB[1], HIGH);
    digitalWrite(semaforoB[2], LOW);
  } else {
    digitalWrite(semaforoA[0], LOW);
    digitalWrite(semaforoA[1], HIGH);
    digitalWrite(semaforoA[2], LOW);

    digitalWrite(semaforoB[0], LOW);
    digitalWrite(semaforoB[1], HIGH);
    digitalWrite(semaforoB[2], LOW);
  }
  delay(2000);

  check(); //-------------------------

  digitalWrite(semaforoC[0], HIGH);
  digitalWrite(semaforoC[1], LOW);

  digitalWrite(semaforoD[0], LOW);
  digitalWrite(semaforoD[1], HIGH);

  if (emergency != HIGH){
    digitalWrite(semaforoA[0], LOW);
    digitalWrite(semaforoA[1], LOW);
    digitalWrite(semaforoA[2], HIGH);

    digitalWrite(semaforoB[0], HIGH);
    digitalWrite(semaforoB[1], LOW);
    digitalWrite(semaforoB[2], LOW);

    delay(8000);
  }

  check(); //-------------------------

  if (emergency == HIGH) {
    digitalWrite(semaforoA[0], LOW);
    digitalWrite(semaforoA[1], LOW);
    digitalWrite(semaforoA[2], LOW);

    digitalWrite(semaforoB[0], LOW);
    digitalWrite(semaforoB[1], HIGH);
    digitalWrite(semaforoB[2], LOW);
  } else {
    digitalWrite(semaforoA[0], LOW);
    digitalWrite(semaforoA[1], HIGH);
    digitalWrite(semaforoA[2], LOW);

    digitalWrite(semaforoB[0], LOW);
    digitalWrite(semaforoB[1], HIGH);
    digitalWrite(semaforoB[2], LOW);
  }
  delay(2000);
}
