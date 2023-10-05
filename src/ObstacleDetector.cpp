#include "ObstacleDetector.hpp"

/**
 * @brief Detect if there's a wall in front of the robot
 * 
 * @return true 
 * A wall is detected 
 * @return false 
 * Nothing is detected
 */
bool GetWall(void){
    return DC2318_Read(DC2318_FRONT_PINS);
}

/**
 * @brief Verify if the wall is aligned
 * 
 * @return bool
 * false : The wall is not aligned
 * true : aligned or no wall
 */
bool WallAligned(void){
    unsigned char wallStatus = DC2318_Read(DC2318_FRONT_PINS);

    if (wallStatus == DC2318_NO_WALL){
        return true;
    }
    if (wallStatus == DC2318_RIGHT_WALL){
        return false;
    }
    if (wallStatus == DC2318_LEFT_WALL){
        return false;
    }
    if (wallStatus == DC2318_FRONT_WALL){
        return true;
    }
}

/**
 * @brief Initialize DC2318 in front of the robot
 * 
 */
void InitializeProximitySensors(void){
    DC2318_Innit(DC2318_FRONT_PINS);
}