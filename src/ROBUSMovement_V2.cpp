#include "ROBUSMovement_V2.hpp"

void ROBUSMovement_stop()
{
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 0);
}

//arc = nombre de pulse pour atteindre l'angle voulu
float ROBUSMovement_turnOnSelf_math(int degrees)
{
  float arc = DISTANCE_BT_WHEEL * (float)degrees * 3200.0f;
  arc = arc / (360.0f*CIRCUMFERENCE_WHEEL);
  return arc;
}

//arc = nombre de pulse pour atteindre la distance voulue
float ROBUSMovement_moveStraight_math(int distance_cm)
{
  float pulse = ((float)distance_cm / CIRCUMFERENCE_WHEEL) * 3200.0f;
  return pulse;
}

float PID(float Ubias, float Kc, float Ki, float Kd, float setPoint, float processVariable, float* errorSum, float* previousProcessVariable)
{
    float interval_s = 0.05f;

    float error = setPoint-processVariable;
    float derivativeError = processVariable-(*previousProcessVariable);
    *errorSum += error;

    float PID = Ubias + Kc*error + Ki*(*errorSum)*interval_s + Kd*(derivativeError)/interval_s;

    *previousProcessVariable = processVariable;

    return PID;
}


void ROBUSMovement_moveStraight(float direction, float speed_pct, float distance_cm)
{
  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);

  float wantedPulse = ROBUSMovement_moveStraight_math(distance_cm);

  /**
   * @brief Keeps track of how close we are to reaching the wanted
   * distance. This value will range from 0 to 1.
   */
  //float distanceRatio = 0;
  speed_pct = direction*speed_pct;
  float newSpeed = speed_pct;

  float currentPulse = 0;
  float rightPulse   = 0;
  float leftPulse    = 0;
  
  int PIDInterval_ms = 50;
  int previousInterval_ms = 0;

  float errorSum = 0.0f;
  float previousProcessVariable = 0.0f;

  MOTOR_SetSpeed(LEFT_MOTOR, speed_pct);
  MOTOR_SetSpeed(RIGHT_MOTOR, speed_pct);  

  int currentInterval_ms  = millis();
  while (currentPulse <= wantedPulse)
  {
    //currentPulse = (float)ENCODER_Read(RIGHT_ENCODER);

    rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
    leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
    currentPulse = rightPulse;

    if((currentInterval_ms-previousInterval_ms)>PIDInterval_ms){
        newSpeed = PID(speed_pct, KP, KI, KD, rightPulse, leftPulse, &errorSum, &previousProcessVariable);
        MOTOR_SetSpeed(LEFT_MOTOR, newSpeed);

        previousInterval_ms = currentInterval_ms;
    }

    //distanceRatio = currentRotations / wantedRotations;
    //ROBUSMovement_adjustDirection(speed_pct, 50, distanceRatio, wantedRotations);
    currentInterval_ms  = millis();
  }

  ROBUSMovement_stop();
}
