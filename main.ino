#include <Servo.h>
#include "Gizmo.h"

Servo DriveL, DriveR, Arm, ClawL, ClawR, Dispenser;
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

  DriveL.attach(GIZMO_MOTOR_1);
  Arm.attach(GIZMO_MOTOR_2);
  DriveR.attach(GIZMO_MOTOR_3);
  ClawL.attach(GIZMO_SERVO_1);
  ClawR.attach(GIZMO_SERVO_2);
  Dispenser.attach(GIZMO_SERVO_3);

  pinMode(LED_BUILTIN, OUTPUT);
}

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

  // bool targetClawL, targetClawR;
  // targetClawL = gizmo.getButton(GIZMO_BUTTON_LSHOULDER);
  // targetClawR = gizmo.getButton(GIZMO_BUTTON_RSHOULDER);
  // int targetClaw = targetArmDown ? 0 : targetArmUp ? 90 : 180;

  // bool targetDispenser;
  // targetDispenser = gizmo.getButton(GIZMO_BUTTON_B);
  // int targetDispense = targetDispenser ? 180 : 90;

  DriveL.write(targetL);
  DriveR.write(targetR);
  Arm.write(targetArm);
  // Dispenser.write(targetDispense);

  delay(20);
}