#include "MazeSolver.hpp"

Maze maze;
Move moveHistory[100]; //all moves
MovementState currentPositionOrientation;

int currentMoveIndex;
int currentPosition_row;
int currentPosition_column;

#define OBSTACLE_LEFT 0
#define OBSTACLE_FOWARD 1
#define OBSTACLE_RIGHT 2
#define OBSTACLE_BACKWARD 3

void MazeSolver_init()
{
    MazeSolver_setBaseMaze();
    currentPosition_row = 0;
    currentPosition_column = 1;
    currentMoveIndex = 0;
}

Move MazeSolver_getNextMove()
{
    Move move;

    if (MazeSolver_canGoFoward() && moveHistory[currentMoveIndex].direction != BACKWARD)
    {
        move.direction = FORWARD;
        move.speed_pct = 20; //À TESTER SI INUTILE ENLEVER
        move.distance_cm = 50;
        move.isTurn = false;
    }
    return move;
}

void MazeSolver_onMoveCompletion(Move move)
{
    currentMoveIndex++;
    moveHistory[currentMoveIndex] = move;
    int newOrientation;
    
    if (move.isTurn)
    {
        //currentPositionOrientation.orientation = currentPositionOrientation
    }
    else
    {
        if (currentPositionOrientation.orientation % 2 == 0) //forward or backward
        {
            currentPositionOrientation.position_row += currentPositionOrientation.orientation;
        }
    }
    
}

bool MazeSolver_canGoFoward()
{
    return maze.positions[currentPosition_row][currentPosition_column].canGoFoward;
}

void MazeSolver_setObstacle(int row, int column, int direction)
{
    switch (direction)
    {
    case OBSTACLE_LEFT:
        if (column > 0)
        {
            maze.positions[row][column - 1].canGoRight = false;
        }
        maze.positions[row][column].canGoLeft = false;
        break;
    case OBSTACLE_FOWARD:
        if (row < MAZE_NUMBER_OF_ROWS - 1)
        {
            maze.positions[row + 1][column].canGoBackward = false;
        }
        maze.positions[row][column].canGoFoward = false;
        break;
    case OBSTACLE_RIGHT:
        if (column < MAZE_NUMBER_OF_COLUMNS - 1)
        {
            maze.positions[row][column + 1].canGoLeft = false;
        }
        maze.positions[row][column].canGoRight = false;
        break;
    case OBSTACLE_BACKWARD:
        if (row < 0)
        {
            maze.positions[row - 1][column].canGoFoward = false;
        }
        maze.positions[row][column].canGoBackward = false;
    default:
        break;
    }
}

