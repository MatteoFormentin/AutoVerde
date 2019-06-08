#include "Arduino.h"
#include "conf.h"

int v = 255;
int v_turn = 80;

/* 
    State:
    0-Off
    1-Forwardz<<
    2-Backward
    3-Left
    4-Right
*/
int state = 0;

void motor_begin()
{
    pinMode(RIGHT_IN1, OUTPUT);
    pinMode(RIGHT_IN2, OUTPUT);
    pinMode(LEFT_IN3, OUTPUT);
    pinMode(LEFT_IN4, OUTPUT);
    pinMode(RIGHT_PWM_ENA, OUTPUT);
    pinMode(LEFT_PWM_ENB, OUTPUT);
}

void setSpeed(int new_v)
{
    if (new_v > 255)
    {
        v = 255;
    }
    else if (new_v < 50)
    {
        v = 50;
    }
    else
    {
        v = new_v;
    }

    if (state != 0)
    {
        runMotor();
    }
}

//Update motor speed
void runMotor()
{
    if (state == 1 || state == 2)
    {
        analogWrite(RIGHT_PWM_ENA, v - COMP_SPEED_R);
        analogWrite(LEFT_PWM_ENB, v - COMP_SPEED_L);
    }
    else
    {
        analogWrite(RIGHT_PWM_ENA, v_turn);
        analogWrite(LEFT_PWM_ENB, v_turn);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    }
}

void motorStop()
{
    analogWrite(RIGHT_PWM_ENA, 0);
    analogWrite(LEFT_PWM_ENB, 0);
    state = 0;
}

void goBackward()
{
    digitalWrite(RIGHT_IN1, HIGH);
    digitalWrite(RIGHT_IN2, LOW);

    digitalWrite(LEFT_IN3, HIGH);
    digitalWrite(LEFT_IN4, LOW);
    state = 1;
    runMotor();
}

void goForward()
{
    Serial.println("going forward");
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, HIGH);

    digitalWrite(LEFT_IN3, LOW);
    digitalWrite(LEFT_IN4, HIGH);
    state = 2;
    runMotor();
}

void rotateRight()
{
    Serial.println("Going right");
    digitalWrite(RIGHT_IN1, HIGH);
    digitalWrite(RIGHT_IN2, LOW);

    digitalWrite(LEFT_IN3, LOW);
    digitalWrite(LEFT_IN4, HIGH);
    state = 3;
    runMotor();
}

void rotateLeft()
{
    Serial.println("going Left");
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, HIGH);

    digitalWrite(LEFT_IN3, HIGH);
    digitalWrite(LEFT_IN4, LOW);
    state = 4;
    runMotor();
}

int getState()
{
    return state;
}

int getSpeed()
{
    return map(v, 0, 255, 0, 100);
}