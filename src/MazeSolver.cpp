#include "MazeSolver.hpp"
#include "ROBUSMovement.hpp"

Maze maze;
Move defaultMove = {-2, 0};

Move moveHistory[MAZE_MOVE_HISTORY_SIZE];
Move moveBuffer[MAZE_BUFFER_SIZE];

int currentMoveIndex;
int bufferIndex;

int currentPosition_row;
int currentPosition_column;
int currentOrientation;

void MazeSolver_init()
{
    //MazeSolver_setBaseMaze();
    MazeSolver_setTestMaze();
    MazeSolver_resetMoveBuffer();
    MazeSolver_resetMoveHistory();
    currentMoveIndex = 0;
    currentPosition_row = 0;
    currentPosition_column = 1;
    currentOrientation = FACING_NORTH;
    maze.positions[currentPosition_row][currentPosition_column].members.hasMovedOn = true;
}

void MazeSolver_resetMoveBuffer()
{
    for (int bufferIndex = 0; bufferIndex < MAZE_BUFFER_SIZE; bufferIndex++)
    {
        moveBuffer[bufferIndex] = defaultMove;
    }
}

void MazeSolver_resetMoveHistory()
{
    for (int historyIndex = 0; historyIndex < MAZE_MOVE_HISTORY_SIZE; historyIndex++)
    {
        moveHistory[historyIndex] = defaultMove;
    }
}

void MazeSolver_setNextMoves()
{
    if (!MazeSolver_checkSetMove(true))
    {
        MazeSolver_checkSetMove(false);
    }
}

bool MazeSolver_checkSetMove(bool checkHasMovedOn)
{
    MazeSolver_resetMoveBuffer();
    bufferIndex = 0;
    bool hasFoundMoves = true;

    if (MazeSolver_canMoveTo(FACING_NORTH, checkHasMovedOn) == 1)
    {
        MazeSolver_addOrientationMoves(FACING_NORTH);
        MazeSolver_addMoveStraight();
        /*if (currentPosition_row < MAZE_NUMBER_OF_ROWS - 2)
        {
            MazeSolver_addMoveStraight();
        }*/
    }
    else if (MazeSolver_canMoveTo(FACING_WEST, checkHasMovedOn) == 1)
    {
        MazeSolver_addOrientationMoves(FACING_WEST);
        MazeSolver_addMoveStraight();
    }
    else if (MazeSolver_canMoveTo(FACING_EAST, checkHasMovedOn) == 1)
    {
        MazeSolver_addOrientationMoves(FACING_EAST);
        MazeSolver_addMoveStraight();
    }
    else if (MazeSolver_canMoveTo(FACING_SOUTH, checkHasMovedOn) == 1)
    {
        MazeSolver_addOrientationMoves(FACING_SOUTH);
        MazeSolver_addMoveStraight();
        /*if (currentPosition_row > 1)
        {
            MazeSolver_addMoveStraight();
        }*/
    }
    else //dead end if checkHasMovedOn is true
    {
        hasFoundMoves = false;
    }
    return hasFoundMoves;
}

void MazeSolver_executeNextMoves()
{
    Move move;
    for (int index = 0; index < MAZE_BUFFER_SIZE; index++)
    {
        if (moveBuffer[index].direction != - 2)
        {
            move = moveBuffer[index];
            if (!move.isTurn)
            {
                //ROBUSMovement_moveStraight((float)move.direction, 20.0f, 50.0f);
            }
            else
            {
                //ROBUSMovement_turnOnSelf((float)move.direction * -1, 0.15f, 90);
            }
            Serial.print("Direction : ");
            Serial.println(move.direction);
            Serial.print("IsTurn : ");
            Serial.println(move.isTurn);

            MazeSolver_onMoveCompletion(move);
            
            Serial.print("Row : ");
            Serial.println(currentPosition_row);
            Serial.print("Column : ");
            Serial.println(currentPosition_column);

            /*if (GetWall())
            {
              MazeSolver_setObstacle();
              return;
            }*/
        }
    }
}

