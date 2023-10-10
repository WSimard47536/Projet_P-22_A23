#include "WhistleDetector.hpp"
#include "WhistlesoundDetector.hpp"
void waitForWhistle(){
    bool status = true;
    while(status){
        int sound = compareBothNoises(); 
        if (sound == 1)
        {
            status = false;
        }
        delay(100);
    }
}