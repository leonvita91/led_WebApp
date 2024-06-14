#include "LedRequest.h"
#include "credentials.h"
#include "esp_sys.h"
#include <Arduino.h>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <Time.h>
#include <esp_task_wdt.h>
#include <esp32/rom/ets_sys.h>
#include "driver/temp_sensor.h"
#include <WireGuard-ESP32.h>
#include <FastLED.h>

void setup()
  {
    Serial.begin(115200);
    // Connect to Wi-Fi
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    // Wait for the Connection to Establish
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
      // IF the Connection not Established it will reboot the ESP32
      Serial.println("Connection Failed! Rebooting...");
      delay(5000);
      ESP.restart();
    }
    Serial.println("\nWiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    // Adjust system time
    Serial.println("Adjusting system time...");
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    setenv("TZ", "GMT0BST,M3.5.0/1,M10.5.0/2", 1); // Set timezone to UK (GMT or BST)
    while (!time(nullptr))
    {
      Serial.println("Waiting for time to be set...");
    }
    delay(3000);
    time_t now = time(nullptr);
    Serial.print("Current time: ");
    Serial.println(ctime(&now));

    // OTA Fire Connection
    ArduinoOTA.begin();
    
    // VPN Fire Connection
    wg.begin(local_ip, private_key, endpoint_address, public_key, endpoint_port);
    Serial.println("VPN Connected");

    // Start web server
    if (!SPIFFS.begin(true))
    {
      Serial.println("An error occurred while mounting SPIFFS");
      return;
    }
    Serial.println("SPIFFS mounted successfully");

    // Route setup
    server.on("/", HTTP_GET, handleRoot);

    // searching for CSS
    server.onNotFound(handleNotFound);

    // ESP temperature
    server.on("/esp_temp", HTTP_GET, []() {
    int temperature = readTemperature();
    server.send(200, "text/plain", String(temperature)); });
    
    // ESP CPU
    server.on("/esp_cpu", HTTP_GET, []() {
    int cpu = getCpuUsage();
    server.send(200, "text/plain", String(cpu)); });

    // Call LED setup 
    setup_LED();
    // Initialize LED strip state to off
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.clear();
    FastLED.show();
    // Call LED Request
    request_Stop();
    Bright_light();
    Frames_Control();
    request_Blue();
    request_Red();
    request_Green();
    // Request Ainmations
    request_Rainbow();
    request_Race();

    // Start Web-server
    server.begin();
    Serial.println("Server started");

    // Call Configure the Temp sensor
    configureTemperatureSensor();

  }

void loop() {
    // Handel OTA Connection
    ArduinoOTA.handle();
    // Handel WebServer Clients
    server.handleClient();
    // Looping the LEDs
    if (Stop) {
      Stop_light();
      FastLED.clear();
      FastLED.show();
      FastLED.delay(50);
    }

    // Brightness
    
    if (Rainbow) {
      rainbow();
      FastLED.show();
    }
    
    if (Blue) {
      Blue_light();
      FastLED.show();
    }

    if (Red) {
      Red_light();
      FastLED.show();
    }
    
    if (Green) {
      Green_light();
    }

    if (Race) {
      race();
    }
  }
