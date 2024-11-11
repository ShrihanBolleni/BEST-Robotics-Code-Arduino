/*
#include <Servo.h>
#include "Gizmo.h"

Servo DriveL, DriveR;
Gizmo gizmo;

void setup() {
  gizmo.begin();

  pinMode(GIZMO_MOTOR_1, OUTPUT);
  pinMode(GIZMO_MOTOR_2, OUTPUT);

  DriveL.attach(GIZMO_MOTOR_1);
  DriveR.attach(GIZMO_MOTOR_2);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  gizmo.refresh();

  int targetL, targetR;
  targetL = map(gizmo.getAxis(GIZMO_AXIS_LY), 0, 255, 0, 180);
  targetR = map(gizmo.getAxis(GIZMO_AXIS_RY), 0, 255, 0, 180);

  DriveL.write(targetL);
  DriveR.write(targetR);

  delay(20);
}
*/

#include <Servo.h>

// Define servo and button
Servo Dispenser;
//const int servoPin = 9;         // Pin connected to the servo signal
//const int buttonPinB = 6;       // Pin connected to button B on the controller

// Variables to track button press
bool buttonPressed = false;     // Current button state
bool previousButtonState = HIGH; // Previous button state (HIGH for unpressed with INPUT_PULLUP)
int servoPosition = 0;          // Servo position (0 or 90 degrees)

void setup() {
  // Initialize the servo and button
  Dispenser.attach(GIZMO_SERVO_3);
  pinMode(buttonPinB, INPUT_PULLUP); // Use pull-up resistor to keep button state stable
  servo.write(servoPosition);        // Set initial servo position to 0 degrees
}

void loop() {
  // Read the button state
  bool currentButtonState = gizmo.getButton(GIZMO_BUTTON_B);

  // Check if the button was just pressed
  if (currentButtonState == LOW && previousButtonState == HIGH) {
    // Toggle the servo position between 0 and 90 degrees
    servoPosition = (servoPosition == 0) ? 90 : 0;
    servo.write(servoPosition);      // Move servo to the new position
    delay(20);                       // Small delay for stability
  }

  // Update previous button state
  previousButtonState = currentButtonState;

  // Delay for button debouncing
  delay(50);
}
