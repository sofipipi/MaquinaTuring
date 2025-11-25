// Actuadores Lineales
const int forwards = 7;
const int backwards = 6;

// Ultrasonido
const int Trigger = 2;
const int Echo = 3;
long t;
long d;

// Distancias simbólicas
const int distanciaBeta = 8;
const int distanciaUno = 2;
const int distanciaCero = 4;

// Motor para el carrito
int entradaMotor1 = 4;
int entradaMotor2 = 5;

// Estados
bool q0 = true;
bool q1 = false;
bool q2 = false;
bool qf = false;

void setup() {
  pinMode(forwards, OUTPUT);
  pinMode(backwards, OUTPUT);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);

  pinMode(entradaMotor1, OUTPUT);
  pinMode(entradaMotor2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  calcularDistancia();

  // Estado q0
  if(q0){
    if(d == distanciaUno){
      // sigue en q0, mueve derecha
      digitalWrite(entradaMotor1, HIGH);
      digitalWrite(entradaMotor2, LOW);
    }
    else if(d == distanciaCero){
      // cambia 0 por 1, pasa a q1
      activarActuador(); // simula escritura
      digitalWrite(entradaMotor1, HIGH);
      digitalWrite(entradaMotor2, LOW);
      q0 = false;
      q1 = true;
    }
    else if(d == distanciaBeta){
      // sigue en q0, mueve derecha
      digitalWrite(entradaMotor1, HIGH);
      digitalWrite(entradaMotor2, LOW);
    }
  }

  // Estado q1
  else if(q1){
    if(d == distanciaUno){
      // sigue en q1, mueve derecha
      digitalWrite(entradaMotor1, HIGH);
      digitalWrite(entradaMotor2, LOW);
    }
    else if(d == distanciaBeta){
      // cambia a q2, mueve izquierda
      activarActuador(); // simula escritura
      digitalWrite(entradaMotor1, LOW);
      digitalWrite(entradaMotor2, HIGH);
      q1 = false;
      q2 = true;
    }
  }

  // Estado q2
  else if(q2){
    if(d == distanciaUno){
      // cambia 1 por beta, pasa a qf
      activarActuador(); // simula escritura
      digitalWrite(entradaMotor1, LOW);
      digitalWrite(entradaMotor2, HIGH);
      q2 = false;
      qf = true;
    }
  }

  // Estado final
  if(qf){
    digitalWrite(entradaMotor1, LOW);
    digitalWrite(entradaMotor2, LOW);
    digitalWrite(forwards, LOW);
    digitalWrite(backwards, LOW);
    while(true); // detener el loop
  }
}

void calcularDistancia() {
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);

  t = pulseIn(Echo, HIGH);
  d = t / 59;

  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.println("cm");
}

void activarActuador() {
  digitalWrite(forwards, LOW);
  digitalWrite(backwards, HIGH);
  delay(500);
  digitalWrite(forwards, HIGH);
  digitalWrite(backwards, LOW);
  delay(500);
}
