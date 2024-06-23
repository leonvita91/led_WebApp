#include "LedRequest.h"
#include "esp_sys.h"
#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>
#include <Time.h>

int FRAMES_PER_SECOND = 1;
int BRIGHTNESS = 50;

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;
bool Stop{false}, Rainbow{false}, Race{false}, Crisscross{false}, Water{false}, Dancing{false}, Blue{false}, Red{false}, Green{false};

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
        Crisscross = false;
        Water = false;
        Dancing = false;
        Blue = false;
        Green = false;
        Red = false;
        Stop = true;
        Stop_light(); });
}

// Control Brightness
void Bright_light()
{
    server.on("/brightness", HTTP_GET, []() {
        if (server.hasArg("value")) {
            int newBrightness = server.arg("value").toInt();
            FastLED.setBrightness(newBrightness);
        }
        server.send(200, "text/plain", "OK"); });
}

// Frames Control
void Frames_Control()
{
    server.on("/set-frames", HTTP_GET, []() {
        if (server.hasArg("value")) {
            FRAMES_PER_SECOND = server.arg("value").toInt();
            Serial.print("Received value: ");
            Serial.println(FRAMES_PER_SECOND);
    }
server.send(200, "text/plain", "OK"); });
}

// Blue Light
void Blue_light()
{
    // Set all LEDs to blue
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
}
// LED HTTP Requests
void request_Blue()
{
    // Request LED
    server.on("/blue-light", HTTP_POST, []()
        { server.send(200, "text/plain");
        Stop = false;
        Rainbow = false;
        Race = false;
        Crisscross = false;
        Water = false;
        Dancing = false;
        Blue = true;
        Green = false;
        Red = false;
        Blue_light(); });
}

// Red Light
void Red_light()
{
    // Set all LEDs to Red
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
}
// LED HTTP Requests
void request_Red()
{
    // Request LED
    server.on("/red-light", HTTP_POST, []()
        { server.send(200, "text/plain");
        Stop = false;
        Rainbow = false;
        Race = false;
        Crisscross = false;
        Water = false;
        Dancing = false;
        Blue = false;
        Green = false;
        Red = true;
        Red_light(); });
}

// Green Light
void Green_light()
{
    // Set all LEDs to Green
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    FastLED.show();
}
// LED HTTP Requests
void request_Green()
{
    // Request LED
    server.on("/green-light", HTTP_POST, []()
        { server.send(200, "text/plain");
        Stop = false;
        Rainbow = false;
        Race = false;
        Crisscross = false;
        Water = false;
        Dancing = false;
        Blue = false;
        Green = true;
        Red = false;
        Green_light(); });
}

// Animations Section
// Rainbow
void rainbow()
{
    fill_rainbow(leds, NUM_LEDS, gHue, 7);
    EVERY_N_MILLISECONDS(FRAMES_PER_SECOND) { gHue++; }
    FastLED.delay(120 / FRAMES_PER_SECOND);
}
// LED HTTP Requests
void request_Rainbow()
{
    // Request LED Functionallty
    server.on("/rainbow-light", HTTP_POST, []()
        { server.send(200, "text/plain");
        Stop = false;
        Rainbow = true;
        Race = false;
        Crisscross = false;
        Water = false;
        Dancing = false;
        Blue = false;
        Green = false;
        Red = false;
        rainbow(); });
}

void race() {
    
    //  RACE
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
        Crisscross = false;
        Water = false;
        Dancing = false;
        Blue = false;
        Green = false;
        Red = false;
        race(); });
}

// Crisscroos
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
    server.on("/cross-light", HTTP_POST, []()
        { server.send(200, "text/plain");
        Stop = false;
        Rainbow = false;
        Race = false;
        Crisscross = true;
        Water = false;
        Dancing = false;
        Blue = false;
        Green = false;
        Red = false;
        crisscross(); 
        });
}

// // Define GRADIENT Setup
// uint8_t palette_Index[NUM_LEDS];
// DEFINE_GRADIENT_PALETTE(heatmap_gp){
//     0,   0,  255, 245,
//     46,  0,  21,  255,
//     179, 12, 250,   0,
//     255, 0,  255, 245
// };

