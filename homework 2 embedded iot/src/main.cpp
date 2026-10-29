#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define RED_LED 5
#define BLUE_LED 23

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

#define RED_CHANNEL 0
#define BLUE_CHANNEL 1

#define PWM_FREQUENCY 5000
#define PWM_RESOLUTION 8
#define PWM_MAX_DUTY 255

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

int redDuty = 0;
int blueDuty = 0;

void updateOLED()
{
    int redPercent = (redDuty * 100) / PWM_MAX_DUTY;
    int bluePercent = (blueDuty * 100) / PWM_MAX_DUTY;

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.println("PWM PARAMETERS");

    display.println("---------------------");

    display.setCursor(0, 20);
    display.print("RED: ");
    display.print(redPercent);
    display.println("%");

    display.print("Freq: ");
    display.print(PWM_FREQUENCY);
    display.println(" Hz");

    display.setCursor(0, 42);
    display.print("BLUE: ");
    display.print(bluePercent);
    display.println("%");

    display.print("Freq: ");
    display.print(PWM_FREQUENCY);
    display.println(" Hz");

    display.display();
}

void setup()
{
    Serial.begin(115200);

    Wire.begin();

    if (!display.begin(
            SSD1306_SWITCHCAPVCC,
            OLED_ADDRESS))
    {
        Serial.println("OLED initialization failed!");
        while (true)
        {
            delay(100);
        }
    }

    ledcSetup(RED_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(RED_LED, RED_CHANNEL);

    ledcSetup(BLUE_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(BLUE_LED, BLUE_CHANNEL);

    ledcWrite(RED_CHANNEL, 0);
    ledcWrite(BLUE_CHANNEL, 0);

    updateOLED();
}

void loop()
{
    // Both LEDs fade in
    for (int duty = 0; duty <= PWM_MAX_DUTY; duty++)
    {
        redDuty = duty;
        blueDuty = duty;

        ledcWrite(RED_CHANNEL, redDuty);
        ledcWrite(BLUE_CHANNEL, blueDuty);

        updateOLED();
        delay(10);
    }

    // Both LEDs fade out
    for (int duty = PWM_MAX_DUTY; duty >= 0; duty--)
    {
        redDuty = duty;
        blueDuty = duty;

        ledcWrite(RED_CHANNEL, redDuty);
        ledcWrite(BLUE_CHANNEL, blueDuty);

        updateOLED();
        delay(10);
    }
}

