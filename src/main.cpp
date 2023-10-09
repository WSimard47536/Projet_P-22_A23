#include "ROBUSMovement.hpp"
#include "ROBUSSensors.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"
#include "MazeSolver.hpp"

#include "integrationTesting/ROBUSMovement_test.hpp"

int vitesse = 30; //0 à 100, % de vitesse

void setup()
{
  BoardInit();
  InitializeProximitySensors();
  MazeSolver_init();
}

void loop()
{
  Serial.println("Beggining...");
  delay(2000);

  while (!MazeSolver_hasCompletedMaze())
  {
    if (GetWall())
    {
      MazeSolver_setObstacle();
    }
    MazeSolver_setNextMoves();
    MazeSolver_executeNextMoves();
  }
  
  for (;;)
  {
    
  }

  /*ROBUSMovement_moveStraight(FORWARD, vitesse, 50);
  delay(500);
  ROBUSMovement_turnOnSelf(1, 0.15, 90); 
  ROBUSMovement_moveStraight(FORWARD, vitesse, 50);
  delay(500);
  ROBUSMovement_turnOnSelf(-1, (0.15), 90);
  //ROBUSMovement_turnOnSelf(1, 0.10, 1080);
  delay(2000);*/



}