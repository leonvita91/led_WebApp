#include "LedRequest.h"
#include "esp_sys.h"
#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>
#include <Time.h>

int FRAMES_PER_SECOND = 20;
int BRIGHTNESS = 10;

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;
bool Stop{false}, Rainbow{false}, Blue{false}, Red{false}, Green{false};

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

// Rainbow
void rainbow() {
    // FastLED's built-in rainbow generator
    // fill_rainbow(leds, NUM_LEDS, gHue, 7); // Run Rainbow
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)

    // Run dancing
    // uint8_t BeatsPerMinute = 62;
    // CRGBPalette16 palette = PartyColors_p;
    // uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    // for (int i = 0; i < NUM_LEDS; i++)
    // { // 9948
    //     leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    // }
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy(leds, NUM_LEDS, 20);
    int pos = beatsin16(FRAMES_PER_SECOND, 0, NUM_LEDS - 1);
    leds[pos] += CHSV(gHue, 255, 192);
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

// // Slider Frames

// void Frames_Control(){
//     // Slider function
//     server.on("/set-frames", HTTP_GET, []() {
//     if (server.hasArg("value")) {
//         FRAMES_PER_SECOND = server.arg("value").toInt();
//         Serial.print("Received value: ");
//         Rainbow = false;
//         Rainbow = true;
//         Serial.println(FRAMES_PER_SECOND);
//     }
//     server.send(200, "text/plain", "OK"); });
// }