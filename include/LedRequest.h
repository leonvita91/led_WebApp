#ifndef LED_functions_req
#define LED_functions_req
// include the necessary lib
#include <Arduino.h>
#include <WebServer.h>
#include <FastLED.h>

// Define LEDs
#define DATA_PIN 5
#define COLOR_ORDER GRB
#define NUM_LEDS 15
#define LED_TYPE WS2812B
#define BRIGHTNESS 96
#define FRAMES_PER_SECOND 120

// Declare variables as extern
extern CRGB leds[NUM_LEDS];
extern uint8_t gHue;
extern bool Rainbow,Blue,Red,Green,Stop;

// Declare LEDs Functions
void setup_LED();
void request_Rainbow(); void rainbow();
void request_Blue();    void Blue_light();
void request_Red();     void Red_light();
void request_Green();   void Green_light();
void request_Stop();    void Stop_light();
#endif