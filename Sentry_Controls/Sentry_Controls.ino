#include <Stepper.h>
#include <Servo.h>

int inByte = 0;
char inData[5] = {0};
//int inData[0]Count = 0;
int index = 0;
int controlLRModifier;
char alt = 1;
int chargepos = 0;
int triggerpos = 0;
unsigned long time = 0;
int state = 0;


const int stepsPerRevolution = 500;
Stepper lemotor(stepsPerRevolution, 8,11,12,13);
//Stepper landscape(stepsPerRevolution, 8,11,12,13);
//Stepper portrait(stepsPerRevolution, 8,11,12,13);
Servo charger;
Servo trigger;

void setup(){
  charger.attach(14); //Digital Pin 1
  trigger.attach(15); //Digital Pin 2
  
  lemotor.setSpeed(60);
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
}
 
void loop() {
//  charger.write(180);
  while(Serial.available() > 0 && Serial.peek() != '#') {
    inByte = Serial.read();
    inData[index] = inByte;
    Serial.println(inData[index]);
    index++;
    inData[index] = '0';
  }
  Serial.read();
  if (inData[1] == '0') {alt = 1;}
  else {alt = inData[1] - '0';}

  if (index > 1) {
    if (index = 2) {
  controlLRModifier = inData[1] - '0';
    }
  while(inData[index] != '\0') {
    Serial.println(controlLRModifier);
  controlLRModifier = (controlLRModifier * 10 + inData[index] - '0');
  index++;
    }
        Serial.println(controlLRModifier);
  }
  index = 0;
//  Serial.println("Indata: ");  
//  Serial.println(inData[0]);
//  Serial.println("inData[0]Count: ");  
//  Serial.println(inData[0]Count);  
//
//  if (inData[0] == 'c') {
//  charger.attach(14);
//  if (state == 1) {
//    time = millis();
//    state = 2;
//  }
//  charger.writeMicroseconds(1000);
//  if (millis() - time > 300) {
//    inData[0] = 0;
//    state = 3;
//  }
//    
//  charger.write(180);
//  inData[0] = '0';
//  } else
  if (inData[0] == 'l') {
    lemotor.step(stepsPerRevolution * 6 / alt / 10);
    inData[0] ='0';
  } else if (inData[0] == 'r') {
    lemotor.step(-stepsPerRevolution * 6 / alt / 10);
    inData[0] ='0';
  } else if (inData[0] == 's' && state == 0) {
  charger.attach(14);
  if (state == 0) {
    time = millis();
    state = 1;
  }
  } else if (state != 0) {
  if (state == 1) {
  charger.writeMicroseconds(1000);
  }
  if (millis() - time > 1000 && state == 1) {
    state = 2;
  }
  if (state == 2) {
    time = millis();
    state = 3;
  }
  if (state == 3) {
  charger.writeMicroseconds(2000);
  }
  if (millis() - time > 200 && state == 3) {
    charger.writeMicroseconds(1500);
    charger.detach();  
    inData[0] = 0;
    state = 0;
  }
//  } else if (inData[0] == 'u') {
//  charger.attach(14);
//  if (state == 4) {
//    time = millis();
//    state = 5;
//  }
//  charger.writeMicroseconds(2000);
//  if (millis() - time > 200) {
//    inData[0] = 0;
//    state = 6;
//  }
//  charger.attach(14);
//  charger.writeMicroseconds(2000);
//  charger.write(0);  
//  inData[0] = '0';
  } else { 
//    charger.write(90); 
    charger.writeMicroseconds(1500);
    charger.detach();
  }  
//  Serial.flush();
}
  
