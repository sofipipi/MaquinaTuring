//Actuadores Lineales
const int forwards = 7;
const int backwards = 6;

//Ultrasonido
const int Trigger = 2; 
const int Echo = 3;   
long t;
long d;
//Variables principales para la maquina

const int distanciaBeta= 8; // epsilon en la animación
const int distanciaUno= 2; // cantidad de unos que representan un numero entero
const int distanciaCero= 4; // operando

//Motor para el carrito
int entradaMotor1 = 4;
int entradaMotor2 = 5;
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
  pinMode(forwards, OUTPUT);
  pinMode(backwards, OUTPUT);

  //Ultrasonido
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

  //Motor con driver L298N
  pinMode(entradaMotor1, OUTPUT);
  pinMode(entradaMotor2, OUTPUT);
}
void loop() {
 
 // si la distancia corresponde a distanciaUno, significa que encontramos nuestra primera entrada en la cinta
 calcularDistancia();
 if(d==distanciaUno){
  
    if(q0){
      //continua moviendose a la derecha
      digitalWrite(entradaMotor1, HIGH);
      digitalWrite(entradaMotor2, LOW);
      
    }
    else if(q1){
      //continua moviendose a la derecha
      digitalWrite(entradaMotor1, HIGH);
      digitalWrite(entradaMotor2, LOW);
      
    }

    else if (q2){
      //cambio de 1 a beta
      //actuador
      digitalWrite(forwards, LOW);
      digitalWrite(backwards, HIGH);
      delay(500);
      digitalWrite(forwards, HIGH);
      digitalWrite(backwards, LOW);
      delay(500);

      //me muevo a la izquierda
      digitalWrite(entradaMotor1, LOW);
      digitalWrite(entradaMotor2, HIGH);
      //cambio de estado
      q2=false;
      q3=true;
    }
    else if(q3){
      //me muevo a la izquierda
      digitalWrite(entradaMotor1, LOW);
      digitalWrite(entradaMotor2, HIGH);
      
    }
    else if(q4){
      //me muevo a la izquierda
      digitalWrite(entradaMotor1, LOW);
      digitalWrite(entradaMotor2, HIGH);
    }
    else if(q5){
      
      //Extender el actuador
      digitalWrite(forwards, LOW);
      digitalWrite(backwards, HIGH);
      delay(2000); // esperar 2 segundos
      //Retraccion
      digitalWrite(forwards, HIGH);
      digitalWrite(backwards, LOW);
      delay(2000);// esperar 2 segundos
      //moverme derecha
      digitalWrite(entradaMotor1, HIGH);
      digitalWrite(entradaMotor2, LOW);
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
      digitalWrite(entradaMotor1, LOW);
      digitalWrite(entradaMotor2, HIGH); // mover izquierda
    }
    if(q4){
      q4=false;
      q5=true;
      digitalWrite(entradaMotor1, HIGH);
      digitalWrite(entradaMotor2, LOW); // mover derecha
    }
 }


 while (d==distanciaCero && q2){
    q2 = false;
    qf = true;
    //muevo izquierda
    digitalWrite(entradaMotor1, LOW);
    digitalWrite(entradaMotor2, HIGH);
    //cambio de 0 a beta
    //Extender el actuador
    digitalWrite(forwards, LOW);
    digitalWrite(backwards, HIGH);
    //retraccion
    digitalWrite(forwards, HIGH);
    digitalWrite(backwards, LOW);
 
 }
 if(qf){
  digitalWrite(entradaMotor1, LOW);
  digitalWrite(entradaMotor2, LOW);
  digitalWrite(forwards, LOW);
  digitalWrite(backwards, LOW);
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
