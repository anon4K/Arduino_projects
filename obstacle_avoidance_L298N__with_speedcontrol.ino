#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 400 
#define ENA 3  // PWM pin for left motor
#define ENB 10 // PWM pin for right motor

int speedLeft = 150;   // You can adjust these values between 0-255
int speedRight = 150;  // to set speed for each side


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

Servo myservo;   

int distance = 100;
int pos = 0;

void setup() {
  //set up motors
  pinMode(7,OUTPUT);   //left motors forward
  pinMode(6,OUTPUT);   //left motors reverse
  pinMode(5,OUTPUT);   //right motors forward
  pinMode(4,OUTPUT);   //right motors reverse
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  Serial.begin(9600);

  // set up servo
  myservo.attach(9); 
  myservo.write(90); 
  delay(2000);
  
  distance = readPing();
  delay(60);
}

void loop() {
  int distanceR = 0;
  int distanceL =  0; 
  Serial.println(distance);
  
  if(distance<=20)
  {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(100);
  distanceR = lookRight();
  delay(50);
  distanceL = lookLeft();
  delay(50);
  
  if(distanceR>=distanceL)
  {
    if(distanceR<=30 && distanceL<=30) { 
      for(int i = 0; i < 2; i++) { // turn around
        turnRight();
        moveStop();
        delay(100);
      }
    } else {
      turnRight();
      moveStop();
      delay(100);
    }
  } else if(distanceR<distanceL)
  {
    if(distanceR<30 && distanceL<=30) { // if both sides are too narrow
      for(int i = 0; i < 2; i++) { // turn around
        turnLeft();
        moveStop();
        delay(100);
      }
    } else {
      turnLeft();
      moveStop();
      delay(100);
    }
  }
} else moveForward();

  distance = readPing();
  delay(60);
} 

int lookLeft()
{
  for (pos = 90; pos <= 180; pos += 1) { // goes from 90 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       
  }
  int distance = readPing();
  delay(60);
  
  for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 90 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       
  }
  return distance; // return distance on the left side
}

int lookRight()
{
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degree
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       
  }
  int distance = readPing();
  delay(60);
  
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degree to 90 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       
  }
  return distance; // return distance on the right side
}

int readPing() { 
  int cm = sonar.ping_cm();
  if(cm==0) // if the measured distance exceeds the measuring limit of the ultrasonic sensor, by default the sonar.ping_cm() function will return a value of 0
  { // Due to the distance of 0 the robot will keep avoiding even when there is nothing in front of it
    cm = MAX_DISTANCE; // To fix this, we set the distance to the pre-defined MAX_DISTANCE of 400 cm
  }
  return cm;
}

void moveStop() {
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
} 
  
void moveForward() {
  digitalWrite(7,HIGH);
  digitalWrite(5,HIGH);
  analogWrite(ENA, speedLeft);  
  analogWrite(ENB, speedRight); 
}

void moveBackward() {
  digitalWrite(6,HIGH);
  digitalWrite(4,HIGH);
  analogWrite(ENA, speedLeft);  
  analogWrite(ENB, speedRight); 
}  

void turnRight() {
  digitalWrite(7,HIGH);
  digitalWrite(4,HIGH);     
  delay(250);
  digitalWrite(7,HIGH);
  digitalWrite(5,HIGH); 
  analogWrite(ENA, speedLeft);  // Set left motor speed
  analogWrite(ENB, speedRight); // Set right motor speed     
} 
 
void turnLeft() {  
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);   
  delay(250);
  digitalWrite(7,HIGH);
  digitalWrite(5,HIGH);
  analogWrite(ENA, speedLeft);  // Set left motor speed
  analogWrite(ENB, speedRight); // Set right motor speed
}    
