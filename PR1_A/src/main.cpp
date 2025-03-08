#include <Arduino.h>

#define LED_BUILTIN 21

unsigned long previousMillis = 0;
const long interval = 1000;
bool ledState = false;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState);
        Serial.println(ledState ? "ON" : "OFF");
    }
}