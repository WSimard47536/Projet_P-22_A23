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
  Serial.println("Beggining...");
  delay(5000);
  MazeSolver_init();
  while (!MazeSolver_hasCompletedMaze())
  {
    MazeSolver_setNextMoves();
    MazeSolver_executeNextMoves();
  }
  //if (ROBUS_IsBumper(REAR_BUMPER))
  //{
  //  #ifdef ISTEST
  //    test_ROBUSMovement_moveStraight();
  //  #endif
  //}

  
  //ROBUSMovement_turnOnSelf(-1, 0.10, 90);
  //ROBUSMovement_turnOnSelf(1, 0.10, 1080);
  //delay(2000);
  
}