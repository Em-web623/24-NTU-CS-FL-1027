#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2

hw_timer_t *debounceTimer = NULL;

volatile bool debounceActive = false;


// Button Interrupt
void IRAM_ATTR onButtonISR()
{
    if (!debounceActive)
    {
        debounceActive = true;

        // Reset timer
        timerWrite(debounceTimer, 0);

        // 50 ms timer
        timerAlarmWrite(debounceTimer, 50000, false);

        // Start timer
        timerAlarmEnable(debounceTimer);
    }
}


// Timer Interrupt
void IRAM_ATTR onDebounceTimer()
{
    if (digitalRead(BUTTON_PIN) == LOW)
    {
        // Valid button press
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }

    debounceActive = false;
}


void setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);

    // Timer frequency = 1 MHz
    // 80 MHz APB clock / 80 = 1 MHz
    debounceTimer = timerBegin(0, 80, true);

    // Attach timer interrupt
    timerAttachInterrupt(
        debounceTimer,
        &onDebounceTimer,
        true
    );

    // Set 50 ms alarm
    timerAlarmWrite(
        debounceTimer,
        50000,
        false
    );

    // Don't start timer here
    // It will start when button is pressed

    // Button interrupt
    attachInterrupt(
        digitalPinToInterrupt(BUTTON_PIN),
        onButtonISR,
        FALLING
    );
}


void loop()
{
    // Main application remains non-blocking
}