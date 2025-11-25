# Simulación Maquina de Turing
**Integrantes:**
> Sofía Contreras, 21702328-9
> Máximo Jofré, 21675371-2

**Profesor:**
> José Luis Veas Muñoz

# Etapas del Proyecto

## 1. Análisis Teórico

Una máquina de Turing es un dispositivo abstracto para modelar el cálculo como manipulación mecánica de símbolos, mediante el uso de un cabezal que escribe y lee una cinta basándose en las reglas planteadas por el autómata.

En una máquina de Turing la cinta, que es teóricamente infinita, es el medio donde se almacenan los datos que guiarán las transiciones de estados, en esta se trabaja con un ***alfabeto de 3 símbolos*** donde ***1 representa los números***, ***0 representa las operaciones*** y los ***espacios vacíos (beta)*** que sirven para delimitar las operaciones. 

En la representación de los números del sistema decimal se utiliza una codificación unaria, que se refiere a la concatenación de n unos (1) para representar un número n. Por ejemplo, 1111, representa 4 y empleando una operación, 111011111, representa 3+5, 3-5, 3*5 o 3/5, dependiendo qué reglas siga el autómata.
El uso de la codificación unaria simplifica la lógica de las operaciones, ya que la máquina sólo necesita reconocer tres símbolos, sin embargo, presenta la limitación de que requiere cintas muy largas para representar números grandes lo que la hace poco eficiente en la práctica, aunque muy útil para el análisis teórico y pedagógico.

## 2. Definición del Automáta

El autómata es una cantidad finita de estados por la cual pasará la máquina para poder realizar una operación, autómatas distintos realizan una operación específica. Para poder cambiar de estados se utilizan los datos escaneados por la máquina, cada estado tiene sus propias reglas para transicionar a otro estado según el dato recibido.
Teniendo lo anterior en cuenta se definen los siguientes autómatas:
### a. Operación Suma 

*Estados*:
- ***q0***: recorrer el primer número y al encontrar el primer 0 lo reemplaza por 1.
- ***q1***: recorrer hasta encontrar un valor beta y retroceder 1 espacio.
- ***q2***: se reemplaza el 1 por un Beta.
- ***qf***: estado final para parar la máquina.
  
*Tabla*:
| Estado | Beta | 0 | 1 |
|---|---|---|---|
| q0 | (q0/Beta, Derecha) | (q1/1, Derecha) | (q0/1,Derecha)|
| q1 | (q2/Beta, Izquierda) | X | (q1/1,Derecha) |
| q2 | X | X | (qf/Beta, Derecha) |
| qf | X | X | X |
### b. Operación Resta

*Estados*:
- ***q0***: avanza a la derecha siempre que lea 1, si lee “0”  continua al siguiente estado hacia la derecha
- ***q1***: avanza a la derecha siempre que lea 1, en caso de leer beta avanza al siguiente estado con dirección a  la izquierda.
- ***q2***: cambia de estado al encontrar 1 reemplazandolo por beta y moviéndose a la izquierda, en caso de encontrar 0 lo cambia a beta y se mueve a la izquierda terminando la operación
- ***q3***: mientras lea 1 avanza a la izquierda y leído 0 cambia de estado moviéndose a la izquierda
- ***q4***: se mantiene mientras lee 1 moviéndose a la izquierda, cambia al encontrar vacío moviéndose a la derecha.
- ***q5***: Cambia el último 1 a beta y se mueve a la derecha volviendo al estado inicial.
- ***qf***: estado final para parar la máquina.

*Tabla*:
| Estado | Beta | 0 | 1 |
|---|---|---|---|
| q0 | X | (q1/0, Derecha) | (q0/1,Derecha) |
| q1 | (q2/Beta,Izquierda) | X | (q1/1,Derecha) |
| q2 | (q3/Beta,Izquierda) | (qf/Beta,Izquierda) | (q3/1, Izquierda) |
| q3 | X | (q4/0,Izquierda) | (q3/1,Izquierda) |
| q4 | (q5/Beta,Derecha) | X | (q4/1,Izquierda) |
| q5 | X | X | (q0/Beta,Derecha) |
| qf | X | X | X |

## 3. Propuesta de Diseño
### Idea General

