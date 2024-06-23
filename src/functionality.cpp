#include "esp_sys.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <Time.h>
#include <esp_task_wdt.h>
#include <esp32/rom/ets_sys.h>
#include "driver/temp_sensor.h"
#include <WireGuard-ESP32.h>
#include <FastLED.h>

WebServer server(80);
// Define Functions
void handleRoot()
{
    File file = SPIFFS.open("/index.html", "r");
    if (!file)
    {
        server.send(500, "text/plain", "Failed to load /index.html");
        return;
    }
    server.streamFile(file, "text/html");
    file.close();
}

void serveCSS(String path)
{
    File file = SPIFFS.open(path, "r");
    if (!file)
    {
        server.send(404, "text/plain", "404: CSS File Not Found");
        return;
    }
    server.streamFile(file, "text/css");
    file.close();
}

void serveJS(String path)
{
    File file = SPIFFS.open(path, "r");
    if (!file)
    {
        server.send(404, "text/plain", "404: JavaScript File Not Found");
        return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
}

void handleNotFound()
{
    String path = server.uri();
    if (path.endsWith(".css"))
    {
        serveCSS(path);
        return;
    }
    else if (path.endsWith(".js"))
    {
        serveJS(path);
        return;
    }
    server.send(404, "text/plain", "404: Not Found");
}

// CPU Reading prop
int getCpuUsage()
{
    uint8_t cpuUsage = uxTaskGetStackHighWaterMark(NULL);
    cpuUsage = (100 - cpuUsage);
    return cpuUsage;
}

// Reading Temprture
void configureTemperatureSensor()
{
    temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
    temp_sensor.dac_offset = TSENS_DAC_L2; // TSENS_DAC_L2 is default; L4(-40°C ~ 20°C), L2(-10°C ~ 80°C), L1(20°C ~ 100°C), L0(50°C ~ 125°C)
    temp_sensor_set_config(temp_sensor);
    temp_sensor_start();
}

// floting the temp function
float readTemperature()
{
    temp_sensor_start();
    float result = 0;
    temp_sensor_read_celsius(&result);
    return result;
}