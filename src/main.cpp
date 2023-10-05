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
   
    ROBUSMovement_moveStraight(FOWARD, 0.25, 15);
    
 


    #ifdef ISTEST
      test_ROBUSMovement_moveStraight();
    #endif
  }
}