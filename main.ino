#include <Servo.h>
#include "Gizmo.h"

Servo DriveL, DriveR, Arm;
Gizmo gizmo;

void setup() {
  gizmo.begin();

  pinMode(GIZMO_MOTOR_1, OUTPUT);
  pinMode(GIZMO_MOTOR_2, OUTPUT);
  pinMode(GIZMO_MOTOR_3, OUTPUT);

  DriveL.attach(GIZMO_MOTOR_1);
  Arm.attach(GIZMO_MOTOR_2);
  DriveR.attach(GIZMO_MOTOR_3);

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
  int targetArm = targetArmDown ? 0 : targetArmUp ? 180 : 90;

  DriveL.write(targetL);
  DriveR.write(targetR);
  Arm.write(targetArm);

  delay(20);
}