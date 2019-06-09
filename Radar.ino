#include "Arduino.h"
#include "conf.h"
#include <Servo.h> //Inserire la libreria Servo

Servo radar_servo; //Il nome del servo è Servo1

int angle = 0;
const int offset = 30;

bool increment = true;

int measure[180 / offset + 1];

int radar_zero_offset = RADAR_ZERO_OFFSET;

unsigned int last_read = 0;

void radarBegin()
{
    radar_servo.attach(RADAR_SERVO_PIN); //Il Servo1 è collegato al pin digitale
    pinMode(HC_TRIGGER, OUTPUT);
    pinMode(HC_ECHO, INPUT);
    radar_servo.write(0);
    delay(500);
}

int getRadar(int a)
{
    if (angle != a)
    {
        radar_servo.write(a + radar_zero_offset);
        angle = a;
        delay(200); //Was 300
    }

    return readDistance();
}

int getRadarCostumDelay(int a, int d)
{
    if (angle != a)
    {
        radar_servo.write(a + radar_zero_offset);
        angle = a;
        delay(d);
    }

    return readDistance();
}

int readDistance()
{
    int mes_read[3];
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(HC_TRIGGER, LOW);
        digitalWrite(HC_TRIGGER, HIGH);
        delayMicroseconds(10);
        digitalWrite(HC_TRIGGER, LOW);

        long durata = pulseIn(HC_ECHO, HIGH, MAX_DISTANCE_TIME); //TODO: Set max

        if (durata == 0)
        {
            mes_read[i] = 0.034 * MAX_DISTANCE_TIME / 2;
        }
        else
        {
            mes_read[i] = 0.034 * durata / 2;
        }
    }

    //Measure Smooth
    int a = abs(mes_read[1] - mes_read[0]);
    int b = abs(mes_read[2] - mes_read[1]);
    int c = abs(mes_read[2] - mes_read[0]);
    int min_off = min(a, min(b,c));
    if(min_off == a){
        return (mes_read[1] + mes_read[0])/2;
    }
    if (min_off == b)
    {
        return (mes_read[2] + mes_read[1]) / 2;
    }
    if (min_off == c)
    {
        return (mes_read[2] + mes_read[0]) / 2;
    }
}

/* 
void updateRadar()
{
    if (millis() - last_read > RADAR_REFRESH_RATE)
    {

        radar_servo.write(angle);
        //Serial.println(angle);
        delay(10);

        if (angle % offset == 0 || angle == 0)
        {
            // Serial.println("QUA");
            measure[angle / offset] = readDistance();
          
        }

        if (angle == 0)
        {
            increment = true;
        }
        else if (angle == 180)
        {
            increment = false;
        }

        if (increment)
        {
            angle++;
        }
        else
        {
            angle--;
        }

        last_read = millis();
    }
}*/

void calibra()
{
    radar_servo.write(90 + radar_zero_offset);
}