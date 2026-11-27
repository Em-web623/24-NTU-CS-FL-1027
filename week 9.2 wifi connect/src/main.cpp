// #include <Arduino.h>

// // put function declarations here:
// int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   int result = myFunction(2, 3);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }
#include <WiFi.h>

const char* ssid = "Khudaira's S26FE";
const char* password = "Abc*7736";

void setup() {

    Serial.begin(115200);

    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting...");
    }

    Serial.println("Connected!");

    Serial.println(WiFi.localIP());
}

void loop() {


}

