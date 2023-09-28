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
    #ifdef ISTEST
      test_ROBUSMovement_moveStraight();
    #endif
  }
}