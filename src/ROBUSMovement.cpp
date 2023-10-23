#include "ROBUSMovement.hpp"

float errorSumStraight = 0.0f;

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

float PID(float Ubias, float Kp, float Ki, float Kd, float setPoint, float processVariable, float* errorSum, float* previousProcessVariable)
{
    //float interval_s = 0.025f;

    float error = setPoint-processVariable;
    float derivativeError = processVariable-(*previousProcessVariable);
    *errorSum += error;

    float PID = Ubias + Kp*error + Ki*(*errorSum); //+ Kd*(derivativeError)/interval_s;

    *previousProcessVariable = processVariable;

    return PID;
}

void ROBUSMovement_moveStraight(float direction, float speed_pct, float distance_cm)
{
  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);

  float wantedPulse = ROBUSMovement_moveStraight_math(distance_cm);
  Serial.println(wantedPulse);

  /**
   * @brief Keeps track of how close we are to reaching the wanted
   * distance. This value will range from 0 to 1.
   */
  //float distanceRatio = 0;
  speed_pct = direction*speed_pct;
  float newSpeed = speed_pct;

  float currentPulseRight = 0.0f;
  float currentPulseLeft  = 0.0f;
  float rightPulse   = 0.0f;
  float leftPulse    = 0.0f;
  
  unsigned long PIDInterval_ms = 25;
  unsigned long previousInterval_ms = 0;

  float previousProcessVariable = 0.0f;

  MOTOR_SetSpeed(LEFT_MOTOR, speed_pct);
  MOTOR_SetSpeed(RIGHT_MOTOR, speed_pct);  

  unsigned long currentInterval_ms  = millis();
  while (currentPulseRight <= wantedPulse)
  {

    if((currentInterval_ms-previousInterval_ms)>PIDInterval_ms){
      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += rightPulse;
      currentPulseLeft += leftPulse;

      newSpeed = PID(speed_pct, KP, KI, KD, rightPulse, leftPulse, &errorSumStraight, &previousProcessVariable);

      if((newSpeed < 0.4f) && (newSpeed > -0.4f)) MOTOR_SetSpeed(LEFT_MOTOR, newSpeed);

      previousInterval_ms = currentInterval_ms;
    }
    currentInterval_ms  = millis();
  }
  ROBUSMovement_stop();
  /*
  Serial.print("RIGHT :");
  Serial.println(currentPulse);
  Serial.print("LEFT :");
  Serial.println(currentPulseLeft);
  Serial.print("error sum :");
  Serial.println(errorSum);
  */
}
