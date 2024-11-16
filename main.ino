#include <Servo.h>
#include "Gizmo.h"

Servo DriveL, DriveR, Arm, Dispenser, ClawL, ClawR, Manny;
Gizmo gizmo;

void setup() {
  gizmo.begin();
  Serial.begin(9600);

  pinMode(GIZMO_MOTOR_1, OUTPUT);
  pinMode(GIZMO_MOTOR_2, OUTPUT);
  pinMode(GIZMO_MOTOR_3, OUTPUT);

  pinMode(GIZMO_SERVO_1, OUTPUT);
  pinMode(GIZMO_SERVO_2, OUTPUT);
  pinMode(GIZMO_SERVO_3, OUTPUT);
  pinMode(21, OUTPUT);

  DriveL.attach(GIZMO_MOTOR_1);
  Arm.attach(GIZMO_MOTOR_2);
  DriveR.attach(GIZMO_MOTOR_3);

  Dispenser.attach(21, 1000, 2100);
  ClawL.attach(GIZMO_SERVO_1);
  ClawR.attach(GIZMO_SERVO_2);
  Manny.attach(GIZMO_SERVO_3, 700, 2300);

  pinMode(LED_BUILTIN, OUTPUT);
}

int targetClawL = 90;
int targetClawR = 90;          // Servo position (0 or 90 degrees)
int targetDispenser = 0;
int targetManny = 0;
// Variables to store previous button states
bool lastDispensingState = false;
bool lastSeatBeltState = false;

void loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  gizmo.refresh();

  int targetL, targetR;
  targetL = map(gizmo.getAxis(GIZMO_AXIS_LY), 0, 255, 0, 180);
  targetR = map(gizmo.getAxis(GIZMO_AXIS_RY), 0, 255, 0, 180);

  bool targetArmUp, targetArmDown;
  targetArmDown = gizmo.getButton(GIZMO_BUTTON_LT);
  targetArmUp = gizmo.getButton(GIZMO_BUTTON_RT);
  int targetArm = targetArmDown ? 180 : targetArmUp ? 0 : 90;

  bool leftBump = gizmo.getButton(GIZMO_BUTTON_LSHOULDER);
  bool rightBump = gizmo.getButton(GIZMO_BUTTON_RSHOULDER);

  if(leftBump){
    targetClawL = 90;
    targetClawR = 90;
    delay(20);
  } else if(rightBump){
    targetClawL = 0;
    targetClawR = 180;
    delay(20);
  }

  // Check if dispensing button has been pressed (on rising edge)
  bool dispensing = gizmo.getButton(GIZMO_BUTTON_B);
  if (dispensing && !lastDispensingState) {
    targetDispenser = targetDispenser == 0 ? 180 : 0;  // Toggle dispenser
    delay(50);
  }
  lastDispensingState = dispensing;  // Update last state

  if(targetDispenser == 180){
    Dispenser.writeMicroseconds(2100);
  } else {
    Dispenser.writeMicroseconds(1000);
  }

  // Check if seatBelt button has been pressed (on rising edge)
  bool seatBelt = gizmo.getButton(GIZMO_BUTTON_X);
  if (seatBelt && !lastSeatBeltState) {
    targetManny = targetManny == 0 ? 180 : 0;  // Toggle Manny
    delay(50);
  }
  lastSeatBeltState = seatBelt;  // Update last state

  if(targetManny == 180){
    Manny.writeMicroseconds(2300);
  } else {
    Manny.writeMicroseconds(1500);
  }

  DriveR.write(targetL);
  DriveL.write(targetR);
  Arm.write(targetArm);
  ClawL.write(targetClawL);
  ClawR.write(targetClawR);
  delay(20);
}
