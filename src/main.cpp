#include "ROBUSMovement.hpp"
#include "ROBUSSensors.hpp"
#include "WhistlesoundDetector.hpp"
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
  //if (ROBUS_IsBumper(REAR_BUMPER))
  //{
  //  #ifdef ISTEST
  //    test_ROBUSMovement_moveStraight();
  //  #endif
  //}
  Serial.println("Va entrer dans le loop");
  waitForWhistle();
  Serial.println("A entendu le son et est sorti du while");
  //ROBUSMovement_turnOnSelf(-1, 0.10, 90);
  //ROBUSMovement_turnOnSelf(1, 0.10, 1080);
  delay(5000);
  
}