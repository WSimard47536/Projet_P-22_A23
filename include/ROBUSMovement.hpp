#pragma once

#include <LibRobus.h>

#define FOWARD 1.0f
#define BACKWARD -1.0f
#define LEFT_TURN 1.0f
#define RIGHT_TURN -1.0f

#define PMV 3200 // 
#define DISTANCE_BT_WHEEL 0.196f // rayon entre les deux roues en metre 
#define DIAMETER_WHEEL 0.076f // diametre de la roue (m)

#define MAGIC_lEFT 0.93
#define MAGIC_RIGHT 0.94

//0.9597

#define CIRCUMFERENCE_ROBOT (3.1416*DISTANCE_BT_WHEEL*2)
#define CIRCUMFERENCE_WHEEL (3.1416*DIAMETER_WHEEL)


#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

void ROBUSMovement_moveStraight(float direction, float speed_pct, int distance_cm);
void ROBUSMovement_turn(float direction, float speed_pct, int turnRadius_degreesPerWheelCycle, int turnDistance_degrees);
void ROBUSMovement_turnOnSelf(float direction, float speed_pct, int turnDistance_degrees);
void ROBUSMovement_stop();