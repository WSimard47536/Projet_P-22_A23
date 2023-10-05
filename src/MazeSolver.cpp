#include "MazeSolver.hpp"

Maze maze;

void MazeSolver_init()
{
    MazeSolver_setBaseMaze();
}

void MazeSolver_algorithmicSolve()
{
    
}

void MazeSolver_setObstacle(int row, int column, int direction)
{
    maze.rows[row].positions[column]
}

// start at maze.rows[0].positions[1]
void MazeSolver_setBaseMaze()
{
    #pragma region Row_1
    maze.rows[0].positions[0].canGoLeft = false;
    maze.rows[0].positions[0].canGoFoward = true;
    maze.rows[0].positions[0].canGoRight = true;
    maze.rows[0].positions[0].canGoBackward = false;

    maze.rows[0].positions[1].canGoLeft = true;
    maze.rows[0].positions[1].canGoFoward = true;
    maze.rows[0].positions[1].canGoRight = true;
    maze.rows[0].positions[1].canGoBackward = false;

    maze.rows[0].positions[2].canGoLeft = true;
    maze.rows[0].positions[2].canGoFoward = true;
    maze.rows[0].positions[2].canGoRight = false;
    maze.rows[0].positions[2].canGoBackward = false;
    #pragma endregion
    #pragma region Row_2
    maze.rows[1].positions[0].canGoLeft = false;
    maze.rows[1].positions[0].canGoFoward = true;
    maze.rows[1].positions[0].canGoRight = false;
    maze.rows[1].positions[0].canGoBackward = true;

    maze.rows[1].positions[1].canGoLeft = false;
    maze.rows[1].positions[1].canGoFoward = true;
    maze.rows[1].positions[1].canGoRight = false;
    maze.rows[1].positions[1].canGoBackward = true;

    maze.rows[1].positions[2].canGoLeft = false;
    maze.rows[1].positions[2].canGoFoward = true;
    maze.rows[1].positions[2].canGoRight = false;
    maze.rows[1].positions[2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_3
    maze.rows[2].positions[0].canGoLeft = false;
    maze.rows[2].positions[0].canGoFoward = true;
    maze.rows[2].positions[0].canGoRight = true;
    maze.rows[2].positions[0].canGoBackward = true;

    maze.rows[2].positions[1].canGoLeft = true;
    maze.rows[2].positions[1].canGoFoward = true;
    maze.rows[2].positions[1].canGoRight = true;
    maze.rows[2].positions[1].canGoBackward = true;

    maze.rows[2].positions[2].canGoLeft = true;
    maze.rows[2].positions[2].canGoFoward = true;
    maze.rows[2].positions[2].canGoRight = false;
    maze.rows[2].positions[2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_4
    maze.rows[3].positions[0].canGoLeft = false;
    maze.rows[3].positions[0].canGoFoward = true;
    maze.rows[3].positions[0].canGoRight = false;
    maze.rows[3].positions[0].canGoBackward = true;

    maze.rows[3].positions[1].canGoLeft = false;
    maze.rows[3].positions[1].canGoFoward = true;
    maze.rows[3].positions[1].canGoRight = false;
    maze.rows[3].positions[1].canGoBackward = true;

    maze.rows[3].positions[2].canGoLeft = false;
    maze.rows[3].positions[2].canGoFoward = true;
    maze.rows[3].positions[2].canGoRight = false;
    maze.rows[3].positions[2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_5
    maze.rows[4].positions[0].canGoLeft = false;
    maze.rows[4].positions[0].canGoFoward = true;
    maze.rows[4].positions[0].canGoRight = true;
    maze.rows[4].positions[0].canGoBackward = true;

    maze.rows[4].positions[1].canGoLeft = true;
    maze.rows[4].positions[1].canGoFoward = true;
    maze.rows[4].positions[1].canGoRight = true;
    maze.rows[4].positions[1].canGoBackward = true;

    maze.rows[4].positions[2].canGoLeft = true;
    maze.rows[4].positions[2].canGoFoward = true;
    maze.rows[4].positions[2].canGoRight = false;
    maze.rows[4].positions[2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_6
    maze.rows[5].positions[0].canGoLeft = false;
    maze.rows[5].positions[0].canGoFoward = true;
    maze.rows[5].positions[0].canGoRight = false;
    maze.rows[5].positions[0].canGoBackward = true;

    maze.rows[5].positions[1].canGoLeft = false;
    maze.rows[5].positions[1].canGoFoward = true;
    maze.rows[5].positions[1].canGoRight = false;
    maze.rows[5].positions[1].canGoBackward = true;

    maze.rows[5].positions[2].canGoLeft = false;
    maze.rows[5].positions[2].canGoFoward = true;
    maze.rows[5].positions[2].canGoRight = false;
    maze.rows[5].positions[2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_7
    maze.rows[6].positions[0].canGoLeft = false;
    maze.rows[6].positions[0].canGoFoward = true;
    maze.rows[6].positions[0].canGoRight = true;
    maze.rows[6].positions[0].canGoBackward = true;

    maze.rows[6].positions[1].canGoLeft = true;
    maze.rows[6].positions[1].canGoFoward = true;
    maze.rows[6].positions[1].canGoRight = true;
    maze.rows[6].positions[1].canGoBackward = true;

    maze.rows[6].positions[2].canGoLeft = true;
    maze.rows[6].positions[2].canGoFoward = true;
    maze.rows[6].positions[2].canGoRight = false;
    maze.rows[6].positions[2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_8
    maze.rows[7].positions[0].canGoLeft = false;
    maze.rows[7].positions[0].canGoFoward = true;
    maze.rows[7].positions[0].canGoRight = false;
    maze.rows[7].positions[0].canGoBackward = true;

    maze.rows[7].positions[1].canGoLeft = false;
    maze.rows[7].positions[1].canGoFoward = true;
    maze.rows[7].positions[1].canGoRight = false;
    maze.rows[7].positions[1].canGoBackward = true;

    maze.rows[7].positions[2].canGoLeft = false;
    maze.rows[7].positions[2].canGoFoward = true;
    maze.rows[7].positions[2].canGoRight = false;
    maze.rows[7].positions[2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_9
    maze.rows[8].positions[0].canGoLeft = false;
    maze.rows[8].positions[0].canGoFoward = true;
    maze.rows[8].positions[0].canGoRight = true;
    maze.rows[8].positions[0].canGoBackward = true;

    maze.rows[8].positions[1].canGoLeft = true;
    maze.rows[8].positions[1].canGoFoward = true;
    maze.rows[8].positions[1].canGoRight = true;
    maze.rows[8].positions[1].canGoBackward = true;

    maze.rows[8].positions[2].canGoLeft = true;
    maze.rows[8].positions[2].canGoFoward = true;
    maze.rows[8].positions[2].canGoRight = false;
    maze.rows[8].positions[2].canGoBackward = true;
    #pragma endregion
    #pragma region Row_10
    maze.rows[9].positions[0].canGoLeft = false;
    maze.rows[9].positions[0].canGoFoward = false;
    maze.rows[9].positions[0].canGoRight = false;
    maze.rows[9].positions[0].canGoBackward = true;

    maze.rows[9].positions[1].canGoLeft = false;
    maze.rows[9].positions[1].canGoFoward = false;
    maze.rows[9].positions[1].canGoRight = false;
    maze.rows[9].positions[1].canGoBackward = true;

    maze.rows[9].positions[2].canGoLeft = false;
    maze.rows[9].positions[2].canGoFoward = false;
    maze.rows[9].positions[2].canGoRight = false;
    maze.rows[9].positions[2].canGoBackward = true;
    #pragma endregion
}