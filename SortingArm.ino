#include <Servo.h>

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

const int Trigger = 12;   //Pin digital 2 para el Trigger del sensor
const int Echo = 13;   //Pin digital 3 para el Echo del sensor

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

Servo base;      //4 ejes del brazo robotico
Servo leftAxis;
Servo rightAxis;
Servo gripper;

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0
  
  base.attach(3);
  leftAxis.attach(9);
  rightAxis.attach(10);
  gripper.attach(11);


}

void loop() {
  home();
  delay(100);


  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm

  Serial.println(d);
 
  if (d<=7 && d>=5){
    
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  redFrequency = pulseIn(sensorOut, LOW);

  redColor = map(redFrequency, 22, 55, 255,0);
  
  Serial.print("R = ");
  Serial.print(redColor);
  delay(100);
  
 
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
 
  greenFrequency = pulseIn(sensorOut, LOW);
  
  greenColor = map(greenFrequency, 43, 90, 255, 0);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenColor);
  delay(100);
 
 
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
 
  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency, 40, 89, 255, 0);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.print(blueColor);
  delay(100);

  // Checks the current detected color and prints
  // a message in the serial monitor
  if(redColor > greenColor && redColor > blueColor){
      Serial.println(" - RED detected!");
      pick();
      home();
      placeRed();
  }
  if(greenColor > redColor && greenColor > blueColor){
    Serial.println(" - GREEN detected!");
    pick();
    home();
    placeGreen();
  }
  if(blueColor > redColor && blueColor > greenColor){
    Serial.println(" - BLUE detected!");
    pick();
    home();
    placeBlue();
  }

  
  }
  delay(100);
  

}


void home() {
  base.write(90);
  leftAxis.write(160);
  rightAxis.write(25);
  gripper.write(100);
}


void pick() {
  gripper.write(175);
  delay(100);


  for (int i = 90; i >= 42; i--) {
    base.write(i);
    delay(80);
  }

  for (int i = 25; i <= 70; i++) {
    rightAxis.write(i);
    delay(80);
  }

  for (int i = 160; i >= 90; i--) {
    leftAxis.write(i);
    delay (80);
  }

  for (int i = 70; i <= 90; i++) {
    rightAxis.write(i);
    delay(80);
  }

  gripper.write(100);
  delay(500);
  
   for (int i = 90; i >= 60; i --) {
    rightAxis.write(i);
    delay(80);
  }

  
  for (int i = 90; i <= 160; i++) {
    leftAxis.write(i);
    delay (80);
  }

  for (int i = 60; i >= 50; i --) {
    rightAxis.write(i);
    delay(80);
  }

   for (int i = 42; i <= 90; i++) {
    base.write(i);
    delay(80);
  }
  
}


void placeRed() {
  for (int i = 90; i >= 85; i--) {
    base.write(i);
    delay(100);
  }

  for (int i = 50; i <= 100; i++) {
    rightAxis.write(i);
    delay(80);
  }
  gripper.write(175);
  delay(100);
  
  for (int i = 100; i >= 50; i--) {
    rightAxis.write(i);
    delay(80);
  }

  for (int i = 85; i >= 90; i--) {
    base.write(i);
    delay(100);
  }

  
}

void placeBlue() {
  for (int i = 90; i <= 140; i++) {
    base.write(i);
    delay(100);
  }

  for (int i = 50; i <= 70; i++) {
    rightAxis.write(i);
    delay(80);
  }
  gripper.write(175);
  delay(100);

  for (int i = 70; i >= 50; i--) {
    rightAxis.write(i);
    delay(100);
  }

   for (int i = 140; i >= 90; i--) {
    base.write(i);
    delay(100);
  }

   

  
}

void placeGreen() {
  for (int i = 90; i <= 110; i++) {
    base.write(i);
    delay(100);
  }

  for (int i = 50; i <= 100; i++) {
    rightAxis.write(i);
    delay(80);
  }
  gripper.write(175);
  delay(100);

  for (int i = 100; i >= 50; i--) {
    rightAxis.write(i);
    delay(80);
  }

  for (int i = 110; i >=90 ; i--) {
    base.write(i);
    delay(100);
  }

  
  
}