// start at maze.rows[0].positions[1]
void MazeSolver_setBaseMaze()
{
    #pragma region Row_1
    maze.positions[0][0].canGoLeft = false;
    maze.positions[0][0].canGoFoward = true;
    maze.positions[0][0].canGoRight = true;
    maze.positions[0][0].canGoBackward = false;

    maze.positions[0][1].canGoLeft = true;
    maze.positions[0][1].canGoFoward = true;
    maze.positions[0][1].canGoRight = true;
    maze.positions[0][1].canGoBackward = false;

    maze.positions[0][2].canGoLeft = true;
    maze.positions[0][2].canGoFoward = true;
    maze.positions[0][2].canGoRight = false;
    maze.positions[0][2].canGoBackward = false;
    #pragma endregion
    #pragma region Row_2
    maze.positions[1][0].canGoLeft = false;
    maze.positions[1][0].canGoFoward = true;
    maze.positions[1][0].canGoRight = false;
    maze.positions[1][0].canGoBackward = true;

    maze.positions[1][1].canGoLeft = false;
    maze.positions[1][1].canGoFoward = true;
    maze.positions[1][1].canGoRight = false;
    maze.positions[1][1].canGoBackward = true;

    maze.positions[1][2].canGoLeft = false;
    maze.positions[1][2].canGoFoward = true;
    maze.positions[1][2].canGoRight = false;
    maze.positions[1][2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_3
    maze.positions[2][0].canGoLeft = false;
    maze.positions[2][0].canGoFoward = true;
    maze.positions[2][0].canGoRight = true;
    maze.positions[2][0].canGoBackward = true;

    maze.positions[2][1].canGoLeft = true;
    maze.positions[2][1].canGoFoward = true;
    maze.positions[2][1].canGoRight = true;
    maze.positions[2][1].canGoBackward = true;

    maze.positions[2][2].canGoLeft = true;
    maze.positions[2][2].canGoFoward = true;
    maze.positions[2][2].canGoRight = false;
    maze.positions[2][2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_4
    maze.positions[3][0].canGoLeft = false;
    maze.positions[3][0].canGoFoward = true;
    maze.positions[3][0].canGoRight = false;
    maze.positions[3][0].canGoBackward = true;

    maze.positions[3][1].canGoLeft = false;
    maze.positions[3][1].canGoFoward = true;
    maze.positions[3][1].canGoRight = false;
    maze.positions[3][1].canGoBackward = true;

    maze.positions[3][2].canGoLeft = false;
    maze.positions[3][2].canGoFoward = true;
    maze.positions[3][2].canGoRight = false;
    maze.positions[3][2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_5
    maze.positions[4][0].canGoLeft = false;
    maze.positions[4][0].canGoFoward = true;
    maze.positions[4][0].canGoRight = true;
    maze.positions[4][0].canGoBackward = true;

    maze.positions[4][1].canGoLeft = true;
    maze.positions[4][1].canGoFoward = true;
    maze.positions[4][1].canGoRight = true;
    maze.positions[4][1].canGoBackward = true;

    maze.positions[4][2].canGoLeft = true;
    maze.positions[4][2].canGoFoward = true;
    maze.positions[4][2].canGoRight = false;
    maze.positions[4][2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_6
    maze.positions[5][0].canGoLeft = false;
    maze.positions[5][0].canGoFoward = true;
    maze.positions[5][0].canGoRight = false;
    maze.positions[5][0].canGoBackward = true;

    maze.positions[5][1].canGoLeft = false;
    maze.positions[5][1].canGoFoward = true;
    maze.positions[5][1].canGoRight = false;
    maze.positions[5][1].canGoBackward = true;

    maze.positions[5][2].canGoLeft = false;
    maze.positions[5][2].canGoFoward = true;
    maze.positions[5][2].canGoRight = false;
    maze.positions[5][2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_7
    maze.positions[6][0].canGoLeft = false;
    maze.positions[6][0].canGoFoward = true;
    maze.positions[6][0].canGoRight = true;
    maze.positions[6][0].canGoBackward = true;

    maze.positions[6][1].canGoLeft = true;
    maze.positions[6][1].canGoFoward = true;
    maze.positions[6][1].canGoRight = true;
    maze.positions[6][1].canGoBackward = true;

    maze.positions[6][2].canGoLeft = true;
    maze.positions[6][2].canGoFoward = true;
    maze.positions[6][2].canGoRight = false;
    maze.positions[6][2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_8
    maze.positions[7][0].canGoLeft = false;
    maze.positions[7][0].canGoFoward = true;
    maze.positions[7][0].canGoRight = false;
    maze.positions[7][0].canGoBackward = true;

    maze.positions[7][1].canGoLeft = false;
    maze.positions[7][1].canGoFoward = true;
    maze.positions[7][1].canGoRight = false;
    maze.positions[7][1].canGoBackward = true;

    maze.positions[7][2].canGoLeft = false;
    maze.positions[7][2].canGoFoward = true;
    maze.positions[7][2].canGoRight = false;
    maze.positions[7][2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_9
    maze.positions[8][0].canGoLeft = false;
    maze.positions[8][0].canGoFoward = true;
    maze.positions[8][0].canGoRight = true;
    maze.positions[8][0].canGoBackward = true;

    maze.positions[8][1].canGoLeft = true;
    maze.positions[8][1].canGoFoward = true;
    maze.positions[8][1].canGoRight = true;
    maze.positions[8][1].canGoBackward = true;

    maze.positions[8][2].canGoLeft = true;
    maze.positions[8][2].canGoFoward = true;
    maze.positions[8][2].canGoRight = false;
    maze.positions[8][2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_10
    maze.positions[9][0].canGoLeft = false;
    maze.positions[9][0].canGoFoward = false;
    maze.positions[9][0].canGoRight = false;
    maze.positions[9][0].canGoBackward = true;

    maze.positions[9][1].canGoLeft = false;
    maze.positions[9][1].canGoFoward = false;
    maze.positions[9][1].canGoRight = false;
    maze.positions[9][1].canGoBackward = true;

    maze.positions[9][2].canGoLeft = false;
    maze.positions[9][2].canGoFoward = false;
    maze.positions[9][2].canGoRight = false;
    maze.positions[9][2].canGoBackward = true;
    #pragma endregion
}