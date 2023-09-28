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
  MazePosition positions[3];
} MazeRow;

typedef struct
{
  MazeRow rows[10];
} Maze;

void MazeSolver_algorithmicSolve();