#pragma once

#include <LibRobus.h>

#define FOWARD 1.0f
#define BACKWARD -1.0f
#define LEFT_TURN 1.0f
#define RIGHT_TURN -1.0f

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

void ROBUSMovement_moveStraight(float direction, float speed_pct, int distance_cm);
void ROBUSMovement_turn(float direction, float speed_pct, int turnRadius_degreesPerWheelCycle, int turnDistance_degrees);
void ROBUSMovement_turnOnSelf(float direction, float speed_pct, int turnDistance_degrees);
void ROBUSMovement_stop();