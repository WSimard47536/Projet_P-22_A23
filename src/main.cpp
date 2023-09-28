#include "ROBUSMovement.hpp"
#include "ROBUSSensors.hpp"
#include "DC2318.hpp"
#include "WhistleDetector.hpp"
#include "ObstacleDetector.hpp"

#include "integrationTesting/ROBUSMovement_test.hpp"

void setup()
{
  BoardInit();
  DC2318_Innit(53, 49);
}

void loop()
{
  unsigned char wallType;
  wallType = DC2318_Read(53, 49);

  if (wallType == 0){
    Serial.println("No wall");
  }
  if (wallType == 1){
    Serial.println("Wall on the left");
  }
  if (wallType == 2){
    Serial.println("Wall on the right");
  }
  if (wallType == 3){
    Serial.println("Wall in front");
  }

  Serial.println("");
  delay(1000);
  if (ROBUS_IsBumper(REAR_BUMPER))
  {
    #ifdef ISTEST
      test_ROBUSMovement_moveStraight();
    #endif
  }
}