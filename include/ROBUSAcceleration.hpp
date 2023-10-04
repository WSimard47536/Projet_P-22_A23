#pragma once

#include <LibRobus.h>

/**
 * @brief 
 * Define that sets at which speed the robot starts.
 * This cannot be 0 because otherwise the robot wont ever move.
 */
#define START_SPEED_OFFSET 0.1

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
float ROBUS_GetSpeedFactorFromCurrentPosition(float distanceLeft);