#ifndef LED_functions_req
#define LED_functions_req
// include the necessary lib
#include <Arduino.h>
#include <WebServer.h>
#include <FastLED.h>

// Define LEDs
#define DATA_PIN 5
#define COLOR_ORDER GRB
#define NUM_LEDS 34
#define LED_TYPE WS2812B

extern int FRAMES_PER_SECOND;
extern int BRIGHTNESS;

// Declare variables as extern
extern CRGB leds[NUM_LEDS];
extern uint8_t gHue;
extern bool Stop, Frames, Rainbow, Race, Crisscross, Blue, Red, Green;

// Declare LEDs Functions
void setup_LED();
void request_Blue();        void Blue_light();
void request_Red();         void Red_light();
void request_Green();       void Green_light();
void request_Stop();        void Stop_light();
void Frames_Control();      void Bright_light();
// Ainmations
void request_Rainbow();     void rainbow();
void request_Race();        void race();
void request_crisscross();  void crisscross();

#endif