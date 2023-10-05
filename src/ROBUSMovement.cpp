#include "ROBUSMovement.hpp"
#define constanteRatio 100


int totalPulsesLeft = 0;
int totalPulsesRight = 0;

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

// direction : direction which to go (LEFT or RIGHT) (-1 or 1)
// speed_pct : speed as a percentage, main speed divided by 2
// turn_degrees : turn in degrees
void ROBUSMovement_turnOnSelf(float direction, float speed_pct, int turn_degrees)
{
  Serial.println("Début tourner");
  
  //à modifier selon tests
  float Kc = 0.0007;
  //float Ti = 1000;
  //float Kd = 1.009;
  float Ti = 900;
  float Kd = 0.97;

  float degrees = turn_degrees * Kd;
  float distance_between_wheels = 18.6;
  float wheel_size = 7.62;

  int wanted_movement = ROBUSMovement_turnOnSelf_math(distance_between_wheels, wheel_size, degrees);

  float temps_debut = millis(); 
  int cycle = 1;
  float erreur_integrale = 0;

  MOTOR_SetSpeed(RIGHT_MOTOR, (speed_pct));
  MOTOR_SetSpeed(LEFT_MOTOR, -(speed_pct));

  int tourne = 1;

  Serial.print("wanted_movement : ");
  Serial.println(wanted_movement);
  Serial.print("temps_debut: ");
  Serial.println(temps_debut);


  Serial.println("Début while");

  //Timing
  float temps_derniere_intervalle = 0;
  float intervalle = 100;
  
  //Reset
  ENCODER_ReadReset(1);
  ENCODER_ReadReset(0);
  erreur_integrale = 0;

  while(tourne == 1){
    

    uint32_t right = ENCODER_Read(1);
    uint32_t left = abs(ENCODER_Read(0));
    
    float temps_actuel = millis();
    if ((temps_actuel - temps_derniere_intervalle) > intervalle){
      float nouvelle_vitesse = direction * PID(Kc, Ti, right, left, cycle, temps_debut, temps_actuel, speed_pct, &erreur_integrale);
      if (!(nouvelle_vitesse < -0.4) && !(nouvelle_vitesse > 0.4)){
        MOTOR_SetSpeed(LEFT_MOTOR, nouvelle_vitesse);
      }
      else {
        Serial.println("Error : too fast >:(");
      }
      temps_derniere_intervalle = 0;

      Serial.print("nouvelle vitesse: ");
      Serial.println(nouvelle_vitesse);
    } 

    if (right >= wanted_movement){
      ROBUSMovement_stop();
      tourne = 0;
      Serial.println("Fin while");
      //if (wanted_movement > right){

      //}
    }
  }
}

float ROBUSMovement_turnOnSelf_math(float distance, float wheel, int degrees)
{
  uint32_t arc = distance * degrees * 3200;
  arc = arc / (360*wheel);
  Serial.print("arc: ");
  Serial.println(arc);
  return arc;
}

float PID(float Kc, float Ti, float set_point, float process_variable, int nbr_cycle, float start_time, float current_time, float Ubias, float* erreur_integrale)
{
  
  float Ki = Kc/Ti;

  float temps_tourner = current_time - start_time;

  float delta_T = (temps_tourner/nbr_cycle)/ 1000; // temps/cycle = delta_T en ms ; /1000 pour secondes

  int32_t erreur = set_point-process_variable;
  *erreur_integrale += (erreur * delta_T);

  float speedLeft = Ubias + Kc*erreur + Ki*(*erreur_integrale);

  Serial.print("right : ");
  Serial.println(set_point);
  Serial.print("left: ");
  Serial.println(process_variable);
  Serial.print("erreur: ");
  Serial.println(erreur);
  Serial.print("erreur integrale: ");
  Serial.println(*erreur_integrale);
  Serial.print("delta T: ");
  Serial.println(delta_T);

  return speedLeft;

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