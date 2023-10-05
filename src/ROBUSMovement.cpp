#include "ROBUSMovement.hpp"
#include "math.h"
#define constanteRatio 100


int totalPulsesLeft = 0;
int totalPulsesRight = 0;

void ROBUSMovement_stop()
{
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 0);
}

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

void ROBUSMovement_stop()
{
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 0);
}