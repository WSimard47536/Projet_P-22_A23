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

// direction : direction which to go (LEFT or RIGHT) (-1 or 1)
// speed_pct : speed as a percentage, main speed divided by 2
// turn_degrees : turn in degrees
void ROBUSMovement_turnOnSelf(float direction, float speed_pct, int turnDistance_degrees);


float ROBUSMovement_turnOnSelf_math(float distance, float wheel, int degrees);


float PID(float Kc, float Ti, float set_point, float process_variable, int nbr_cycle, float start_time, float current_time, float Ubias, float* erreur_integrale);


void ROBUSMovement_stop();