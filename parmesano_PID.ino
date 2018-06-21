/*
* Parmesano PID
*
* Programa para Robot Lamborghino. 
* Incluye funciones para el control de los motores del robot, calibracion manual y control PID.
*
* Francisco Lara - Matia Cornejo
*/
//Se incluye la libreria para los sensores frontales
#include <QTRSensors.h>

//Mapeo de pines                                                                                                                                                                                                                                                                     
#define AIN1 7   
#define AIN2 8 
#define PWMA 6

#define BIN1 9 
#define BIN2 4  
#define PWMB 5 

#define BUZZER 10

#define NUM_SENSORS             6    
#define NUM_SAMPLES_PER_SENSOR  4    
#define EMITTER_PIN             11  
#define LED     13  

//Velocidad nominal del robot y diferencial maximo
int VELNOM = 80;
int DIFMAX = VELNOM;

//Constantes PID 60 20 0.1
 
float Kp = 31.0;
float Kd = 55.0;
float Ki = 0.59;

// Configuración de la librería QTR-8A         
QTRSensorsAnalog qtra((unsigned char[]) 
  {A0, A1, A2, A3, A4, A5}
, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);

unsigned int sensorValues[NUM_SENSORS];


// Función accionamiento motor izquierdo
void Motoriz(int value)
{
  if ( value >= 0 )
  {
    digitalWrite(BIN1,HIGH);
    digitalWrite(BIN2,LOW);
  }
  else
  {
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,HIGH);
    value *= -1;
  }
  analogWrite(PWMB,value);
}

// Función accionamiento motor derecho
void Motorde(int value)
{  
  if ( value >= 0 )
  {
    digitalWrite(AIN1,HIGH);
    digitalWrite(AIN2,LOW);
  }
  else
  {
    digitalWrite(AIN1,LOW);
    digitalWrite(AIN2,HIGH);
    value *= -1;
  }    
  analogWrite(PWMA,value);
}


//Accionamiento de motores
void Motor(int left, int righ)
{
  Motoriz(left);
  Motorde(righ);
}



void setup() {
  // Se declaran como salida los pines utilizados
  pinMode(LED   ,OUTPUT);
  pinMode(BIN2  ,OUTPUT);
  pinMode(BIN1  ,OUTPUT);
  pinMode(PWMB  ,OUTPUT);
  pinMode(AIN1  ,OUTPUT);
  pinMode(AIN2  ,OUTPUT);
  pinMode(PWMA  ,OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Calibracion sensores
  for ( int i=0; i<70; i++)
  {
    digitalWrite(LED, HIGH); delay(20);
    qtra.calibrate();
    digitalWrite(LED, LOW);  delay(20);
  }
  //Espera 3 segundos antes de partir
  delay(3000);
  //Musica Mario
  tone(BUZZER, 1319/2, 100);
  delay(117);
  tone(BUZZER,1319/2 , 100);
  delay(333);
  tone(BUZZER, 1319/2, 100);
  delay(334);
  tone(BUZZER, 1047/2, 100);
  delay(117);
  tone(BUZZER, 1319/2 , 100);
  delay(334);
  tone(BUZZER,1564/2 , 100);
  delay(600);
  tone(BUZZER, 784/2, 100);
  //Para modulo bluetooth
  //Serial.begin(9600);
}
//Declaracion de variables
unsigned int position = 0; 

int proporcional = 0;
int derivativo = 0;
int integrativo = 0;

int error2 = 0;
int error3 = 0;
int error4 = 0;
int error5 = 0;
int error6 = 0;

int diferencial = 0;
int ultimo_diferencial;

// Para Modulo bluetooth
//int dato;

void loop() {

  /*
  //Para usar el modulo bluetooth
  if(Serial.available()){
    dato = Serial.read();
    switch(dato){
      case 81: //Q
        Kd++;
        break;
      case 65: //A
        Kd--;
        break;
      case 87: //W
        Kp++;
        break;
      case 83: //S
        Kp--;
        break;
      case 69: //E
        Kd++;
        break;
      case 68: //D
        Kd--;
        break;
      default:
        break; 
    }    
  }*/
  
  position = qtra.readLine(sensorValues, true, false); // Guarda la posicion en la variable position. Valor de 0 a 5000
  
  proporcional = ((int)position) - 2500; // Se asigna la posicion central en 0 y se guarda en la variable proporcional
  derivativo = proporcional - ultimo_diferencial; // Se calcula la variable derivativa restando el valor actual de la medición y el valor de la medicion anterior 
  integrativo = ultimo_diferencial + error2 + error3 + error4 + error5 + error6; // Se calcula la variable integral sumando las ultimas seis mediciones guardadas

  // Se calcula el diferencial, correspondiente a cada una de las variables calculadas anteriormente, ponderadas por sus respectivas constantes PID
  diferencial = proporcional * Kp + integrativo * Ki + derivativo * Kd;

  // Se actualizan los errores guardadados
  error6 = error5;
  error5 = error4;
  error4 = error3;
  error3 = error2;
  error2 = ultimo_diferencial;
  ultimo_diferencial = proporcional;

  // Si el diferencial calculado supera al diferencial maximo permitido, este adquiere ese valor
  if(diferencial >= DIFMAX)
    diferencial = DIFMAX;    
  else if(diferencial <= -DIFMAX)
    diferencial = -DIFMAX;

  // Si el diferencial es positivo, se resta a la velocidad de la rueda izquierda. Si es negativo, se resta a la rueda derecha.
  if(diferencial >= 0)
  {
    Motor(VELNOM - diferencial, VELNOM );
  }
  else
  {
    Motor(VELNOM, VELNOM + diferencial); 
  }
}
