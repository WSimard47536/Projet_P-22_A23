#include "ROBUSMovement.hpp"
#include "ROBUSSensors.hpp"
#include "WhistlesoundDetector.hpp"
#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"
//#include "MazeSolver.hpp"

//#include "integrationTesting/ROBUSMovement_test.hpp"

void setup()
{
  BoardInit();
  //InitializeProximitySensors();
  //MazeSolver_init();
  delay(100);
  
}

void loop()
{

  //ROBUSMovement_moveStraight_cm(FORWARD, 0.3f, 50.0f);
  //ROBUSMovement_turnOnSelf_deg(RIGHT_TURN, 0.2f, 90.0f); //86.4\

  //ROBUSMovement_arcMove(0.4, COLOR_YELLOW, 90, RIGHT_TURN);
  ROBUSMovement_arcMoveTEST(COLOR_GREEN, 90, RIGHT_TURN);
  delay(5000);


  /*waitForWhistle();

  MazeSolver_init();
  while (!MazeSolver_hasCompletedMaze())
  {
    if (GetWall())
    {
      MazeSolver_setObstacle();
    }
    MazeSolver_setNextMoves();
    MazeSolver_executeNextMoves();
  }
  ROBUSMovement_moveStraight(FORWARD,20.0f,50.0f);
  MazeSolver_returnToStart();*/

  /*if (ROBUS_IsBumper(3))
  {
    MazeSolver_init();
    while (!MazeSolver_hasCompletedMaze())
    {
      if (GetWall())
      {
        MazeSolver_setObstacle();
      }
      MazeSolver_setNextMoves();
      MazeSolver_executeNextMoves();
    }
  }*/
  //ROBUSMovement_turnOnSelf(LEFT_TURN, 0.15f, 90);
  //delay(1500);
  //ROBUSMovement_turnOnSelf(RIGHT_TURN, 0.15f, 90);
  //delay(1500);
  //ROBUSMovement_moveStraight(FORWARD, 20, 50);
}