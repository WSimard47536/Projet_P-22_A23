#include "ROBUSMovement.hpp"


//ErrorSum values will be recorded through
//multiple PIDs to adjust through time
float errorSumStraight = 0.0f;
float errorSumTurn = 0.0f;

//These parameters are reused and reset
// every time a new movement is started
float currentPulseRight = 0.0f;
float currentPulseLeft  = 0.0f;
float rightPulse   = 0.0f;
float leftPulse    = 0.0f;
unsigned long previousInterval_ms = 0;
float previousValue = 0.0f;



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
 * affecting the PID (when different
 * movements)
 * 
 * @return void 
 */
void ROBUSMovement_resetParameters()
{
  errorSumStraight = 0.0f;
  errorSumTurn = 0.0f;
}

/**
 * @brief Resets the movement variables
 * affecting the PID (every movement).
 * Is called in every movement function.
 * 
 * Resets the encoders
 * Sets the current pulses,
 * pulses, previous intervals
 * and previous variables to 0.
 * 
 * @return void 
 */
void ROBUSMovement_initMovement()
{
  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);
  currentPulseRight = 0.0f;
  currentPulseLeft  = 0.0f;
  rightPulse   = 0.0f;
  leftPulse    = 0.0f;
  previousInterval_ms = 0;
  previousValue = 0.0f;
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
/*float ROBUSMovement_arc_math(int color)
{
  float arc_R = 0.0f;
  float arc_L = 0.0f;
  float colorRadius = 0.0f;
  if (color == 1) {//GREEN
    colorRadius = 45.72f;
  } 
  else if (color == 3){ //YELLOW
    colorRadius = 76.20f;
  }

  arc_R = colorRadius-(DISTANCE_BT_WHEEL/2);
  arc_L = colorRadius+(DISTANCE_BT_WHEEL/2);

  return arc_R, arc_L;
}
*/
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
/*float ROBUSMovement_arcPulse_math(float arc_R, float arc_L)
{
  float pulse_R = (arc_R / CIRCUMFERENCE_WHEEL) * 3200.0f;
  float pulse_L = (arc_L / CIRCUMFERENCE_WHEEL) * 3200.0f;
  return pulse_R, pulse_L;
}
*/

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
  

  float wantedPulse = (ROBUSMovement_moveStraight_math(distance_cm));
  //float wantedPulse = 3200;
  Serial.println(wantedPulse);

  speed_pct = direction*speed_pct;
  float newSpeed = speed_pct;

  //ROBUSMovement_initMovement();

  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);
  currentPulseRight = 0.0f;
  currentPulseLeft  = 0.0f;
  rightPulse   = 0.0f;
  leftPulse    = 0.0f;
  previousInterval_ms = 0;
  previousValue = 0.0f;
  //int previousEncoderInterval_ms = 0;

  //float pulsePIDLeft = 0.0f;
  //float pulsePIDRight = 0.0f;

  MOTOR_SetSpeed(LEFT_MOTOR, speed_pct);
  MOTOR_SetSpeed(RIGHT_MOTOR, speed_pct);  

  unsigned long currentInterval_ms  = millis();
  while (currentPulseRight <= wantedPulse)
  {
    
    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){
      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft += abs(leftPulse);

      newSpeed = PID(speed_pct, KP, KI, KD, abs(leftPulse), abs(rightPulse), &errorSumStraight, &previousValue);

      if((newSpeed < 0.4f) && (newSpeed > -0.4f)) MOTOR_SetSpeed(LEFT_MOTOR, newSpeed);

      //pulsePIDRight = 0.0f;
      //pulsePIDLeft = 0.0f;

      previousInterval_ms = currentInterval_ms;
      
    }
  
    

    currentInterval_ms  = millis();
  }
  ROBUSMovement_stop();
  
  Serial.print("RIGHT :");
  Serial.println(currentPulseRight);
  Serial.print("LEFT :");
  Serial.println(currentPulseLeft);
  Serial.print("error sum :");
  Serial.println(errorSumStraight);
  //Serial.print("derivative :");
  //Serial.println((pulsePIDLeft-(previousValue)));
  
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
  float wantedPulse = ROBUSMovement_turnOnSelf_math(degrees);
  Serial.println(wantedPulse);

  float speedRight = -1.0f*direction*speed_pct;
  float newSpeedLeft  = direction*speed_pct;

  //ROBUSMovement_initMovement();
  ENCODER_Reset(LEFT_ENCODER);
  ENCODER_Reset(RIGHT_ENCODER);
  currentPulseRight = 0.0f;
  currentPulseLeft  = 0.0f;
  rightPulse   = 0.0f;
  leftPulse    = 0.0f;
  previousInterval_ms = 0;
  previousValue = 0.0f;

  MOTOR_SetSpeed(LEFT_MOTOR, newSpeedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  unsigned long currentInterval_ms  = millis();
  while (abs(currentPulseRight) <= wantedPulse)
  {

    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){

      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft += abs(leftPulse);
      
      newSpeedLeft = PID(speed_pct, KP, KI, KD, abs(leftPulse), abs(rightPulse), &errorSumTurn, &previousValue);

      if((newSpeedLeft < 0.6f) && (newSpeedLeft > -0.6f)) MOTOR_SetSpeed(LEFT_MOTOR, newSpeedLeft);

      previousInterval_ms = currentInterval_ms;
    }

    currentInterval_ms  = millis();
  }
  ROBUSMovement_stop();
  
  Serial.print("RIGHT :");
  Serial.println(currentPulseRight);
  Serial.print("LEFT :");
  Serial.println(currentPulseLeft);
  Serial.print("error sum :");
  Serial.println(errorSumTurn);
  
}

