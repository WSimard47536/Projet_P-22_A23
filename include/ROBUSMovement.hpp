#pragma once
#include <LibRobus.h>

#define CIRCUMFERENCE_WHEEL (3.1416*DIAMETER_WHEEL)
#define DISTANCE_BT_WHEEL 19.6f // rayon entre les deux roues en cm 
#define DIAMETER_WHEEL 7.6f // diametre de la roue (cm)

// ROBUS CONSTANTS
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define LEFT_ENCODER 0
#define RIGHT_ENCODER 1

// MOVEMENT CONSTANTS
#define FORWARD 1.0f
#define BACKWARD -1.0f
#define RIGHT_TURN 1.0f
#define LEFT_TURN -1.0f

// PID CONSTANTS
#define PID_INTERVAL_MS 25.0l

#define KU 0.03f
#define TU 50.0f

#define TI (TU)
#define TD (TU/8.0f)
#define KP (KU/2.5f)
#define KI (KU/TI)
#define KD 0 //(KU*TD) to be added in later after more testing.



//FUNCTIONS

void ROBUSMovement_stop();

void ROBUSMovement_resetParameters();

void ROBUSMovement_initMovement();

float ROBUSMovement_turnOnSelf_math(int degrees);

float ROBUSMovement_moveStraight_math(int distance_cm);

float PID(float baseValue, float proportional, float integral, float derivative, float currentValue, float wantedValue, float* errorSum, float* previousValue);

void ROBUSMovement_moveStraight_cm(float direction, float speed_pct, float distance_cm);

void ROBUSMovement_turnOnSelf_deg(float direction, float speed_pct, float degrees);