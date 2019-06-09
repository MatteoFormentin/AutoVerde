/* 
*       IR SENSOR
*       Used for starting and stopping the car once crossing finish line
*/

#include "Arduino.h"
#include "conf.h"

unsigned int last_check = 0;

bool previous_ir = false;

void beginIr()
{
    pinMode(IR_PULLUP_PIN, OUTPUT);
    pinMode(IR_PIN, INPUT);
    digitalWrite(IR_PULLUP_PIN, HIGH);
}

/*---- Check if start or stop seignal emitted ----*/
bool checkIr()
{
    if (millis() - last_check > 10000)
    {
        bool ir = !digitalRead(IR_PIN);
        if (ir == true)
        {
            //If if recieve the signal, ignore any other imput for n second
            last_check = millis();
        }
        return ir;
    }
    else
    {
        return false;
    }
}
