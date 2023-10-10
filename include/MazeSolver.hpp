#pragma once

#include "ROBUSDefines.hpp"
#include "ObstacleDetector.hpp"

#define MAZE_NUMBER_OF_ROWS 10
#define MAZE_NUMBER_OF_COLUMNS 3

#define LEFT_COLUMN 0
#define MIDDLE_COLUMN 1
#define RIGHT_COLUMN 2

#define MAZE_MOVE_HISTORY_SIZE 100
#define MAZE_BUFFER_SIZE 5

#define STRAIGHT 0
#define TURN 1

#ifdef ROBOTA
  #define ROBOT_OFFSET 0
#else
    #ifdef ROBOTB
      #define ROBOT_OFFSET 1
    #endif
#endif

typedef struct
{
  int direction;
  bool isTurn;
} Move;

typedef union 
{
  struct
  {
    bool canGoLeft;
    bool canGoFoward;
    bool canGoRight;
    bool canGoBackwards;

    bool hasMovedOn;
  } members;
  
  bool values[5];
} MazePosition;

typedef struct
{
  MazePosition positions[MAZE_NUMBER_OF_ROWS][MAZE_NUMBER_OF_COLUMNS];
} Maze;

void MazeSolver_init();
void MazeSolver_resetMoveHistory();
void MazeSolver_resetMoveBuffer();

void MazeSolver_setObstacle();

void MazeSolver_setNextMoves();
bool MazeSolver_checkSetMove(bool checkHasMovedOn);
void MazeSolver_executeNextMoves();

void MazeSolver_addOrientationMoves(int wantedOrientation);
void MazeSolver_addMoveStraight();
bool MazeSolver_canMoveTo(int direction, bool checkHasMovedOn);
bool MazeSolver_hasMovedOn(int direction);

void MazeSolver_onMoveCompletion(Move move);
bool MazeSolver_hasCompletedMaze();

void MazeSolver_setBaseMaze();
void MazeSolver_setTestMaze();