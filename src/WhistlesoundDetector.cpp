#include "WhistleDetector.hpp"
#include <LibRobus.h>
const int ambientNoise = A0;
const int whistleNoise = A1;

int readAmbientNoise(){
    int i = analogRead(ambientNoise);
    Serial.print("Ambient: ");
    Serial.println(i);
    return i;
}

int readWhistleNoise(){
    int i = analogRead(whistleNoise);
    Serial.print("Whistle: ");
    Serial.println(i);
    return i;
}


bool compareBothNoises(){
    int a = readAmbientNoise();
    int w = readWhistleNoise();
    //int a = 650;
    if (a > w){
        Serial.println(0);
        return 0;
    }
    else{
        Serial.println(1);
        return 1;
    }
}