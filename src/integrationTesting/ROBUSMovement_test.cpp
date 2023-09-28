#include "integrationTesting/ROBUSMovement_test.hpp"

void test_ROBUSMovement_moveStraight()
{
  ROBUSMovement_moveStraight(FOWARD, 25, 100);
}

void test_ROBUSMovement_turn()
{
  ROBUSMovement_turn(LEFT_TURN, 25, 0, 90);
}

void test_ROBUSMovement_turnOnSelf()
{
  ROBUSMovement_turnOnSelf(RIGHT_TURN, 25, 90);
}