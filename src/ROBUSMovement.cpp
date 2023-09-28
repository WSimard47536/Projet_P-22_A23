#include "ROBUSMovement.hpp"

// direction : direction which to go (FOWARD or BACKWARD)
// speed_pct : speed as a percentage
// distance_cm : distance in centimeters
void ROBUSMovement_moveStraight(float direction, float speed_pct, int distance_cm)
{
  // à coder
  // indice : la vitesse finale sera égale à (direction * speed_pct / 100)

  // test pour jeudi
  MOTOR_SetSpeed(LEFT_MOTOR, 25);
  MOTOR_SetSpeed(RIGHT_MOTOR, 25);
  delay(2000);
  ROBUSMovement_stop();
}

// direction : direction which to go (LEFT or RIGHT)
// speed_pct : speed as a percentage
// turnRadius_degrees : turn wideness in degrees per wheel turn
// turn_degrees : turn in degrees
void ROBUSMovement_turn(float direction, float speed_pct, int turnRadius_degreesPerWheelCycle, int turn_degrees) // à revoir
{
  // à coder

  // test pour jeudi
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 25);
  delay(2000);
  ROBUSMovement_stop();
}

// direction : direction which to go (LEFT or RIGHT)
// speed_pct : speed as a percentage
// turn_degrees : turn in degrees
void ROBUSMovement_turnOnSelf(float direction, float speed_pct, int turn_degrees)
{
  // à coder

  // test pour jeudi
  MOTOR_SetSpeed(LEFT_MOTOR, 25);
  MOTOR_SetSpeed(RIGHT_MOTOR, -25);
  delay(2000);
  ROBUSMovement_stop();
}

void ROBUSMovement_stop()
{
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 0);
}