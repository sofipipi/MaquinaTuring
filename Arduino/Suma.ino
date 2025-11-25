// Actuadores Lineales
const int forwards1 = 7;
const int backwards1 = 6;

const int forwards2 = 10;
const int backwards2 = 11;


// Ultrasonido
const int Trigger = 2;
const int Echo = 3;
long t;
long d;

// Distancias simbólicas
const int distanciaBeta = 8;
const int distanciaUno = 2;
const int distanciaCero = 4;

// Motores para los carritos
int entradaCarrito1Motor1 = 4;
int entradaCarrito1Motor2 = 5;

int entradaCarrito2Motor1 = 8;
int entradaCarrito2Motor2 = 9;

// Estados
bool q0 = true;
bool q1 = false;
bool q2 = false;
bool qf = false;

void setup() {
  pinMode(forwards1, OUTPUT);
  pinMode(backwards1, OUTPUT);
  
  pinMode(forwards2, OUTPUT);
  pinMode(backwards2, OUTPUT);
  
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trigger, LOW);

  pinMode(entradaCarrito1Motor1, OUTPUT);
  pinMode(entradaCarrito1Motor2, OUTPUT);

  pinMode(entradaCarrito2Motor1, OUTPUT);
  pinMode(entradaCarrito2Motor2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  calcularDistancia();

  // Estado q0
  if(q0){
    if(d == distanciaUno){
      // sigue en q0, mueve derecha
      moverMotoresDerecha();
    }
    else if(d == distanciaCero){
      // cambia 0 por 1, pasa a q1
      activarActuador2(); // simula escritura
      //derecha
      moverMotoresDerecha();
      q0 = false;
      q1 = true;
    }
    else if(d == distanciaBeta){
      // sigue en q0, mueve derecha
      moverMotoresDerecha();
    }
  }

  // Estado q1
  else if(q1){
    if(d == distanciaUno){
      // sigue en q1, mueve derecha
      moverMotoresDerecha();
    }
    else if(d == distanciaBeta){
      // cambia a q2, mueve izquierda
      moverMotoresIzquierda();
      q1 = false;
      q2 = true;
    }
  }

  // Estado q2
  else if(q2){
    if(d == distanciaUno){
      // cambia 1 por beta, pasa a qf
      activarActuador1();
      moverMotoresIzquierda();
      q2 = false;
      qf = true;
    }
  }

  // Estado final
  if(qf){
    Apagar();

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

void activarActuador1() {
  digitalWrite(forwards1, LOW);
  digitalWrite(backwards1, HIGH);
  delay(500);
  digitalWrite(forwards1, HIGH);
  digitalWrite(backwards1, LOW);
  delay(500);
}
void activarActuador2() {
  digitalWrite(forwards2, LOW);
  digitalWrite(backwards2, HIGH);
  delay(500);
  digitalWrite(forwards2, HIGH);
  digitalWrite(backwards2, LOW);
  delay(500);

}
void moverMotoresDerecha(){
  //carrito 1
  digitalWrite(entradaCarrito1Motor1, HIGH);
  digitalWrite(entradaCarrito1Motor2, LOW);
  //carrito 2
  digitalWrite(entradaCarrito2Motor1, HIGH);
  digitalWrite(entradaCarrito2Motor2, LOW);
}
void moverMotoresIzquierda(){
  //carrito 1
  digitalWrite(entradaCarrito1Motor1, LOW);
  digitalWrite(entradaCarrito1Motor2, HIGH);
  //carrito 2
  digitalWrite(entradaCarrito2Motor1, LOW);
  digitalWrite(entradaCarrito2Motor2, HIGH);
}
void Apagar(){
  //carrito 1
  digitalWrite(entradaCarrito1Motor1, LOW);
  digitalWrite(entradaCarrito1Motor2, LOW);
  //carrito 2
  digitalWrite(entradaCarrito2Motor1, LOW);
  digitalWrite(entradaCarrito2Motor2, LOW);

  //Actuadores
  digitalWrite(forwards1, LOW);
  digitalWrite(backwards1, LOW);

  digitalWrite(forwards2, LOW);
  digitalWrite(backwards2, LOW);

}
