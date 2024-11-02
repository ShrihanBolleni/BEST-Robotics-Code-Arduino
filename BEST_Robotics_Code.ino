#include "Gizmo.h"
#include <Servo.h>

Gizmo gizmo;

// Joystick pins for motors
const int joystickY = A0; // Y-axis
const int joystickX = A1; // X-axis

// Motor numbers
const int leftMotor = 1;
const int rightMotor = 2;

// Servo setup
Servo servo1;
Servo servo2;
Servo servo3;
const int servoPin1 = 3;  // Pin for servo 1
const int servoPin2 = 4;  // Pin for servo 2
const int servoPin3 = 5;  // Pin for servo 3

// Button pins for servos
const int buttonPin1 = 6; // Button to control servo 1
const int buttonPin2 = 7; // Button to control servo 2
const int buttonPin3 = 8; // Button to control servo 3

// State tracking for servo positions
bool servo1Moved = false;
bool servo2Moved = false;
bool servo3Moved = false;

void setup() {
  gizmo.begin();
  Serial.begin(9600);

  // Initialize motors
  pinMode(joystickY, INPUT);
  pinMode(joystickX, INPUT);

  // Attach servos
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);

  // Initialize buttons
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
}

void loop() {
  // Read joystick values and control motors
  int yValue = analogRead(joystickY);
  int xValue = analogRead(joystickX);

  int forwardSpeed = map(yValue, 0, 1023, -255, 255);
  int turnSpeed = map(xValue, 0, 1023, -255, 255);

  int leftMotorSpeed = constrain(forwardSpeed + turnSpeed, -255, 255);
  int rightMotorSpeed = constrain(forwardSpeed - turnSpeed, -255, 255);

  gizmo.setMotor(leftMotor, leftMotorSpeed);
  gizmo.setMotor(rightMotor, rightMotorSpeed);
  gizmo.refresh();

  // Check button states and control servos
  if (digitalRead(buttonPin1) == LOW && !servo1Moved) {
    servo1.write(90);  // Move servo 1 to 90 degrees
    servo1Moved = true;
  } else if (digitalRead(buttonPin1) == HIGH && servo1Moved) {
    servo1.write(0);   // Reset servo 1 to 0 degrees
    servo1Moved = false;
  }

  if (digitalRead(buttonPin2) == LOW && !servo2Moved) {
    servo2.write(90);  // Move servo 2 to 90 degrees
    servo2Moved = true;
  } else if (digitalRead(buttonPin2) == HIGH && servo2Moved) {
    servo2.write(0);   // Reset servo 2 to 0 degrees
    servo2Moved = false;
  }

  if (digitalRead(buttonPin3) == LOW && !servo3Moved) {
    servo3.write(90);  // Move servo 3 to 90 degrees
    servo3Moved = true;
  } else if (digitalRead(buttonPin3) == HIGH && servo3Moved) {
    servo3.write(0);   // Reset servo 3 to 0 degrees
    servo3Moved = false;
  }

  delay(50); // Small delay for smoother control
}
