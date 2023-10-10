#include "ROBUSMovement.hpp"
#include "ROBUSSensors.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"
#include "MazeSolver.hpp"

#include "integrationTesting/ROBUSMovement_test.hpp"

void setup()
{
  BoardInit();
  InitializeProximitySensors();
}

void loop()
{
  //if (ROBUS_IsBumper(REAR_BUMPER))
  //{
  //  #ifdef ISTEST
  //    test_ROBUSMovement_moveStraight();
  //  #endif
  //}

  ROBUSMovement_moveStraight(FORWARD, vitesse, 50);
  delay(500);
  ROBUSMovement_turnOnSelf(1, 0.15, 90); 
  ROBUSMovement_moveStraight(FORWARD, vitesse, 50);
  delay(500);
  ROBUSMovement_turnOnSelf(-1, (0.15), 90);
  //ROBUSMovement_turnOnSelf(1, 0.10, 1080);
  delay(2000);



}