#include "math.h"
#include "ROBUSAcceleration.hpp"


/**
 * @brief This function's use is to calculate the wanted speed
 * factor depending on how much distance is left to move to
 * reach its wanted destination. This allows the robot to perform
 * an acceleration when starting its movement and a deacceleration
 * when its nearing the end of its distance.
 * 
 * This is important to make the robot go faster than instant
 * acceleration that would otherwise cause slip and potential
 * drifting.
 * @param distanceLeft 
 * a ratio from 0 to 1 that indicates how close the robot is
 * to reaching its destination.
 * @return float 
 */
float ROBUS_GetSpeedFactorFromCurrentPosition(float distanceLeft)
{
  #pragma region -ERROR_CASES-
  if(distanceLeft > 1)
  {
    Serial.println("Acceleration.cpp : l24 : ratio cannot be higher than 1.");
    return 0;
  }

  if(distanceLeft < 0)
  {
    Serial.println("Acceleration.cpp : l30 : ratio cannot be lower than 0.");
    return 0;
  }
  #pragma endregion

  #pragma region -SPEED COMPENSATION-

  /**
   * @brief allows the sin operator to
   * make a bell curve of the wanted speed
   * depending on the distance left to make
   * to reach the wanted destination.
   */
  float radians = distanceLeft * 3.14f;

  return START_SPEED_OFFSET + sin(radians);

  #pragma endregion
}