///////////////////////

double SpeedLeftTrigo  = 0.0;
double SpeedRightTrigo = 0.0;

int speedStatus = STATUS_STOPPED;

double wantedPulseDiff = 0;

double currentSpeed = 0;



void ROBUSMovement_trigoMath(double angle, int direction)
{
  angle = (direction*angle+45.0) * PI / 180.0;
  SpeedLeftTrigo  = sin(angle);
  SpeedRightTrigo = cos(angle);
}

void ROBUSMovement_acceleration(){
  if      ((currentSpeed <  MAXSPEED)  && (speedStatus == STATUS_ACCELERATING)) currentSpeed+=0.01;
  else if ((currentSpeed >= MAXSPEED)  && (speedStatus == STATUS_ACCELERATING)) speedStatus = STATUS_MAXSPEED;
  else if ((currentSpeed >  STOPSPEED) && (speedStatus == STATUS_DECELERATING)) currentSpeed-=0.03;
  else if ((currentSpeed <= STOPSPEED) && (speedStatus == STATUS_DECELERATING)) {
    currentSpeed = 0;
    speedStatus = STATUS_STOPPED;
  }
  else if ((currentSpeed >  STOPSPEED) && (speedStatus == STATUS_EMERGENCYSTOP)) currentSpeed-=0.08;
  else if ((currentSpeed <= STOPSPEED) && (speedStatus == STATUS_EMERGENCYSTOP)) {
    currentSpeed = 0;
    speedStatus = STATUS_STOPPED;
  }
}

void ROBUSMovement_arcPulse(int arcangle){
  wantedPulseDiff = arcangle*ARC_PULSE_DIFFERENCE/90;
}