// Water
uint8_t palette_Index[NUM_LEDS];
DEFINE_GRADIENT_PALETTE(heatmap_gp){
    0, 0, 255, 245,
    46, 0, 21, 255,
    179, 12, 250, 0,
    255, 0, 255, 245};
CRGBPalette16 water = heatmap_gp;

void call_first()
{
    // Define GRADIENT Setup
    for (int i = 0; i < NUM_LEDS; i++)
    {
        palette_Index[i] = random8();
    }
}
// NEED TO BE FIXED :D §§§
void water_light(){
    // Water
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = ColorFromPalette(water, palette_Index[i]);
    }
    FastLED.show();
    EVERY_N_MILLISECONDS(FRAMES_PER_SECOND)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            palette_Index[i]++;
        }
    }
    FastLED.delay(120 / FRAMES_PER_SECOND);
}

// LED HTTP Requests
void request_water()
{
    // Request LED Functionallty
    server.on("/water-light", HTTP_POST, []()
            { server.send(200, "text/plain");
        Stop = false;
        Rainbow = false;
        Race = false;
        Crisscross = false;
        Water = true;
        Dancing = false;
        Blue = false;
        Green = false;
        Red = false;
        water_light(); });
}

//  Dancing LED
void dancing(){
    // Waves for LED position
    // Control the BPM by changing Number 20 20 20 20
    uint8_t posBeat = beatsin8(20, 0, NUM_LEDS - 1, 0, 0);
    uint8_t posBeat2 = beatsin8(20, 0, NUM_LEDS - 1, 0, 0);
    uint8_t posBeat3 = beatsin16(20, 0, NUM_LEDS - 1, 0, 127);
    uint8_t posBeat4 = beatsin16(20, 0, NUM_LEDS - 1, 0, 127);

    // In the video I use beatsin8 for the positions. For longer strips,
    // the resolution isn't high enough for position and can lead to some
    // LEDs not lighting. If this is the case, use the 16 bit versions below
    // uint16_t posBeat  = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);
    // uint16_t posBeat2 = beatsin16(60, 0, NUM_LEDS - 1, 0, 0);
    // uint16_t posBeat3 = beatsin16(30, 0, NUM_LEDS - 1, 0, 32767);
    // uint16_t posBeat4 = beatsin16(60, 0, NUM_LEDS - 1, 0, 32767);

    // Wave for LED color
    uint8_t colBeat = beatsin8(45, 0, 255, 0, 0);

    leds[(posBeat + posBeat2) / 2] = CHSV(colBeat, 255, 255);
    leds[(posBeat3 + posBeat4) / 2] = CHSV(colBeat, 255, 255);
    fadeToBlackBy(leds, NUM_LEDS, 6);
    FastLED.show();
}

// LED HTTP Requests
void request_dancing() {
    // Request LED Functionallty
    server.on("/dancing-light", HTTP_POST, []()
        { server.send(200, "text/plain");
        Stop = false;
        Rainbow = false;
        Race = false;
        Crisscross = true;
        Water = false;
        Dancing = true;
        Blue = false;
        Green = false;
        Red = false;
        dancing(); 
        });
}

// GRADIENTS SECTION

// Define GRADIENT Setup
// uint8_t palette_Index = 0;
// DEFINE_GRADIENT_PALETTE(heatmap_gp){
//     0, 0, 0, 0,
//     128, 255, 0, 0,
//     200, 255, 255, 0,
//     255, 255, 255, 255};

// // GRADIENT
// void gradient() {
//     CRGBPalette16 mypal = heatmap_gp;
//     fill_palette(leds, NUM_LEDS, palette_Index, 255 / NUM_LEDS, mypal, BRIGHTNESS, LINEARBLEND);
//     FastLED.show();
//     EVERY_N_MILLISECONDS(FRAMES_PER_SECOND) {
//         palette_Index++;
//     }
//     FastLED.delay(120 / FRAMES_PER_SECOND);
// }
// // LED HTTP Requests
// void request_Gradient() {
//     // Request LED Functionallty
//     server.on("/gradient-light", HTTP_POST, []()
//             { server.send(200, "text/plain");
//         Stop = false;
//         Rainbow = false;
//         Race = false;
//         Crisscross = false;
//         Gradient = true;
//         Blue = false;
//         Green = false;
//         Red = false;
//         gradient(); });
// }