void MazeSolver_addOrientationMoves(int wantedOrientation)
{
    int orientation = currentOrientation;
    int orientationDifference = orientation - wantedOrientation;
    int turnDirection = orientationDifference > 0 ? LEFT_TURN : RIGHT_TURN;

    if (abs(orientationDifference) == 3)
    {
      turnDirection = -1 * turnDirection;
    }

    if (orientationDifference != 0)
    {
        moveBuffer[bufferIndex].direction = turnDirection;
        moveBuffer[bufferIndex].isTurn = true;
        bufferIndex++;

        if (orientationDifference % 2 == 0)
        {
            moveBuffer[bufferIndex].direction = turnDirection;
            moveBuffer[bufferIndex].isTurn = true;
            bufferIndex++;
        }
    }
}

void MazeSolver_addMoveStraight()
{
    Move move;
    move.direction = FORWARD;
    move.isTurn = false;
    moveBuffer[bufferIndex] = move;
    bufferIndex++;
}

void MazeSolver_addMoveToPosition(int row, int column)
{
    
}

void MazeSolver_onMoveCompletion(Move move)
{
    moveHistory[currentMoveIndex] = move;
    currentMoveIndex++;

    if (move.isTurn)
    {
        currentOrientation = (currentOrientation + move.direction * - 1) % 4; // à tester
        if (currentOrientation == -1)
        {
          currentOrientation = FACING_SOUTH;
        }
    }
    else
    {
        if (currentOrientation % 2 == 1) //forward or backward
        {
            if (currentOrientation == FACING_NORTH)
            {
              currentPosition_row += move.direction;
            }
            else if (currentOrientation == FACING_SOUTH)
            {
              currentPosition_row -= move.direction;
            }
            else
            {
              Serial.print("Orientation Error");
            }
        }
        else
        {
            if (currentOrientation == FACING_EAST)
            {
                currentPosition_column += move.direction;
            }
            else if (currentOrientation == FACING_WEST)
            {
                currentPosition_column -= move.direction;
            }
        }
    }
    maze.positions[currentPosition_row][currentPosition_column].members.hasMovedOn = true;
}

bool MazeSolver_hasCompletedMaze()
{
    return currentPosition_row == MAZE_NUMBER_OF_ROWS - 1;
}

bool MazeSolver_canMoveTo(int direction, bool checkHasMovedOn)
{
    MazePosition position = maze.positions[currentPosition_row][currentPosition_column];
    bool canMoveToDirection = position.values[direction];

    if (currentPosition_row == 4 && currentPosition_column == 1)
    {
      Serial.print(canMoveToDirection);
      Serial.print(position.members.canGoFoward);
    }

    if (!checkHasMovedOn)
    {
        return canMoveToDirection;
    }
    else if (!MazeSolver_hasMovedOn(direction))
    {
        return canMoveToDirection;
    }
    else 
    {
        Serial.println("Cant");
        return false;
    }
}

bool MazeSolver_hasMovedOn(int direction) // à coder
{
    bool hasMovedOn;
    switch (direction)
    {
    case FACING_WEST:
        if (currentPosition_column > 0)
        {
            hasMovedOn = maze.positions[currentPosition_row][currentPosition_column - 1].members.hasMovedOn;
        }
        break;
    case FACING_NORTH:
        if (currentPosition_row < MAZE_NUMBER_OF_ROWS - 1)
        {
            hasMovedOn = maze.positions[currentPosition_row + 1][currentPosition_column].members.hasMovedOn;
        }
        break;
    case FACING_EAST:
        if (currentPosition_column < MAZE_NUMBER_OF_COLUMNS - 1)
        {
            hasMovedOn = maze.positions[currentPosition_row][currentPosition_column + 1].members.hasMovedOn;
        }
        break;
    case FACING_SOUTH:
        if (currentPosition_row > 0)
        {
            hasMovedOn = maze.positions[currentPosition_row - 1][currentPosition_column].members.hasMovedOn;
        }
        break;
    default:
        break;
    }
    Serial.print("Has moved on ");
    Serial.print(direction);
    Serial.print(" : ");
    Serial.println(hasMovedOn);
    return hasMovedOn;
}

