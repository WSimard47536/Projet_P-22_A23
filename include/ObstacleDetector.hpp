/**
 * @file ObstacleDetector.hpp
 * @author Élodie
 * @brief File header for obstacle detection in labynrith
 * @version 0.1
 * @date 2023-09-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "DC2318.hpp"

#define LEFT_PIN 53
#define RIGHT_PIN 49
#define DC2318_FRONT_PINS LEFT_PIN, RIGHT_PIN

/**
 * @brief Detect if there's a wall in front of the robot
 * 
 * @return true 
 * A wall is detected 
 * @return false 
 * Nothing is detected
 */
bool GetWall(void);

/**
 * @brief Verify if the wall is aligned
 * 
 * @return bool
 * false : The wall is not aligned
 * true : aligned or no wall
 */
bool WallAligned(void);

/**
 * @brief Initialize DC2318 in front of the robot
 * 
 */
void InitializeProximitySensors(void);