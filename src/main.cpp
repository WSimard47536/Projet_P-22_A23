#include "ROBUSMovement.hpp"
#include "ROBUSSensors.hpp"

#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"

#include "integrationTesting/ROBUSMovement_test.hpp"

void setup()
{
  BoardInit();
}

void loop()
{
  if (ROBUS_IsBumper(REAR_BUMPER))
  {
   
    ROBUSMovement_moveStraight(FOWARD, 0.25, 0.18);
    
    ROBUSMovement_turn(LEFT_TURN, 0.25, 19, 90);
   
    ROBUSMovement_turn(RIGHT_TURN, 0.25, 19, 90);
    
    ROBUSMovement_moveStraight(BACKWARD, 0.25, 0.18);
    
    ROBUSMovement_turn(RIGHT_TURN, 0.25, 19, 360);
    ROBUSMovement_turn(LEFT_TURN, 0.25, 19, 360);
   
    ROBUSMovement_moveStraight(FOWARD, 0.25, 0.18);

    
  // ROBUSMovement_turn(LEFT_TURN, 0.25, 19, 90);
   //delay (2500);
   //ROBUSMovement_turn(LEFT_TURN, 0.35, 19, 90);
   delay(1500);
   //ROBUSMovement_turn(LEFT_TURN, 0.19, 19, 90);
   delay (2500);
   // ROBUSMovement_turn(RIGHT_TURN, 0.25, 19, 360);
    delay(3000);
    //ROBUSMovement_turn(RIGHT_TURN, 0.25, 19, 90);



    #ifdef ISTEST
      test_ROBUSMovement_moveStraight();
    #endif
  }
}