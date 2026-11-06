#include <Arduino.h>

#define DAC_PIN 25

void setup()
{
    Serial.begin(115200);
    Serial.println("ESP32 DAC Brightness Fade (Program 2)");
}

void loop()
{
    // Fade up from 0 (off) to 255 (maximum brightness)
    for (int i = 0; i <= 255; i++)
    {
        dacWrite(DAC_PIN, i);
        delay(10);
    }

    // Fade down from 255 (maximum brightness) to 0 (off)
    for (int i = 255; i >= 0; i--)
    {
        dacWrite(DAC_PIN, i);
        delay(25);
    }
}