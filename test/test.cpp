#include <Arduino.h>
#include "Apmode.h"
#include <unity.h>

void setup()
{
    pinMode(2,OUTPUT);
    ApMode ap("/wifi.cfg");

    ap.run();
}

void loop()
{

    digitalWrite(2, 1);
    delay(500);
    digitalWrite(2, 0);
    delay(500);
    Serial.println("test");
}