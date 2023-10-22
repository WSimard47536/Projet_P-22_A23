#pragma once
#include <LibRobus.h>

#define CIRCUMFERENCE_WHEEL (3.1416*DIAMETER_WHEEL)
#define DISTANCE_BT_WHEEL 0.196f // rayon entre les deux roues en metre 
#define DIAMETER_WHEEL 0.076f // diametre de la roue (m)

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define LEFT_ENCODER 0
#define RIGHT_ENCODER 1

#define FORWARD 1.0f
#define BACKWARD -1.0f
#define LEFT_TURN -1.0f
#define RIGHT_TURN 1.0f

#define KU 0.0069427506f
#define TU 200.0f

#define TI (TU/2.0f)
#define TD (TU/8.0f)
#define KP (KU*0.6)
#define KI (KP/TI)
#define KD (KP*TD)


void ROBUSMovement_stop();

float ROBUSMovement_turnOnSelf_math(int degrees);

float ROBUSMovement_moveStraight_math(int distance_cm);

float PID(float Ubias, float Kc, float Ki, float Kd, float setPoint, float processVariable, float* errorSum, float* previousProcessVariable);

void ROBUSMovement_moveStraight(float direction, float speed_pct, float distance_cm);