#include "ROBUSMovement.hpp"
#define constanteRatio 100


int totalPulsesLeft = 0;
int totalPulsesRight = 0;

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

 /* Serial.println("Gauche : ");
  Serial.println(ENCODER_Read(LEFT_ENCODER));
  Serial.println("Droite : ");
  Serial.println(ENCODER_Read(RIGHT_ENCODER));

  totalPulsesLeft += abs(ENCODER_Read(LEFT_ENCODER));
  totalPulsesRight += abs(ENCODER_Read(RIGHT_ENCODER));

  ENCODER_Reset(RIGHT_ENCODER);
  if (abs(totalPulsesLeft - totalPulsesRight) >= 10)
  {
    int test = totalPulsesRight;
    while (test >= totalPulsesLeft)
    {
      test -= abs(ENCODER_ReadReset(RIGHT_ENCODER));
      MOTOR_SetSpeed(RIGHT_ENCODER, -0.1f);

      Serial.println("Droite : ");
      Serial.println(test);
    }
    ROBUSMovement_stop();
  }*/
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

/**
 * @brief This fonction adjust the power from an under performing motor by reducing
 * the output of the stronger one
 * 
 * @param speed_pct  Speed of the motors up to 100
 * @param delay_ms  Delay before evaluating the If/ Else if
 */
void ROBUSMovement_adjustDirection(float speed_pct, int delay_ms, float distanceRatio, float totalDistance)
{
  int leftEncoderCount= ENCODER_Read(LEFT_ENCODER);
  int rightEncoderCount= ENCODER_Read(RIGHT_ENCODER);

  float speedRatio = speed_pct/100;
  float speedFactor = ROBUS_GetSpeedFactorFromCurrentPosition(distanceRatio, totalDistance, speedRatio);

  float offset = leftEncoderCount - rightEncoderCount;
  float offsetRatio = offset/constanteRatio;
  offsetRatio= 1-offsetRatio;
  




  //Serial.println(speedRatio);

  MOTOR_SetSpeed(RIGHT_MOTOR, speedFactor);
  MOTOR_SetSpeed(LEFT_MOTOR, speedFactor);
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