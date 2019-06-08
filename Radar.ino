#include "Arduino.h"
#include "conf.h"

int measure[3];

unsigned int last_read = 0;

void radarBegin()
{
    pinMode(HC_TRIGGER_RIGHT, OUTPUT);
    pinMode(HC_ECHO_RIGHT, INPUT);

    pinMode(HC_TRIGGER_CENTER, OUTPUT);
    pinMode(HC_ECHO_CENTER, INPUT);

    pinMode(HC_TRIGGER_LEFT, OUTPUT);
    pinMode(HC_ECHO_LEFT, INPUT);

    delay(500);
}

void updateRadar()
{
    if (millis() - last_read > RADAR_REFRESH_RATE)
    {
        measure[0] = readDistance(HC_TRIGGER_RIGHT, HC_ECHO_RIGHT);
        measure[1] = readDistance(HC_TRIGGER_CENTER, HC_ECHO_CENTER);
        measure[2] = readDistance(HC_TRIGGER_LEFT, HC_ECHO_LEFT);

        last_read = millis();
    }
}

int readDistance(int trigger_pin, int echo_pin)
{
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);

    long durata = pulseIn(echo_pin, HIGH, 6000);
    long distanza = 0.034 * durata / 2;

    if (distanza > 100 || distanza == 0)
    {
        distanza = 100;
    }

    return distanza;
}

int *getMeasure()
{
    return measure;
}