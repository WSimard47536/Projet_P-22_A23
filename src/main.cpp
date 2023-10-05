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
     // test_ROBUSMovement_moveStraight();
    #endif
    ROBUSMovement_moveStraight(FORWARD, 75, 10.00f);
    delay(2000);
    ROBUSMovement_moveStraight(FORWARD, 75, 20.00f);
    delay(2000);
    ROBUSMovement_moveStraight(FORWARD, 75, 30.00f);
    delay(2000);
    ROBUSMovement_moveStraight(FORWARD, 75, 40.00f);
    delay(2000);
    ROBUSMovement_moveStraight(FORWARD, 75, 50.00f);
    delay(2000);
    ROBUSMovement_moveStraight(FORWARD, 75, 60.00f);
    delay(2000);
    ROBUSMovement_moveStraight(FORWARD, 75, 70.00f);
    delay(2000);
    ROBUSMovement_moveStraight(FORWARD, 75, 80.00f);
  }
}