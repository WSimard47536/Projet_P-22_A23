#include "ROBUSMovement.hpp"
#include "math.h"
#define CONSTANTE_RATIO 1000

void ROBUSMovement_stop()
{
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 0);
}

// direction : direction which to go (FOWARD or BACKWARD)
// speed_pct : speed as a percentage
// distance_cm : distance in centimeters
void ROBUSMovement_moveStraight(float direction, float speed_pct, float distance_cm)
{
  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);

  float rotations= distance_cm / CIRCUMFERENCE;

  /**
   * @brief Keeps track of how close we are to reaching the wanted
   * distance. This value will range from 0 to 1.
   */
  float distanceRatio = 0;

  float currentRotations = 0;
  float wantedRotations = rotations*FULL_ROTATIONS_PULSES;

  MOTOR_SetSpeed(LEFT_MOTOR, speed_pct / 100);
  MOTOR_SetSpeed(RIGHT_MOTOR, speed_pct / 100);

  while (currentRotations <= wantedRotations)
  {
    currentRotations = (float)ENCODER_Read(LEFT_ENCODER);
    distanceRatio = currentRotations / wantedRotations;

    ROBUSMovement_adjustDirection(speed_pct, 50, distanceRatio, wantedRotations);
  }

  ROBUSMovement_stop();
}

// direction : direction which to go (LEFT or RIGHT)
// speed_pct : speed as a percentage
// turnRadius_degrees : turn wideness in degrees per wheel turn
// turn_degrees : turn in degrees
void ROBUSMovement_turn(float direction, float speed_pct, int turnRadius_degreesPerWheelCycle, int turn_degrees) // à revoir
{

  ENCODER_Reset(RIGHT_MOTOR);
  ENCODER_Reset(LEFT_MOTOR);
  //distance circulaire (arc)
  float large_rotation = (LARGE_CIRCUMFERENCE_ROBOT*turn_degrees)/360;
  float small_rotation = (SMALL_CIRCUMFERENCE_ROBOT*turn_degrees)/360;
  
  // nombre de pulse necesaire pour faire distance circulaire (arc) 
  float large_turn_pulse = (large_rotation*FULL_ROTATIONS_PULSES/CIRCUMFERENCE_WHEEL);  
  //float small_turn_pulse = (small_rotation*ROTATION_PULSE/CIRCUMFERENCE_WHEEL); 
  // vitesse des moteurs fct arc
  float slow_speed = (speed_pct*small_rotation)/large_rotation;

  // tournant droite
  if (direction == RIGHT_TURN){
    //rajouter de contrainte ?
    while(ENCODER_Read(LEFT_MOTOR) <= large_turn_pulse*MAGIC_RIGHT){
      MOTOR_SetSpeed(RIGHT_MOTOR, slow_speed);
      MOTOR_SetSpeed(LEFT_MOTOR, speed_pct);
      }
  }
  // tournant gauche
  if (direction == LEFT_TURN){
    while(ENCODER_Read(RIGHT_MOTOR) <= large_turn_pulse*MAGIC_lEFT){
      MOTOR_SetSpeed(LEFT_MOTOR, slow_speed);
      MOTOR_SetSpeed(RIGHT_MOTOR, speed_pct);
      }
  }

    ROBUSMovement_stop();

}



// direction : direction which to go (LEFT or RIGHT) (-1 or 1)
// speed_pct : speed as a percentage, main speed divided by 2
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


/**
 * @brief This fonction adjust the power from an under performing motor by reducing
 * the output of the stronger one
 * 
 * @param speed_pct  Speed of the motors up to 100
 * @param delay_ms  Delay before evaluating the If/ Else if
 */
void ROBUSMovement_adjustDirection(float speed_pct, int delay_ms, float distanceRatio, float totalDistance)
{
  static int maxOffset = 0;
  int leftEncoderCount= ENCODER_Read(LEFT_ENCODER);
  int rightEncoderCount= ENCODER_Read(RIGHT_ENCODER);

  float speedRatio = speed_pct/100;
  float speedFactor = ROBUS_GetSpeedFactorFromCurrentPosition(distanceRatio, totalDistance, speedRatio);

  float offset = leftEncoderCount - rightEncoderCount;
  float offsetRatio = offset/CONSTANTE_RATIO;
  //offsetRatio= 1-offsetRatio;


 /* if (abs(offset) > maxOffset)
  {
    maxOffset = abs(offset);
    Serial.println(maxOffset);
  }*/



  Serial.println(offsetRatio);

  MOTOR_SetSpeed(RIGHT_MOTOR, offsetRatio+speedFactor);
  MOTOR_SetSpeed(LEFT_MOTOR, -offsetRatio+speedFactor);
  /*
  if (abs(leftEncoderCount) > abs(rightEncoderCount))
  {
    MOTOR_SetSpeed(LEFT_MOTOR, speedFactor*0.197);
  }
  else if (abs(leftEncoderCount) < abs(rightEncoderCount))
  {
    MOTOR_SetSpeed(LEFT_MOTOR, speedFactor*0.2015);
  }
  */
 
}