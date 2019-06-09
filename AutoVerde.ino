#include "Arduino.h"

void setup()
{
    //Serial.begin(9600);
    //calibra();

    radarBegin();
    motor_begin();
    beginIr();
    //rotateRight(100000);
}

void loop()
{
    go();
    //Serial.println(checkIr());
    /* Serial.println(readDistance());
    delay(1000);*/
}



/* 
void test()
{
    goForward();
    delay(1000);
    rotateLeft();
    delay(1000);
    rotateRight();
    delay(1000);

    Serial.print("30: ");
    Serial.println(getRadar(30));
    delay(10);

    Serial.print("60: ");
    Serial.println(getRadar(60));
    delay(10);

    Serial.print("90: ");
    Serial.println(getRadar(90));
    delay(10);

    Serial.print("120: ");
    Serial.println(getRadar(120));
    delay(10);

    Serial.print("150: ");
    Serial.println(getRadar(150));
    delay(10);

    Serial.println();
}*/