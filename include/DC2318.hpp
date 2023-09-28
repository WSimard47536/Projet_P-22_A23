/**
 * @file DC2318.hpp
 * @author Élodie (you@domain.com)
 * @brief Header file for the use of the infra red sensor DC2318
 * @version 0.1
 * @date 2023-09-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

/**
 * @brief Fonction that initialize a DC2318 sensor
 * 
 * @param leftPin 
 * the pin used for the left IR sensor
 * @param rightPin 
 * the pin used for the right IR sensor
 */
void DC2318_Innit(int leftPin, int rightPin);

/**
 * @brief Function that read a DC2318 sensor
 * 
 * @param leftPin 
 * the pin used for the left IR sensor
 * @param rightPin 
 * the pin used for the right IR sensor
 * @return unsigned char 
 * Value returned depending on the state of the IR sensor.
 * 0: no walls
 * 1: A wall on the left is detected
 * 2: A wall on the right is detected
 * 3: A wall straight ahead is detected
 */
unsigned char DC2318_Read(int leftPin, int rightPin);