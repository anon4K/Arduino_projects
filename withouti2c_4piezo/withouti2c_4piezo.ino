#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int trigPin = A0;
const int echoPin = A1;

const int buzzerPin = A2;
const int greenLedPin = A3;
const int redLedPin = A4;

String password = "2356";
String input = "";
bool systemArmed = false;
bool alarmActive = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  delay(500);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, HIGH);
  delay(500);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  delay(500);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, HIGH);
  delay(500);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  delay(500);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, HIGH);
  delay(500);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  Serial.println("Enter Password to Arm System:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (input == password) {
        systemArmed = !systemArmed;
        if (systemArmed) {
          Serial.println("System Armed");
          digitalWrite(greenLedPin, HIGH);
        } else {
          Serial.println("System Disarmed");
          alarmActive = false;
          digitalWrite(buzzerPin, LOW);
          digitalWrite(greenLedPin, HIGH);
          digitalWrite(redLedPin, LOW);
        }
        input = "";
      } else {
        Serial.println("Wrong Password");
        alarmActive = true;
        input = "";
      }
      Serial.println("Enter Password to Arm/Disarm System:");
    } else if (key == '*') {
      input = "";
      Serial.println("Enter Password to Arm/Disarm System:");
    } else {
      input += key;
    }
  }

  if (systemArmed && !alarmActive) {
    if (detectMotion()) {
      alarmActive = true;
      soundAlarm();
    }
  }

  if (alarmActive) {
    if (input.length() > 0 && key == '#') {
      if (input == password) {
        alarmActive = false;
        digitalWrite(buzzerPin, LOW);
        digitalWrite(redLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
        Serial.println("Correct Password. Alarm Deactivated.");
        delay(2000);
        digitalWrite(greenLedPin, LOW);
      } else {
        digitalWrite(redLedPin, HIGH);
        Serial.println("Incorrect Password. Alarm Continues.");
      }
      input = "";
      Serial.println("Enter Password to Disarm Alarm:");
    }
  }
}

bool detectMotion() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1;

  if (distance < 20) { // Adjust the distance threshold as needed
    return true;
  } else {
    return false;
  }
}

void soundAlarm() {
  digitalWrite(greenLedPin, LOW);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(redLedPin, HIGH);
  Serial.println("Motion Detected! Alarm Activated.");
}
