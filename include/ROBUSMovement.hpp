#pragma once
#include <LibRobus.h>

#define CIRCUMFERENCE_WHEEL (3.1416*DIAMETER_WHEEL)
#define DISTANCE_BT_WHEEL 19.6f // rayon entre les deux roues en cm 
#define DIAMETER_WHEEL 7.6f // diametre de la roue (cm)

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define LEFT_ENCODER 0
#define RIGHT_ENCODER 1

#define FORWARD 1.0f
#define BACKWARD -1.0f
#define LEFT_TURN -1.0f
#define RIGHT_TURN 1.0f

#define KU 0.03f
#define TU 50.0f

#define TI (TU)
#define TD (TU/8.0f)
#define KP (KU/2.5f)
#define KI (KU/TI)
#define KD (KU*TD)


void ROBUSMovement_stop();

float ROBUSMovement_turnOnSelf_math(int degrees);

float ROBUSMovement_moveStraight_math(int distance_cm);

float PID(float Ubias, float Kc, float Ki, float Kd, float setPoint, float processVariable, float* errorSum, float* previousProcessVariable);

void ROBUSMovement_moveStraight(float direction, float speed_pct, float distance_cm);