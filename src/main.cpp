#include <LibRobus.h>

// defines for speed multipliers
#define FOWARD 1.0f
#define BACKWARD -1.0f
#define LEFT_TURN 1.0f
#define RIGHT_TURN -1.0f

void moveStraight(float direction, float speed_pct, int distance_cm);
void turn(float direction, float speed_pct, int turnRadius_degreesPerWheelCycle, int turn_degrees);
void turnOnSelf(float direction, float speed_pct, int turn_degrees);

// tests
void moveStraightTest();
void turnTest();
void turnOnSelfTest();
void moveTest();

// global variables
uint32_t totalLeftMotorPulses = 0;
uint32_t totalRightMotorPulses = 0;

uint32_t totalExpectedLeftMotorPulses = 0;
uint32_t totalExpectedRightMotorPulses = 0;

void setup()
{
  BoardInit();
}

void loop()
{
  
}

// direction : direction which to go (FOWARD or BACKWARD)
// speed_pct : speed as a percentage
// distance_cm : distance in centimeters
void moveStraight(float direction, float speed_pct, int distance_cm)
{
  // à coder
  // indice : la vitesse finale sera égale à (direction * speed_pct / 100)
}

// direction : direction which to go (LEFT or RIGHT)
// speed_pct : speed as a percentage
// turnRadius_degrees : turn wideness in degrees per wheel turn
// turn_degrees : turn in degrees
void turn(int direction, float speed_pct, int turnRadius_degreesPerWheelCycle, int turn_degrees) // à revoir
{
  // à coder
}

// direction : direction which to go (LEFT or RIGHT)
// speed_pct : speed as a percentage
// turn_degrees : turn in degrees
void turnOnSelf(int direction, float speed_pct, int turn_degrees)
{
  // à coder
}

void moveStraightTest()
{
  moveStraight(FOWARD, 75, 50);
  delay(1000);
  moveStraight(BACKWARD, 75 , 50);
}

void turnTest()
{
  //turn(LEFT_TURN, 50.0, )
}

void turnOnSelfTest()
{
  turnOnSelf(LEFT_TURN, 50, 360);
  turnOnSelf(RIGHT_TURN, 50, 360);
}

void moveTest()
{
  moveStraight(FOWARD, 50, 120);
  turnOnSelf(LEFT_TURN, 30, 180);
  moveStraight(FOWARD, 50, 30);
  turnOnSelf(RIGHT_TURN, 30, 90);
  moveStraight(FOWARD, 50, 25);
  turnOnSelf(LEFT_TURN, 50, 180);
  moveStraight(FOWARD, 50, 50);
  turnOnSelf(RIGHT_TURN, 30, 180);
  moveStraight(FOWARD, 50, 25);
  turnOnSelf(RIGHT_TURN, 30, 90);
  moveStraight(BACKWARD, 50, 90);
}