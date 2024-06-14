#include "LedRequest.h"
#include "esp_sys.h"
#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>
#include <Time.h>

int FRAMES_PER_SECOND = 1;
int BRIGHTNESS = 10;

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;
bool Stop{false}, Rainbow{false}, Race{false}, Crisscross{false}, Blue{false}, Red{false}, Green{false};

// LED Setup
void setup_LED()
{
    // Tell FastLED about the LED strip configuration
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    // Set master brightness control
    FastLED.setBrightness(BRIGHTNESS);
}

// Stop Light
void Stop_light()
{
    // Set all LEDs to Black
    fill_solid(leds, NUM_LEDS, CRGB::Black);
}
// LED HTTP Requests
void request_Stop()
{
    // Request LED
    server.on("/stop-light", HTTP_POST, []()
            { server.send(200, "text/plain");
    Rainbow = false;
    Race = false;
    Blue = false;
    Green = false;
    Red = false;
    Stop = true;
    Stop_light(); });
}

// Control Brightness
void Bright_light(){
    server.on("/brightness", HTTP_GET, []() {
        if (server.hasArg("value")) {
            int newBrightness = server.arg("value").toInt();
            FastLED.setBrightness(newBrightness);
        }
        server.send(200, "text/plain", "OK"); });
}

// Frames Control
void Frames_Control(){
server.on("/set-frames", HTTP_GET, []() {
if (server.hasArg("value")) {
    FRAMES_PER_SECOND = server.arg("value").toInt();
    Serial.print("Received value: ");
    Serial.println(FRAMES_PER_SECOND);
}
server.send(200, "text/plain", "OK"); });

}

// Blue Light
void Blue_light() {
    // Set all LEDs to blue
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
}
// LED HTTP Requests
void request_Blue() {
    // Request LED
    server.on("/blue-light", HTTP_POST, []()
            { server.send(200, "text/plain");
    Stop = false;
    Rainbow = false;
    Blue = true;
    Green = false;
    Red = false;
    Blue_light(); });
}

// Red Light
void Red_light() {
    // Set all LEDs to Red
    fill_solid(leds, NUM_LEDS, CRGB::Red);
}
// LED HTTP Requests
void request_Red() {
    // Request LED
    server.on("/red-light", HTTP_POST, []()
        { server.send(200, "text/plain");
    Stop = false;
    Rainbow = false;
    Blue = false;
    Green = false;
    Red = true;
    Red_light(); });
}

// Green Light
void Green_light() {
    // Set all LEDs to Green
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
}
// LED HTTP Requests
void request_Green() {
    // Request LED
    server.on("/green-light", HTTP_POST, []()
        { server.send(200, "text/plain");
    Stop = false;
    Rainbow = false;
    Blue = false;
    Green = true;
    Red = false;
    Green_light(); });
}

// Animations Section

// Rainbow
void rainbow() {
    fill_rainbow(leds, NUM_LEDS, gHue, 7);
    EVERY_N_MILLISECONDS(FRAMES_PER_SECOND) { gHue++; }
    FastLED.delay(50 / FRAMES_PER_SECOND);
}
// LED HTTP Requests
void request_Rainbow()
{
    // Request LED Functionallty
    server.on("/rainbow-light", HTTP_POST, []()
            { server.send(200, "text/plain");
    Stop = false;
    Rainbow = true;
    Blue = false;
    Green = false;
    Red = false;
    rainbow(); });
}

// Race
void race()
{
    static int ledIndex = 0;
    static unsigned long previousMillis = 0;

    if (millis() - previousMillis >= FRAMES_PER_SECOND)
    {
        previousMillis = millis();
        leds[ledIndex] = CRGB::Black;
        ledIndex = (ledIndex + 1) % NUM_LEDS;
        leds[ledIndex] = CRGB::BlueViolet;
        FastLED.show();
    }
}
// LED HTTP Requests
void request_Race()
{
    // Request LED Functionallty
    server.on("/race-light", HTTP_POST, []()
            { server.send(200, "text/plain");
    Stop = false;
    Rainbow = false;
    Race = true;
    Blue = false;
    Green = false;
    Red = false;
    race(); });
}

// Race
void crisscross()
{
    static int ledIndex_First = 0;
    static int ledIndex_Sec = 0;
    static unsigned long previousMillis_First = 0;
    static unsigned long previousMillis_Sec = 0;
    long timeStamp = millis();

    if (timeStamp - previousMillis_First >= FRAMES_PER_SECOND)
    {
        previousMillis_First = timeStamp;
        ledIndex_First = (ledIndex_First - 1 + 32) % 32;
        leds[ledIndex_First] = CRGB::BlueViolet;
        ledIndex_Sec = (ledIndex_Sec + 1) % 32;
        leds[ledIndex_Sec] = CRGB::Blue;
        FastLED.show();
    }
}
// LED HTTP Requests
void request_crisscross()
{
    // Request LED Functionallty
    server.on("/race-light", HTTP_POST, []()
            { server.send(200, "text/plain");
    Stop = false;
    Rainbow = false;
    Race = true;
    Blue = false;
    Green = false;
    Red = false;
    crisscross; });
}