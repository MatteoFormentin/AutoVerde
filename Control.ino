/* 
*       AUTONOMOUS DRIVE AND OBSTACLE AVOIDING
*/

#include "Arduino.h"
#include "conf.h"

bool is_moving = false;
bool obstacle_found = false; //Check if run path corrction routine (Should run once only)
bool is_turning = false;     //Check if path has been already corrected (after obstacle detection)
bool parking = false;
bool raddriz = true;

void go()
{
    checkIfIrStop();

    /*----- Lap routine -----*/
    if (is_moving)
    {
        /*----- Standard forward routine -----*/
        if (!obstacle_found)
        {
            //Check if obstacle
            int forw_mes = getRadar(90);
            if (forw_mes < MAX_DISTANCE_BEFORE_TURN) //Check first forward, if found break
            {
                obstacle_found = true;
                Serial.println("Obstacole Forward");
            }
            else
            {
                if (checkIfIrStop())
                {
                    return;
                }
                int right_mes = getRadar(45); //Check second right, if found break
                if (right_mes < MAX_DISTANCE_BEFORE_TURN)
                {
                    obstacle_found = true;
                    Serial.println("Obstacole right");
                }
                else
                {

                    if (checkIfIrStop())
                    {
                        return;
                    }
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

        /*----- Obstacle avoiding routine -----*/
        if (obstacle_found) //If obstacle and correction has not been berformed
        {
            //If is turning the rotation direction has been already choosen, so just check if forward line of sight is clear
            if (is_turning)
            {
                Serial.println("Turning");

                if (checkIfIrStop())
                {
                    return;
                }
                delay(ROTATATION_STOP_TIME); //Needed to give motor time to stop
                int forw_mes = getRadar(90);

                if (forw_mes < MAX_DISTANCE_BEFORE_TURN) //If not clear continue rotate
                {
                    runMotor(ROTATATION_TIME);
                }
                else //Else go foward a bit so i will not find obstacle left or right
                {
                    goForward(400);
                    is_turning = false;
                    obstacle_found = false;
                    Serial.println("Set to false");
                }
            }
            else //If obstacle has just been found choose best direction
            {
                Serial.println("Correction start");
                motorStop(); //Stop before measure else will be wrong

                if (checkIfIrStop())
                {
                    return;
                }

                int r = getRadar(45);
                int l = getRadar(135);

                //Check what direction has maximum space available and turn here for a few time, then i will check if clear (on next loop)
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
        else //If no obstacle go forward
        {
            is_turning = false;
            if (checkIfIrStop())
            {
                return;
            }
            goForwardContinuosly(); //No time limit
        }
    }

    /*----- Final parking routine -----*/
    if (parking)
    {
        setSpeed(75);

        int a = 0;
        int b = 0;
        int c = 0;
        int d = 0;
        if (raddriz)
        {
            a = getRadarCostumDelay(0, DELAY_SERVO_PARK);
            b = getRadarCostumDelay(180, DELAY_SERVO_PARK);
            goBackward(200);
            c = getRadarCostumDelay(0, DELAY_SERVO_PARK);
            d = getRadarCostumDelay(180, DELAY_SERVO_PARK);
            Serial.print("a ");
            Serial.println(a);

            Serial.print("b ");
            Serial.println(b);
            Serial.print("c ");
            Serial.println(c);

            Serial.print("d ");
            Serial.println(d);
        }

        if (a - c < -5 && b - d > 5 && raddriz)
        {
            setSpeed(100);
            rotateRight(100);
        }
        else if (a - c > 5 && b - d < -5 && raddriz)
        {
            setSpeed(100);
            rotateLeft(100);
        }
        else
        {
            raddriz = false;
            goBackward(1200);

            int e = getRadarCostumDelay(180, DELAY_SERVO_PARK);
            if (e > 100)
            {
                goBackward(1000);
                rotateRight(200);
                goBackward(5000);
                parking = false;
                while (1) //After parking stop car -- our race is finished!
                {
                }
            }
            else
            {
                goBackward(200);
            }
        }
    }
}

/*----- Routine selection based on ir command -----*/
bool checkIfIrStop()
{
    if (checkIr())
    {
        if (is_moving && !parking) //After parking dont check ir anymnore
        {
            //STOP (END LAP)
            is_moving = false;
            parking = true;
            obstacle_found = false;
            is_turning = false;
            motorStop();
            Serial.println("IR Stop");
            return true;
        }
        else
        {
            //GO (START LAP)
            is_moving = true;
            Serial.println("IR Start");
            return false;
        }
    }
    return false;
}