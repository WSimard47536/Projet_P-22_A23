#include "ROBUSMovement.hpp"

float errorSumStraight = 0.0f;
float errorSumTurn = 0.0f;

/**
 * @brief Stops the robot by putting
 * the speed of both motors at 0.
 * 
 * @return void 
 */
void ROBUSMovement_stop()
{
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 0);
}

/**
 * @brief Resets the movement parameters
 * affecting the PWM
 * 
 * @return void 
 */
void ROBUSMovement_resetParameters()
{
  errorSumStraight = 0.0f;
  errorSumTurn = 0.0f;
}



/**
 * @brief Basic math allowing to return the number
 * of pulses needed to reach the desired angle
 * (in centimeters). Based on the formula :
 * 
 * (deg/360) * DISTANCE_BT_WHEEL * (3200/(DIAMETER_WHEEL*pi))
 *  or 
 * (deg*DISTANCE_BT_WHEEL*3200)/(360*DIAMETER_WHEEL)
 * 
 * @param degrees
 * Number of degrees the robot wants to turn. 
 * @return float 
 */
float ROBUSMovement_turnOnSelf_math(int degrees)
{
  float pulse = DISTANCE_BT_WHEEL * (float)degrees * 3200.0f;
  pulse = pulse / (360.0f*DIAMETER_WHEEL);
  return pulse;
}

/**
 * @brief Basic math allowing to return the number
 * of pulses needed to reach the desired distance
 * (in centimeters). Based on the formula :
 * 
 * wanted distance/wanted pulse = circumference_wheel/
 * pulse of 1 rotation
 * 
 * @param distance_cm
 * The total distance the robot wants to cross in
 * centimeters. Using the math function, allows to
 * know the total number of pulses needed to reach
 * the desired distance.
 * @return float 
 */
float ROBUSMovement_moveStraight_math(int distance_cm)
{
  float pulse = ((float)distance_cm / CIRCUMFERENCE_WHEEL) * 3200.0f;
  return pulse;
}

/**
 * @brief Basic PID function that returns an
 * adjusted value over time based on a wanted
 * value. P,I,D numbers are used to tune the
 * responsiveness of the PID and varies
 * depending on its applications.
 * 
 * For example, to tune the difference
 * between 2 motors that should be the same,
 * you would first get the difference between
 * the 2, knowing you want it to be 0, and
 * then call he function as following:
 * speedCorrection = PID(p, i, d, difference, 0);
 * 
 * @param proportional 
 * the P value of the PID. The increase of the
 * number the further it is from wanted value.
 * @param integral 
 * the I value of the PID. In other words, the
 * small corrections done over time if there's
 * oscillaton.
 * @param derivative
 * The D value of the PID. When the value
 * begins to reach the wanted value, this
 * will deaccelerate the PID.
 * @param currentValue 
 * @param wantedValue 
 * @return float 
 */
float PID(float baseValue, float proportional, float integral, float derivative, float currentValue, float wantedValue, float* errorSum, float* previousValue)
{
  float error = wantedValue-currentValue;
  float derivativeError = currentValue-(*previousValue);
  *errorSum += error;

  float PID = baseValue + proportional*error + integral*(*errorSum) + derivative*(derivativeError);

  *previousValue = currentValue;

  return PID;
}

/**
 * @brief Basic movement function that allows the
 * robot to go in a straight line according to a
 * set distance in centimeters.
 * 
 * @param direction 
 * The direction determines whether the robot will
 * go forward or backwards. It is multiplied by
 * the speed to set the motors' speed & direction.
 * @param speed_pct 
 * The speed at which the robot should move. Can
 * be anything from 0 (not moving) to 1 (max speed).
 * @param distance_cm
 * The total distance the robot wants to cross in
 * centimeters. Using the math function, allows to
 * know the total number of pulses needed to reach
 * the desired distance.
 * @return void 
 */
void ROBUSMovement_moveStraight_cm(float direction, float speed_pct, float distance_cm)
{
  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);

  float wantedPulse = ROBUSMovement_moveStraight_math(distance_cm);
  //Serial.println(wantedPulse);

  speed_pct = direction*speed_pct;
  float newSpeed = speed_pct;

  float currentPulseRight = 0.0f;
  float currentPulseLeft  = 0.0f;
  float rightPulse   = 0.0f;
  float leftPulse    = 0.0f;
  
  unsigned long previousInterval_ms = 0;

  float previousProcessVariable = 0.0f;

  MOTOR_SetSpeed(LEFT_MOTOR, speed_pct);
  MOTOR_SetSpeed(RIGHT_MOTOR, speed_pct);  

  unsigned long currentInterval_ms  = millis();
  while (currentPulseRight <= wantedPulse)
  {

    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){
      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += rightPulse;
      currentPulseLeft += leftPulse;

      newSpeed = PID(speed_pct, KP, KI, KD, leftPulse, rightPulse, &errorSumStraight, &previousProcessVariable);

      if((newSpeed < 0.4f) && (newSpeed > -0.4f)) MOTOR_SetSpeed(LEFT_MOTOR, newSpeed);

      previousInterval_ms = currentInterval_ms;
    }
    currentInterval_ms  = millis();
  }
  ROBUSMovement_stop();
  /*
  Serial.print("RIGHT :");
  Serial.println(currentPulseRight);
  Serial.print("LEFT :");
  Serial.println(currentPulseLeft);
  Serial.print("error sum :");
  Serial.println(errorSum);
  */
}

