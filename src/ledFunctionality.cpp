#include "LedRequest.h"
#include "esp_sys.h"
#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>
#include <Time.h>

// Define LEDs
#define DATA_PIN 5
#define COLOR_ORDER GRB
#define NUM_LEDS 15
#define LED_TYPE WS2812B
#define BRIGHTNESS 96
#define FRAMES_PER_SECOND 120

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;
bool Rainbow{false}, Blue{false}, Red{false}, Green{false}, Stop{false};

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
    Blue = false;
    Green = false;
    Red = false;
    Stop = true;
    Stop_light(); });
}

// Rainbow
void rainbow() {
    // FastLED's built-in rainbow generator
    fill_rainbow(leds, NUM_LEDS, gHue, 7);
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