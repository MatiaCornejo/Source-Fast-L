#include <QTRSensors.h>

//sudo chmod a+rw /dev/ttyUSB* abrir puerto

//CONSTANTES
#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2
#define BUZZER 10                  // parlante
#define AIN1 9    // pin 1 de dirección del Motor Izquierdo
#define AIN2 4    // pin 2 de dirección del Motor Izquierdo
#define PWMA 5    // pin PWM del Motor Izquierdo
#define BIN1 7   // pin 1 de dirección del Motor Derecho
#define BIN2 8   // pin 2 de dirección del Motor Derecho
#define PWMB 6    // pin PWM del Motor Derecho
#define VAL 90
#define SUBVAL 80
 

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {0, 1, 2, 3, 4, 5}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
unsigned int valueA, valueB;


void setup() {
  // put your setup code here, to run once:
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(10,OUTPUT);
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  tone(BUZZER,1300,50);
  delay(1000);
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
  tone(BUZZER,1300,100);

}

void loop() {
  //entero sin signo, siempre positivo
  unsigned int position = qtra.readLine(sensorValues);
  /*for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }*/
  Serial.println(position); // comment this line out if you are using raw values
  if(position<2300){
    valueA = VAL;
    valueB = VAL-SUBVAL;
  }
  else if(position > 2700){
    valueA = VAL-SUBVAL;
    valueB = VAL;
  }
  else{
    valueA = VAL;
    valueB = VAL;
  }
  
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, valueB);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, valueA);
  delay(250);

}
