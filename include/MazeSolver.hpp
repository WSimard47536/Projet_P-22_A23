#pragma once

#ifdef ROBOTA
  #define ROBOT_OFFSET 0
#else
    #ifdef ROBOTB
      #define ROBOT_OFFSET 1
    #endif
#endif

typedef struct 
{
  bool canGoLeft = true;
  bool canGoRight = true;
  bool canGoFoward = true;
  bool canGoBackward = true;
} MazePosition;

typedef struct
{
  MazePosition positions[10][3];
} Maze;

void MazeSolver_init();
void MazeSolver_setObstacle(int row, int column);
void MazeSolver_algorithmicSolve();