void ROBUSMovement_arcMove(double speed_pct, int color, int arcangle, int direction){
  if (arcangle == 90) wantedPulseDiff = ARC_PULSE_DIFFERENCE;
  else ROBUSMovement_arcPulse(arcangle);

  double theta = 0;
  if      (color == COLOR_GREEN)  theta = THETA_GREEN;
  else if (color == COLOR_YELLOW) theta = THETA_YELLOW;
  else if (color == COLOR_BLUE)   theta = THETA_BLUE;

  ROBUSMovement_trigoMath(theta, direction);

  double speedLeft  = speed_pct*SpeedLeftTrigo;
  double speedRight = speed_pct*SpeedRightTrigo;
  float ratio = SpeedLeftTrigo/SpeedRightTrigo;

  double currentPulseLeft  = 0;
  double currentPulseRight = 0;

  MOTOR_SetSpeed(LEFT_MOTOR,  speedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  previousInterval_ms = 0;
  unsigned long currentInterval_ms = millis();

  while(abs(currentPulseLeft-currentPulseRight)<wantedPulseDiff){

    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){

      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft  += abs(leftPulse);

      speedLeft = SpeedLeftTrigo*PID(speed_pct, KP, KI, 0, (abs(leftPulse)), (ratio*abs(rightPulse)), &errorSumTurn, 0);

      if((speedLeft < 0.8f) && (speedLeft > -0.8f)) MOTOR_SetSpeed(LEFT_MOTOR, speedLeft);

      previousInterval_ms = currentInterval_ms;
    }

    currentInterval_ms  = millis();
  }
  ROBUSMovement_stop();

}

void ROBUSMovement_EmergencyStop(){
  speedStatus = STATUS_EMERGENCYSTOP;
  int currentInterval_ms = millis();
  while(speedStatus != STATUS_STOPPED){
    
    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){
      ROBUSMovement_acceleration();
      MOTOR_SetSpeed(RIGHT_MOTOR, SpeedRightTrigo*currentSpeed);
      MOTOR_SetSpeed(LEFT_MOTOR, SpeedLeftTrigo*currentSpeed);
      previousInterval_ms = currentInterval_ms;
    }

    currentInterval_ms = millis();
  }
}

void ROBUSMovement_arcMoveTEST(int color, int arcangle, int direction){
  speedStatus = STATUS_ACCELERATING;

  if (arcangle == 90) wantedPulseDiff = ARC_PULSE_DIFFERENCE;
  else ROBUSMovement_arcPulse(arcangle);

  double theta = 0;
  if      (color == COLOR_GREEN)  theta = THETA_GREEN;
  else if (color == COLOR_YELLOW) theta = THETA_YELLOW;
  else if (color == COLOR_BLUE)   theta = THETA_BLUE;

  ROBUSMovement_trigoMath(theta, direction);

  double speedLeft  = currentSpeed*SpeedLeftTrigo;
  double speedRight = currentSpeed*SpeedRightTrigo;
  float ratio = SpeedLeftTrigo/SpeedRightTrigo;

  double currentPulseLeft  = 0;
  double currentPulseRight = 0;

  MOTOR_SetSpeed(LEFT_MOTOR,  speedLeft);
  MOTOR_SetSpeed(RIGHT_MOTOR, speedRight);  

  previousInterval_ms = 0;

  unsigned long currentInterval_ms = millis();
  
  while(abs(currentPulseLeft-currentPulseRight)<wantedPulseDiff){
    
    if((currentInterval_ms-previousInterval_ms)>PID_INTERVAL_MS){

      ROBUSMovement_acceleration();

      rightPulse = (float)ENCODER_ReadReset(RIGHT_ENCODER);
      leftPulse  = (float)ENCODER_ReadReset(LEFT_ENCODER);
      currentPulseRight += abs(rightPulse);
      currentPulseLeft  += abs(leftPulse);

      speedLeft = SpeedLeftTrigo*PID(currentSpeed, KP, KI, 0, (abs(leftPulse)), (ratio*abs(rightPulse)), &errorSumTurn, 0);

      if((speedLeft < 0.8f) && (speedLeft > -0.8f)) MOTOR_SetSpeed(LEFT_MOTOR, speedLeft);

      MOTOR_SetSpeed(RIGHT_MOTOR, SpeedRightTrigo*currentSpeed);
      
      previousInterval_ms = currentInterval_ms;

    }

    currentInterval_ms  = millis();
  }
  ROBUSMovement_EmergencyStop();

}



