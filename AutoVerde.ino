/* 
*       SELF DRIVING CAR 
*       Leonardo - Politecnico di Milano Innovathon Contest  
*/

#include "Arduino.h"

void setup()
{
    Serial.begin(9600);
    radarBegin();
    motor_begin();
    beginIr();
}

void loop()
{
    go();
}