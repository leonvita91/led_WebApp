#ifndef System_Functionality
#define System_Functionality
// include the necessary lib
#include <Arduino.h>
#include <WebServer.h>
// Declare this Var as Global
extern WebServer server;

// Declare web functions
void handleRoot();
void serveCSS(String path);
void serveJS(String path);
void handleNotFound();

// Declare sys functions
void configureTemperatureSensor();
float readTemperature();
int getCpuUsage();

#endif