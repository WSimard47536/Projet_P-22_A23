#pragma once
#include <LibRobus.h>
#include "ROBUSAcceleration.hpp"

#define FORWARD 1.0f
#define BACKWARD -1.0f
#define LEFT_TURN 1.0f
#define RIGHT_TURN -1.0f

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define LEFT_ENCODER 0
#define RIGHT_ENCODER 1

#define DIAMETER 7.60f
#define CIRCUMFERENCE 23.87f
#define FULL_ROTATIONS_PULSES 3200.00f

void ROBUSMovement_adjustDirection(float speed_pct, int delay_ms, float distanceRatio);
void ROBUSMovement_moveStraight(float direction, float speed_pct, float distance_cm);
void ROBUSMovement_turn(float direction, float speed_pct, int turnRadius_degreesPerWheelCycle, int turnDistance_degrees);
void ROBUSMovement_turnOnSelf(float direction, float speed_pct, int turnDistance_degrees);
void ROBUSMovement_stop();