#include "Arduino.h"
#include "conf.h"

unsigned int last_check = 0;

bool previous_ir = false;

void beginIr()
{
    pinMode(A0, OUTPUT);
    pinMode(IR_PIN, INPUT);
    digitalWrite(A0, HIGH);
}

bool checkIr()
{
    if (millis() - last_check > 10000)
    {
        bool ir = !digitalRead(IR_PIN);
        if (ir == true)
        {
            last_check = millis();
        }

        return ir;
    }
    else
    {
        return false;
    }
}
