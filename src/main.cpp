#include "ROBUSMovement.hpp"
#include "ROBUSSensors.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"

#include "integrationTesting/ROBUSMovement_test.hpp"

void setup()
{
  BoardInit();
  InitializeProximitySensors();
}

void loop()
{
  
  ROBUSMovement_moveStraight(FORWARD, 100, 50.0f);
  for (;;)
  {

  }
  /*delay(2000);
  ROBUSMovement_moveStraight(FORWARD, 100, 20.0f);
  delay(2000);
  ROBUSMovement_moveStraight(FORWARD, 100, 30.0f);
  delay(2000);
  ROBUSMovement_moveStraight(FORWARD, 100, 40.0f);
  delay(2000);
  ROBUSMovement_moveStraight(FORWARD, 100, 50.0f);
  delay(2000);
  ROBUSMovement_moveStraight(FORWARD, 100, 60.0f);
  delay(2000);
  ROBUSMovement_moveStraight(FORWARD, 100, 70.0f);
  delay(2000);
  ROBUSMovement_moveStraight(FORWARD, 100, 80.0f);
  delay(2000);
  ROBUSMovement_moveStraight(FORWARD, 100, 90.0f);
  delay(2000);
  ROBUSMovement_moveStraight(FORWARD, 100, 100.0f);
  delay(2000);
  */
}