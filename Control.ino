#include "Arduino.h"
#include "conf.h"

bool obstacle_found = false; //Check if run path corrction routine (Should run once only)
bool is_turning = false;     //Check if path has been already corrected (after obstacle detection)

void go()
{
    /*----- Check if obstacle -----*/
    int forw_mes = getRadar(90);
    if (forw_mes < MAX_DISTANCE_BEFORE_TURN) //Check first forward, if found break
    {
        obstacle_found = true;

        //Safe Roll Back
        if (forw_mes < SAFE_DISTANCE)
        {
            goBackward();
            Serial.println("Going backward");
            delay(1000);
            return;
        }

        if (is_turning) //If i am turning measure only forward
        {
            return;
        }

        Serial.println("Obstacole Forward");
    }
    else
    {
        int right_mes = getRadar(45); //Check second right, if found break
        if (right_mes < MAX_DISTANCE_BEFORE_TURN)
        {
            obstacle_found = true;
            Serial.println("Obstacole right");
        }
        else
        {
            int left_mes = getRadar(135); //Finally check left, if found break
            if (left_mes < MAX_DISTANCE_BEFORE_TURN)
            {
                obstacle_found = true;
                Serial.println("Obstacole Left");
            }
            else //No obstacle in no direction
            {
                obstacle_found = false;
                Serial.println("Clear");
            }
        }
    }

    //If obstacle and correction has not been berformed
    if (obstacle_found && !is_turning)
    {
        Serial.println("Correction start");
        motorStop(); //Stop before measure

        int r = getRadar(30);
        int l = getRadar(150);

        //Check what direction has maximum space available and turn here
        int maximum = max(l, r);
        if (l == maximum)
        {
            rotateLeft();
        }
        else if (r == maximum)
        {
            rotateRight();
        }
        is_turning = true;
    }
    else //If no obstacle or correction already performed
    {
        is_turning = false;
        goForward();
    }
}