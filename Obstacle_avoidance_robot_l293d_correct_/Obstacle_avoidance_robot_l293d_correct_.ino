#include <Servo.h>
#include <AFMotor.h>


// Define pins for the Ultrasonic Sensor
const int trigPin = A0;
const int echoPin = A1;

// Define distance threshold in cm
const int threshold = 20;

Servo myservo;

// Create an instance of the Adafruit Motor Shield library
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

void setup() {
  // Set the pinMode for the Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(10);  
  myservo.write(90); 
  delay(1000);
  
  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  // Measure the distance using the Ultrasonic Sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58;
  
  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // If the distance is less than the threshold, stop the robot and turn it
  if (distance <= threshold) {
    stop();
    delay(1000);
    turnLeft();
    delay(1000);
  }
  // Otherwise, move the robot forward
  else {
    moveForward();
  }
}

// Define a function to move the robot forward
void moveForward() {
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  motor3.setSpeed(100);
  motor4.setSpeed(100);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

// Define a function to move the robot backward
void moveBackward() {
  motor1.setSpeed(100);
  motor2.setSpeed(100);
  motor3.setSpeed(100);
  motor4.setSpeed(100);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

// Define a function to turn the robot left
void turnLeft() {
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

// Define a function to turn the robot right
void turnRight() {
  motor1.setSpeed(150);
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

// Define a function to stop the robot
void stop() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
