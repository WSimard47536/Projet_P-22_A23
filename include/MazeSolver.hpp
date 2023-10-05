#pragma once

#define MAZE_NUMBER_OF_ROWS 10
#define MAZE_NUMBER_OF_COLUMNS 3

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
  int speed_pct;
  int distance_cm;
} Move;

typedef struct 
{
  bool canGoLeft;
  bool canGoRight;
  bool canGoFoward;
  bool canGoBackward;
} MazePosition;

typedef struct
{
  MazePosition positions[MAZE_NUMBER_OF_ROWS][MAZE_NUMBER_OF_COLUMNS];
} Maze;

void MazeSolver_init();
void MazeSolver_setBaseMaze();

void MazeSolver_setObstacle(int row, int column);
Move MazeSolver_getNextMove();

bool MazeSolver_canGoFoward();