#include "ROBUSMovement.hpp"

void ROBUSMovement_stop()
{
  MOTOR_SetSpeed(LEFT_MOTOR, 0);
  MOTOR_SetSpeed(RIGHT_MOTOR, 0);
}

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


