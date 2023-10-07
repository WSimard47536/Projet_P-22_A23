/**
 * @file ROBUSDefines.hpp
 * @author Lyam BRS (lyam.brs@domain.com)
 * @brief This file contains defines used throughout
 * the ROBUS project. These defines are specific to the
 * ROBUS but can be used throughout the session's projects.
 * @version 0.1
 * @date 2023-10-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#pragma region -MOVEMENTS-
#define FORWARD 1.0f
#define BACKWARD -1.0f
#define LEFT_TURN 1.0f
#define RIGHT_TURN -1.0f
#pragma endregion

#pragma region -MOTORS-
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define LEFT_ENCODER 0
#define RIGHT_ENCODER 1
#pragma endregion

#pragma region -ORIENTATIONS
#define ORIENTATION_LEFT 0
#define ORIENTATION_FORWARD 1
#define ORIENTATION_RIGHT 2
#define ORIENTATION_BACKWARD 3
#pragma endregion

#pragma region -DIMMENSIONS
/** @brief The diameter of the motor wheels in centimeters */
#define DIAMETER 7.60f
/** @brief The approximated circumference of the motor wheels in centimeters */
#define CIRCUMFERENCE 23.87f
/** @brief how many pulses of encoders are necessary to make one rotation of the wheel. */
#define FULL_ROTATIONS_PULSES 3200.00f
#pragma endregion

