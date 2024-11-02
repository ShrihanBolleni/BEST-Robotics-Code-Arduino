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