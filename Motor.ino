#include "Arduino.h"
#include "conf.h"

int v = V_NORMAL;
int v_turn = V_TURN;

/* 
    State:
    0-Off
    1-Backward<<
    2-Forward
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

//Update motor speed
void runMotor(int t)
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
    delay(t);
    motorStop();
}

void motorStop()
{
    analogWrite(RIGHT_PWM_ENA, 0);
    analogWrite(LEFT_PWM_ENB, 0);
    state = 0;
    Serial.println("Stop");
}

void goBackward(int t)
{
    digitalWrite(RIGHT_IN1, HIGH);
    digitalWrite(RIGHT_IN2, LOW);

    digitalWrite(LEFT_IN3, HIGH);
    digitalWrite(LEFT_IN4, LOW);
    state = 1;
    runMotor(t);
}

void goForward(int t)
{
    Serial.println("going forward");
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, HIGH);

    digitalWrite(LEFT_IN3, LOW);
    digitalWrite(LEFT_IN4, HIGH);
    state = 2;
    runMotor(t);
}

void goForwardContinuosly()
{
    Serial.println("going forward");
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, HIGH);

    digitalWrite(LEFT_IN3, LOW);
    digitalWrite(LEFT_IN4, HIGH);
    state = 2;
    analogWrite(RIGHT_PWM_ENA, v - COMP_SPEED_R);
    analogWrite(LEFT_PWM_ENB, v - COMP_SPEED_L);
}

void rotateLeft(int t)
{
    Serial.println("Going left");
    digitalWrite(RIGHT_IN1, HIGH);
    digitalWrite(RIGHT_IN2, LOW);

    digitalWrite(LEFT_IN3, LOW);
    digitalWrite(LEFT_IN4, HIGH);
    state = 3;
    runMotor(t);
}

void rotateRight(int t)
{
    Serial.println("going Right");
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, HIGH);

    digitalWrite(LEFT_IN3, HIGH);
    digitalWrite(LEFT_IN4, LOW);
    state = 4;
    runMotor(t);
}

int getState()
{
    return state;
}