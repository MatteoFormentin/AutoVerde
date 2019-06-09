#include "Arduino.h"
#include "conf.h"

bool is_moving = false;
bool obstacle_found = false; //Check if run path corrction routine (Should run once only)
bool is_turning = false;     //Check if path has been already corrected (after obstacle detection)

void go()
{
    checkIfIrStop();

    /*Serial.print("is_moving: ");

    Serial.println(is_moving);*/

    if (is_moving) //Correggere!!
    {
        /*----- Check if obstacle -----*/
        if (!obstacle_found)
        {
            int forw_mes = getRadar(90);
            if (forw_mes < MAX_DISTANCE_BEFORE_TURN) //Check first forward, if found break
            {
                obstacle_found = true;

                //Safe Roll Back
                /*  if (forw_mes < SAFE_DISTANCE)
            {
                goBackward(1000);
                Serial.println("Going backward");
                return;
            }*/

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
        }

        //If obstacle and correction has not been berformed
        if (obstacle_found)
        {
            if (is_turning)
            {
                Serial.println("Turning");
                if (checkIfIrStop())
                {
                    return;
                }

                delay(ROTATATION_STOP_TIME);
                int forw_mes = getRadar(90);
                if (forw_mes < MAX_DISTANCE_BEFORE_TURN) //Check first forward, if found break
                {
                    runMotor(ROTATATION_TIME);
                }
                else
                {
                    obstacle_found = false;
                    is_turning = false;
                    Serial.println("Set to false");
                }
            }
            else
            {
                Serial.println("Correction start");
                motorStop(); //Stop before measure
                //delay(ROTATATION_STOP_TIME);
                if (checkIfIrStop())
                {
                    return;
                }
                int r = getRadar(30);
                int l = getRadar(150);

                //Check what direction has maximum space available and turn here
                int maximum = max(l, r);
                if (l == maximum)
                {
                    rotateLeft(ROTATATION_TIME);
                }
                else if (r == maximum)
                {
                    rotateRight(ROTATATION_TIME);
                }
                is_turning = true;
            }
        }
        else //If no obstacle or correction already performed
        {
            is_turning = false;
            goForwardContinuosly();
        }
    }
}

bool checkIfIrStop()
{
    if (checkIr())
    {
        if (is_moving)
        {
            //STOP (END LAP)
            is_moving = false;
            obstacle_found = false;
            is_turning = false;
            motorStop();
            Serial.println("asdf stop");
            return true;
        }
        else
        {
            //GO (START LAP)
            is_moving = true;
            Serial.println("Start");
            return false;
        }
    }
}