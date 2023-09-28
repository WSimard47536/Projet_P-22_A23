#include "ROBUSMovement.hpp"
#include "ROBUSSensors.hpp"
#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"

#include "integrationTesting/ROBUSMovement_test.hpp"

void setup()
{
  BoardInit();
  InitializeProximitySensors();
}

void loop()
{
  if (GetWall()){
    if (WallAligned()){
        Serial.println("Aligned wall detected");
    }
    else{
        Serial.println("Misaligned wall detected");
    }
  }
  else{
    Serial.println("No wall detected");
  }
  delay(1000);
  if (ROBUS_IsBumper(REAR_BUMPER))
  {
    #ifdef ISTEST
      test_ROBUSMovement_moveStraight();
    #endif
  }
}