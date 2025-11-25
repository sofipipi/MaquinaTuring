// Actuadores Lineales
const int forwards1 = 7;
const int backwards1 = 6;

const int forwards2 = 10;
const int backwards2 = 11;

//Ultrasonido
const int Trigger = 2; 
const int Echo = 3;   
long t;
long d;
//Variables principales para la maquina

const int distanciaBeta= 8; // epsilon en la animación
const int distanciaUno= 2; // cantidad de unos que representan un numero entero
const int distanciaCero= 4; // operando

// Motores para los carritos
int entradaCarrito1Motor1 = 4;
int entradaCarrito1Motor2 = 5;

int entradaCarrito2Motor1 = 8;
int entradaCarrito2Motor2 = 9;

//booleanos

bool q0=true;
bool q1=false;
bool q2=false;
bool q3=false;
bool q4=false;
bool q5=false;
bool qf=false;

void setup() {
  //Actuadores Lineales (configurados con relé)
  pinMode(forwards1, OUTPUT);
  pinMode(backwards1, OUTPUT);
  pinMode(forwards2, OUTPUT);
  pinMode(backwards2, OUTPUT);
  
  //Ultrasonido
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

  //Motor con driver L298N
  pinMode(entradaCarrito1Motor1, OUTPUT);
  pinMode(entradaCarrito1Motor2, OUTPUT);

  pinMode(entradaCarrito2Motor1, OUTPUT);
  pinMode(entradaCarrito2Motor2, OUTPUT);

}
void loop() {
 
 // si la distancia corresponde a distanciaUno, significa que encontramos nuestra primera entrada en la cinta
 calcularDistancia();
 if(d==distanciaUno){
  
    if(q0){
      //continua moviendose a la derecha
      moverMotoresDerecha();
      
    }
    else if(q1){
      //continua moviendose a la derecha
      moverMotoresDerecha();
      
    }

    else if (q2){
      //cambio de 1 a beta
      //actuador
      activarActuador1();
      
      //me muevo a la izquierda
      moverMotoresIzquierda();
      
      //cambio de estado
      q2=false;
      q3=true;
    }
    else if(q3){
      //me muevo a la izquierda
      moverMotoresIzquierda();
      
    }
    else if(q4){
      //me muevo a la izquierda
      moverMotoresIzquierda();
    }
    else if(q5){
      
      activarActuador1();
      //moverme derecha
      moverMotoresDerecha();
      q5=false;
      q0=true;
    }
  

 }

 else if(d==distanciaCero){
      if(q0){
         q0=false;
         q1=true;
        }
      if (q3){
        //cambio de estado
        q3=false;
        q4=true;
        
      }
 
 }

 else if(d==distanciaBeta){
    if (q1){
      q1=false;
      q2=true;
      moverMotoresIzquierda();
    }
    if(q4){
      q4=false;
      q5=true;
      moverMotoresDerecha();
    }
 }


 while (d==distanciaCero && q2){
    q2 = false;
    qf = true;
    //muevo izquierda
    moverMotoresIzquierda();
    //cambio de 0 a beta
    //Extender el actuador
    activarActuador1();
 
 }
 if(qf){
  Apagar();
  while(true); // detener el loop
}

 
  
}
void calcularDistancia() {
 

  // Generar pulso en Trigger
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);  // pulso de 10us
  digitalWrite(Trigger, LOW);

  // Medir duración del pulso en Echo
  t = pulseIn(Echo, HIGH);

  // Convertir tiempo a distancia
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