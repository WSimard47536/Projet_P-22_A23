#include "ROBUSMovement.hpp"
#include "math.h"
#define constanteRatio 100

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
  Serial.println("Début tourner");
  
  ////// ROBOT A ///////
  //////////////////////
  //à modifier selon tests
  //float Kc = 0.0007;
  //float Ti = 900;
  //float Kd = 0.925; //90°
  //////////////////////


  ////// ROBOT B ///////
  //////////////////////
  //à modifier selon tests
  float Kc = 0.0007;
  float Ti = 900;
  float Kd = 0.9280; //90°
  //////////////////////

  float degrees = turn_degrees * Kd;
  float distance_between_wheels = 18.6;
  float wheel_size = 7.62;

  int wanted_movement = ROBUSMovement_turnOnSelf_math(distance_between_wheels, wheel_size, degrees);

  float temps_debut = millis(); 
  int cycle = 1;
  float erreur_integrale = 0;

  MOTOR_SetSpeed(RIGHT_MOTOR, (-1*direction*speed_pct));
  MOTOR_SetSpeed(LEFT_MOTOR, (direction*speed_pct));

  int tourne = 1;

  Serial.print("wanted_movement : ");
  Serial.println(wanted_movement);
  Serial.print("temps_debut: ");
  Serial.println(temps_debut);


  Serial.println("Début while");

  //Timing
  float temps_derniere_intervalle = 0;
  float intervalle = 50;
  
  //Reset
  ENCODER_ReadReset(1);
  ENCODER_ReadReset(0);
  erreur_integrale = 0;

  while(tourne == 1){
    

    uint32_t right = abs(ENCODER_Read(1));
    uint32_t left  = abs(ENCODER_Read(0));
    
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