Para la cinta de datos se utilizará una sucesión de contenedores con un bloque adentro, el cual se moverá horizontalmente en un solo eje para representar los datos, en este caso si el bloque está en lo más profundo del contenedor entonces representará un espacio vacío, al medio representa un 0 y al tope representará un 1. Esta cinta es estática.

Para la lectura de estos datos se utilizará un sensor ultrasónico que mide distancia.

Para la escritura se utilizarán actuadores lineales, uno por lado, para empujar el bloque que está en el contenedor.

El cabezal, compuesto por el sensor y los actuadores lineales, será montado en un carro sobre un riel para su movilidad horizontal. Además de un riel adicional paralelo a este que tiene otro carro está compuesto de los mismos elementos menos el sensor.

### Primer Modelo 3D

- Dos carritos y rieles
  
  <img width="1066" height="565" alt="image" src="https://github.com/user-attachments/assets/c0d67259-6c3a-4a44-a5b6-93060e8e2663" />

### Segundo Modelo 3D

- Sin riel
  
  <img width="1290" height="1110" alt="image" src="https://github.com/user-attachments/assets/3b648a53-7081-43d0-b378-a752015359c7" />

### Materiales para implementación física

Los materiales a utilizar serían:

- Arduino Uno
- Protoboard
- Jumpers
- Relé de 4 canales o 2 de 2 canales
- Driver L298N
- 2 Motor DC
- Sensor Ultrasónico
- 2 actuadores lineales
- Fuente voltaje 12 V

## 4. Código Arduino para realizarlo en físico

  ### a. Explicación General
La “cinta” del autómata está representada por una serie de objetos ubicados a distintas distancias, medibles mediante un sensor ultrasónico HC-SR04, cada objeto representa un símbolo:

+ distanciaUno → símbolo 1

+ distanciaCero → símbolo 0

+ distanciaBeta → símbolo β (blanco / epsilon)

_El “cabezal lector/escritor” se implementa combinando:_

* Carritos motorizados → mover el cabezal izquierda/derecha

* Actuadores lineales → “escribir” sobre la cinta (cambiar un símbolo)

El autómata utiliza variables booleanas para representar su estado actual (q0, q1, q2,... ).
La lógica del loop() ejecuta la transición de estados según el símbolo leído.

### b. Declaración de pines y constantes
**Actuadores Lineales**
```
const int forwards1 = 7;
const int backwards1 = 6;

const int forwards2 = 10;
const int backwards2 = 11;
```
Cada actuador usa dos relés para invertir la polaridad, lo que permite:

-extensión

-retracción
**Ultrasónido**
```
const int Trigger = 2;
const int Echo = 3;
long t;
long d;
```
El sensor ultrasónico sirve como lector de cinta, midiendo la distancia al objeto y determinando qué símbolo representa.

**Valores asignados a cada símbolo**

```
const int distanciaBeta= 8;
const int distanciaUno= 2;
const int distanciaCero= 4;
```

**Motores del cabezal**
```
int entradaCarrito1Motor1 = 4;
int entradaCarrito1Motor2 = 5;

int entradaCarrito2Motor1 = 8;
int entradaCarrito2Motor2 = 9;
```
Controlan la dirección izquierda/derecha mediante un driver L298N.

**Estados del Automata**
```
bool q0=true;
bool q1=false;
bool q2=false;
bool q3=false;
bool q4=false;
bool q5=false;
bool qf=false;

```
### c. Setup()
El setup() inicializa los pines del sistema:

* Configura actuadores como salida

* Configura Trigger y Echo del ultrasónico

* Inicializa los motores que mueven la cinta/cabezal
  
### d. Loop()

Dentro del loop() se ejecuta continuamente la lógica del autómata:

- Lectura del símbolo actual mediante calcularDistancia()

- Determinación de transición según:

    --> **estado actual**

    --> **símbolo leído**

-  Acciones físicas:

    --> **mover cabezal a izquierda/derecha**

    --> **“escribir” mediante actuadores**

- Actualización de estado

- Detención si se llega al estado final qf

### e. Funciones

***CalcularDistancia***

* Aquí se emite un pulso de 10 μs y se mide el tiempo de retorno.
* El tiempo se convierte en distancia, representando el símbolo leído.

***ActivarActuador1/ActivarActuador2***

* Simula la escritura sobre la cinta.

***MoverMotoresDerecha/Izquierda***

* Simula el movimiento del cabezal

***Apagar***

* Detiene todo al llegar al estado final.