/**
 * @brief Basic movement function that allows the
 * robot to go in a straight line according to a
 * set distance in centimeters.
 * 
 * @param direction 
 * The direction determines whether the robot will
 * go forward or backwards. It is multiplied by
 * the speed to set the motors' speed & direction.
 * @param speed_pct 
 * The speed at which the robot should move. Can
 * be anything from 0 (not moving) to 1 (max speed).
 * @param degrees
 * The total distance the robot wants to cross in
 * centimeters. Using the math function, allows to
 * know the total number of pulses needed to reach
 * the desired distance.
 * @return void 
 */
void ROBUSMovement_turnOnSelf_deg(float direction, float speed_pct, float degrees)
{
  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);

  float wantedPulse = ROBUSMovement_turnOnSelf_math(degrees);
  //Serial.println(wantedPulse);

  float speedRight = -1.0f*direction*speed_pct;
  float speedLeft  = direction*speed_pct;
  float newSpeedLeft = speedLeft;

  float currentPulseRight = 0.0f;
  float currentPulseLeft  = 0.0f;
  float rightPulse   = 0.0f;
  float leftPulse    = 0.0f;
  
  unsigned long previousInterval_ms = 0;

  float previousProcessVariable = 0.0f;

  MOTOR_SetSpeed(LEFT_MOTOR, speedRight);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedLeft);  

  unsigned long currentInterval_ms  = millis();
  while (currentPulseRight <= wantedPulse)
  {
    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){
      rightPulse = abs((float)ENCODER_ReadReset(RIGHT_ENCODER));
      leftPulse  = abs((float)ENCODER_ReadReset(LEFT_ENCODER));
      currentPulseRight += rightPulse;
      currentPulseLeft += leftPulse;

      newSpeedLeft = PID(speed_pct, KP, KI, KD, leftPulse, rightPulse, &errorSumTurn, &previousProcessVariable);

      if((newSpeedLeft < 0.4f) && (newSpeedLeft > -0.4f)) MOTOR_SetSpeed(LEFT_MOTOR, newSpeedLeft);

      previousInterval_ms = currentInterval_ms;
    }
    currentInterval_ms  = millis();
  }
  ROBUSMovement_stop();
  /*
  Serial.print("RIGHT :");
  Serial.println(currentPulseRight);
  Serial.print("LEFT :");
  Serial.println(currentPulseLeft);
  Serial.print("error sum :");
  Serial.println(errorSum);
  */
}


/**
 * @brief Basic movement function that allows the
 * robot to go in a straight line. Stops only when
 * an interrupt of some kind happens.
 * 
 * Implemented interrupt types : 
 *  MASTER - emergency stop signal;
 *  OBSTACLE - stops when obstacle in front;
 *  COLOR - stops when color is seen.
 *  
 *  More can be added, as desired.
 * 
 * @param direction 
 * The direction determines whether the robot will
 * go forward or backwards. It is multiplied by
 * the speed to set the motors' speed & direction.
 * @param speed_pct 
 * The speed at which the robot should move. Can
 * be anything from 0 (not moving) to 1 (max speed).
 * @return void 
 *//*
void ROBUSMovement_moveStraight(float direction, float speed_pct)
{
  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);

  speed_pct = direction*speed_pct;
  float newSpeed = speed_pct;

  float currentPulseRight = 0.0f;
  float currentPulseLeft  = 0.0f;
  float rightPulse   = 0.0f;
  float leftPulse    = 0.0f;
  
  unsigned long previousInterval_ms = 0;

  float previousProcessVariable = 0.0f;

  bool forwardStatus = true;

  MOTOR_SetSpeed(LEFT_MOTOR,  speedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  unsigned long currentInterval_ms  = millis();
  while (forwardStatus)
  {
    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){
      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += rightPulse;
      currentPulseLeft += leftPulse;

      newSpeedLeft = PID(speedLeft, KP, KI, KD, leftPulse, rightPulse, &errorSumStraight, &previousProcessVariable);

      if((speedLeft < 0.4f) && (speedLeft > -0.4f)) MOTOR_SetSpeed(LEFT_MOTOR, newSpeedLeft);

      previousInterval_ms = currentInterval_ms;
    }
    currentInterval_ms  = millis();

    /*if(
      CONDITION 1 || //MASTER ERROR
      CONDITION 2 || //OBSTACLE DETECTED
      CONDITION 3    //COLOR ERROR
    ){
      forwardStatus = false;
    }*/

    /*
    ActionToAccomplish();
    

  }
  ROBUSMovement_stop();
  /*
  Serial.print("RIGHT :");
  Serial.println(currentPulseRight);
  Serial.print("LEFT :");
  Serial.println(currentPulseLeft);
  Serial.print("error sum :");
  Serial.println(errorSum);
  
}*/




