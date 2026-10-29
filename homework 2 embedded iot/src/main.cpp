#include <Arduino.h>

constexpr uint8_t RED_LED = 5;
constexpr uint8_t BLUE_LED = 23;

constexpr uint32_t PWM_FREQUENCY = 5000;
constexpr uint8_t PWM_RESOLUTION = 8;
constexpr uint16_t PWM_MAX_DUTY = 255;

void setup()
{
    Serial.begin(115200);

    ledcSetup(0, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(RED_LED, 0);

    ledcSetup(1, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(BLUE_LED, 1);

    ledcWrite(0, 0);
    ledcWrite(1, 0);
}


void loop()
{
    // Dono LEDs ek saath bright hongi
    for (int duty = 0; duty <= 255; duty++)
    {
        ledcWrite(0, duty);  // Red LED
        ledcWrite(1, duty);  // Blue LED
        delay(10);
    }

    // Dono LEDs ek saath dim hongi
    for (int duty = 255; duty >= 0; duty--)
    {
        ledcWrite(0, duty);  // Red LED
        ledcWrite(1, duty);  // Blue LED
        delay(10);
    }
}


// #include <Arduino.h>

// constexpr uint8_t LED_PIN = 2;
// constexpr uint32_t PWM_FREQUENCY = 5000;
// constexpr uint8_t PWM_RESOLUTION = 8;
// constexpr uint16_t PWM_MAX_DUTY = 255;

// void setup()
// {
//     Serial.begin(115200);

//     ledcSetup(0, PWM_FREQUENCY, PWM_RESOLUTION);
//     ledcAttachPin(LED_PIN, 0);

//     ledcWrite(0, 0);

//     Serial.println("ESP32 PWM LED Fade Started");
// }

// void loop()
// {
//     for (int duty = 0; duty <= PWM_MAX_DUTY; duty++)
//     {
//         ledcWrite(0, duty);
//         delay(10);
//     }

//     for (int duty = PWM_MAX_DUTY; duty >= 0; duty--)
//     {
//         ledcWrite(0, duty);
//         delay(10);
//     }
// }