void MazeSolver_setObstacle()
{
    int row = currentPosition_row;
    int column = currentPosition_column;
    switch (currentOrientation)
    {
        case FACING_WEST:
            if (column > 0)
            {
                maze.positions[row][column - 1].members.canGoRight = false;
            }
            maze.positions[row][column].members.canGoLeft = false;
            break;
        case FACING_NORTH:
            if (row < MAZE_NUMBER_OF_ROWS - 1)
            {
                maze.positions[row + 1][column].members.canGoBackwards = false;
            }
            maze.positions[row][column].members.canGoFoward = false;
            break;
        case FACING_EAST:
            if (column < MAZE_NUMBER_OF_COLUMNS - 1)
            {
                maze.positions[row][column + 1].members.canGoLeft = false;
            }
            maze.positions[row][column].members.canGoRight = false;
            break;
        case FACING_SOUTH:
            if (row < 0)
            {
                maze.positions[row - 1][column].members.canGoFoward = false;
            }
            maze.positions[row][column].members.canGoBackwards = false;
        default:
            break;
    }
}

// start at maze.rows[0].positions[1]
void MazeSolver_setBaseMaze()
{
    #pragma region Row_1
    maze.positions[0][0].members.canGoLeft = false;
    maze.positions[0][0].members.canGoFoward = true;
    maze.positions[0][0].members.canGoRight = true;
    maze.positions[0][0].members.canGoBackwards = false;

    maze.positions[0][1].members.canGoLeft = true;
    maze.positions[0][1].members.canGoFoward = true;
    maze.positions[0][1].members.canGoRight = true;
    maze.positions[0][1].members.canGoBackwards = false;

    maze.positions[0][2].members.canGoLeft = true;
    maze.positions[0][2].members.canGoFoward = true;
    maze.positions[0][2].members.canGoRight = false;
    maze.positions[0][2].members.canGoBackwards = false;
    #pragma endregion
    #pragma region Row_2
    maze.positions[1][0].members.canGoLeft = false;
    maze.positions[1][0].members.canGoFoward = true;
    maze.positions[1][0].members.canGoRight = false;
    maze.positions[1][0].members.canGoBackwards = true;

    maze.positions[1][1].members.canGoLeft = false;
    maze.positions[1][1].members.canGoFoward = true;
    maze.positions[1][1].members.canGoRight = false;
    maze.positions[1][1].members.canGoBackwards = true;

    maze.positions[1][2].members.canGoLeft = false;
    maze.positions[1][2].members.canGoFoward = true;
    maze.positions[1][2].members.canGoRight = false;
    maze.positions[1][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_3
    maze.positions[2][0].members.canGoLeft = false;
    maze.positions[2][0].members.canGoFoward = true;
    maze.positions[2][0].members.canGoRight = true;
    maze.positions[2][0].members.canGoBackwards = true;

    maze.positions[2][1].members.canGoLeft = true;
    maze.positions[2][1].members.canGoFoward = true;
    maze.positions[2][1].members.canGoRight = true;
    maze.positions[2][1].members.canGoBackwards = true;

    maze.positions[2][2].members.canGoLeft = true;
    maze.positions[2][2].members.canGoFoward = true;
    maze.positions[2][2].members.canGoRight = false;
    maze.positions[2][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_4
    maze.positions[3][0].members.canGoLeft = false;
    maze.positions[3][0].members.canGoFoward = true;
    maze.positions[3][0].members.canGoRight = false;
    maze.positions[3][0].members.canGoBackwards = true;

    maze.positions[3][1].members.canGoLeft = false;
    maze.positions[3][1].members.canGoFoward = true;
    maze.positions[3][1].members.canGoRight = false;
    maze.positions[3][1].members.canGoBackwards = true;

    maze.positions[3][2].members.canGoLeft = false;
    maze.positions[3][2].members.canGoFoward = true;
    maze.positions[3][2].members.canGoRight = false;
    maze.positions[3][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_5
    maze.positions[4][0].members.canGoLeft = false;
    maze.positions[4][0].members.canGoFoward = true;
    maze.positions[4][0].members.canGoRight = true;
    maze.positions[4][0].members.canGoBackwards = true;

    maze.positions[4][1].members.canGoLeft = true;
    maze.positions[4][1].members.canGoFoward = true;
    maze.positions[4][1].members.canGoRight = true;
    maze.positions[4][1].members.canGoBackwards = true;

    maze.positions[4][2].members.canGoLeft = true;
    maze.positions[4][2].members.canGoFoward = true;
    maze.positions[4][2].members.canGoRight = false;
    maze.positions[4][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_6
    maze.positions[5][0].members.canGoLeft = false;
    maze.positions[5][0].members.canGoFoward = true;
    maze.positions[5][0].members.canGoRight = false;
    maze.positions[5][0].members.canGoBackwards = true;

    maze.positions[5][1].members.canGoLeft = false;
    maze.positions[5][1].members.canGoFoward = true;
    maze.positions[5][1].members.canGoRight = false;
    maze.positions[5][1].members.canGoBackwards = true;

    maze.positions[5][2].members.canGoLeft = false;
    maze.positions[5][2].members.canGoFoward = true;
    maze.positions[5][2].members.canGoRight = false;
    maze.positions[5][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_7
    maze.positions[6][0].members.canGoLeft = false;
    maze.positions[6][0].members.canGoFoward = true;
    maze.positions[6][0].members.canGoRight = true;
    maze.positions[6][0].members.canGoBackwards = true;

    maze.positions[6][1].members.canGoLeft = true;
    maze.positions[6][1].members.canGoFoward = true;
    maze.positions[6][1].members.canGoRight = true;
    maze.positions[6][1].members.canGoBackwards = true;

    maze.positions[6][2].members.canGoLeft = true;
    maze.positions[6][2].members.canGoFoward = true;
    maze.positions[6][2].members.canGoRight = false;
    maze.positions[6][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_8
    maze.positions[7][0].members.canGoLeft = false;
    maze.positions[7][0].members.canGoFoward = true;
    maze.positions[7][0].members.canGoRight = false;
    maze.positions[7][0].members.canGoBackwards = true;

    maze.positions[7][1].members.canGoLeft = false;
    maze.positions[7][1].members.canGoFoward = true;
    maze.positions[7][1].members.canGoRight = false;
    maze.positions[7][1].members.canGoBackwards = true;

    maze.positions[7][2].members.canGoLeft = false;
    maze.positions[7][2].members.canGoFoward = true;
    maze.positions[7][2].members.canGoRight = false;
    maze.positions[7][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_9
    maze.positions[8][0].members.canGoLeft = false;
    maze.positions[8][0].members.canGoFoward = true;
    maze.positions[8][0].members.canGoRight = true;
    maze.positions[8][0].members.canGoBackwards = true;

    maze.positions[8][1].members.canGoLeft = true;
    maze.positions[8][1].members.canGoFoward = true;
    maze.positions[8][1].members.canGoRight = true;
    maze.positions[8][1].members.canGoBackwards = true;

    maze.positions[8][2].members.canGoLeft = true;
    maze.positions[8][2].members.canGoFoward = true;
    maze.positions[8][2].members.canGoRight = false;
    maze.positions[8][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_10
    maze.positions[9][0].members.canGoLeft = false;
    maze.positions[9][0].members.canGoFoward = false;
    maze.positions[9][0].members.canGoRight = false;
    maze.positions[9][0].members.canGoBackwards = true;

    maze.positions[9][1].members.canGoLeft = false;
    maze.positions[9][1].members.canGoFoward = false;
    maze.positions[9][1].members.canGoRight = false;
    maze.positions[9][1].members.canGoBackwards = true;

    maze.positions[9][2].members.canGoLeft = false;
    maze.positions[9][2].members.canGoFoward = false;
    maze.positions[9][2].members.canGoRight = false;
    maze.positions[9][2].members.canGoBackwards = true;
    #pragma endregion

    for (int row = 0; row < MAZE_NUMBER_OF_ROWS; row++)
    {
        for (int column = 0; column < MAZE_NUMBER_OF_COLUMNS; column++)
        {
            maze.positions[row][column].members.hasMovedOn = false;
        }
    }
}

void MazeSolver_setTestMaze()
{
    #pragma region Row_1
    maze.positions[0][0].members.canGoLeft = false;
    maze.positions[0][0].members.canGoFoward = false;
    maze.positions[0][0].members.canGoRight = true;
    maze.positions[0][0].members.canGoBackwards = false;

    maze.positions[0][1].members.canGoLeft = true;
    maze.positions[0][1].members.canGoFoward = false;
    maze.positions[0][1].members.canGoRight = true;
    maze.positions[0][1].members.canGoBackwards = false;

    maze.positions[0][2].members.canGoLeft = true;
    maze.positions[0][2].members.canGoFoward = true;
    maze.positions[0][2].members.canGoRight = false;
    maze.positions[0][2].members.canGoBackwards = false;
    #pragma endregion
    #pragma region Row_2
    maze.positions[1][0].members.canGoLeft = false;
    maze.positions[1][0].members.canGoFoward = true;
    maze.positions[1][0].members.canGoRight = false;
    maze.positions[1][0].members.canGoBackwards = false;

    maze.positions[1][1].members.canGoLeft = false;
    maze.positions[1][1].members.canGoFoward = true;
    maze.positions[1][1].members.canGoRight = false;
    maze.positions[1][1].members.canGoBackwards = false;

    maze.positions[1][2].members.canGoLeft = false;
    maze.positions[1][2].members.canGoFoward = true;
    maze.positions[1][2].members.canGoRight = false;
    maze.positions[1][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_3
    maze.positions[2][0].members.canGoLeft = false;
    maze.positions[2][0].members.canGoFoward = true;
    maze.positions[2][0].members.canGoRight = true;
    maze.positions[2][0].members.canGoBackwards = true;

    maze.positions[2][1].members.canGoLeft = true;
    maze.positions[2][1].members.canGoFoward = true;
    maze.positions[2][1].members.canGoRight = true;
    maze.positions[2][1].members.canGoBackwards = true;

    maze.positions[2][2].members.canGoLeft = true;
    maze.positions[2][2].members.canGoFoward = true;
    maze.positions[2][2].members.canGoRight = false;
    maze.positions[2][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_4
    maze.positions[3][0].members.canGoLeft = false;
    maze.positions[3][0].members.canGoFoward = true;
    maze.positions[3][0].members.canGoRight = false;
    maze.positions[3][0].members.canGoBackwards = true;

    maze.positions[3][1].members.canGoLeft = false;
    maze.positions[3][1].members.canGoFoward = true;
    maze.positions[3][1].members.canGoRight = false;
    maze.positions[3][1].members.canGoBackwards = true;

    maze.positions[3][2].members.canGoLeft = false;
    maze.positions[3][2].members.canGoFoward = true;
    maze.positions[3][2].members.canGoRight = false;
    maze.positions[3][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_5
    maze.positions[4][0].members.canGoLeft = false;
    maze.positions[4][0].members.canGoFoward = true;
    maze.positions[4][0].members.canGoRight = false;
    maze.positions[4][0].members.canGoBackwards = true;

    maze.positions[4][1].members.canGoLeft = false;
    maze.positions[4][1].members.canGoFoward = false;
    maze.positions[4][1].members.canGoRight = true;
    maze.positions[4][1].members.canGoBackwards = true;

    maze.positions[4][2].members.canGoLeft = true;
    maze.positions[4][2].members.canGoFoward = false;
    maze.positions[4][2].members.canGoRight = false;
    maze.positions[4][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_6
    maze.positions[5][0].members.canGoLeft = false;
    maze.positions[5][0].members.canGoFoward = true;
    maze.positions[5][0].members.canGoRight = false;
    maze.positions[5][0].members.canGoBackwards = true;

    maze.positions[5][1].members.canGoLeft = false;
    maze.positions[5][1].members.canGoFoward = true;
    maze.positions[5][1].members.canGoRight = false;
    maze.positions[5][1].members.canGoBackwards = false;

    maze.positions[5][2].members.canGoLeft = false;
    maze.positions[5][2].members.canGoFoward = true;
    maze.positions[5][2].members.canGoRight = false;
    maze.positions[5][2].members.canGoBackwards = false;
    #pragma endregion
    #pragma region Row_7
    maze.positions[6][0].members.canGoLeft = false;
    maze.positions[6][0].members.canGoFoward = true;
    maze.positions[6][0].members.canGoRight = true;
    maze.positions[6][0].members.canGoBackwards = true;

    maze.positions[6][1].members.canGoLeft = true;
    maze.positions[6][1].members.canGoFoward = true;
    maze.positions[6][1].members.canGoRight = true;
    maze.positions[6][1].members.canGoBackwards = true;

    maze.positions[6][2].members.canGoLeft = true;
    maze.positions[6][2].members.canGoFoward = true;
    maze.positions[6][2].members.canGoRight = false;
    maze.positions[6][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_8
    maze.positions[7][0].members.canGoLeft = false;
    maze.positions[7][0].members.canGoFoward = true;
    maze.positions[7][0].members.canGoRight = false;
    maze.positions[7][0].members.canGoBackwards = true;

    maze.positions[7][1].members.canGoLeft = false;
    maze.positions[7][1].members.canGoFoward = true;
    maze.positions[7][1].members.canGoRight = false;
    maze.positions[7][1].members.canGoBackwards = true;

    maze.positions[7][2].members.canGoLeft = false;
    maze.positions[7][2].members.canGoFoward = true;
    maze.positions[7][2].members.canGoRight = false;
    maze.positions[7][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_9
    maze.positions[8][0].members.canGoLeft = false;
    maze.positions[8][0].members.canGoFoward = true;
    maze.positions[8][0].members.canGoRight = true;
    maze.positions[8][0].members.canGoBackwards = true;

    maze.positions[8][1].members.canGoLeft = true;
    maze.positions[8][1].members.canGoFoward = true;
    maze.positions[8][1].members.canGoRight = true;
    maze.positions[8][1].members.canGoBackwards = true;

    maze.positions[8][2].members.canGoLeft = true;
    maze.positions[8][2].members.canGoFoward = true;
    maze.positions[8][2].members.canGoRight = false;
    maze.positions[8][2].members.canGoBackwards = true;
    #pragma endregion
    #pragma region Row_10
    maze.positions[9][0].members.canGoLeft = false;
    maze.positions[9][0].members.canGoFoward = false;
    maze.positions[9][0].members.canGoRight = false;
    maze.positions[9][0].members.canGoBackwards = true;

    maze.positions[9][1].members.canGoLeft = false;
    maze.positions[9][1].members.canGoFoward = false;
    maze.positions[9][1].members.canGoRight = false;
    maze.positions[9][1].members.canGoBackwards = true;

    maze.positions[9][2].members.canGoLeft = false;
    maze.positions[9][2].members.canGoFoward = false;
    maze.positions[9][2].members.canGoRight = false;
    maze.positions[9][2].members.canGoBackwards = true;
    #pragma endregion

    for (int row = 0; row < MAZE_NUMBER_OF_ROWS; row++)
    {
        for (int column = 0; column < MAZE_NUMBER_OF_COLUMNS; column++)
        {
            maze.positions[row][column].members.hasMovedOn = false;
        }
    }
}