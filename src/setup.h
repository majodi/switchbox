#ifndef SETUP_H
#define SETUP_H 1

#include "constants.h"
#include <ESP8266WiFi.h>
#include <DNSServer.h>           //needed for WiFiManager
#include <ESP8266WebServer.h>    //needed for WiFiManager
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
// #include <time.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ArduinoOTA.h>
#include "mcp.h"
#include "menu.h"
#include "blnk.h"
#include "general.h"
#include "radio.h"

// extern RemoteDebug Debug;

void setupPins();
void setupWiFi();
void setupTime();
void setupOTA();
void setupDebugOTA();
void setupRF24();
void setupMCP23017();
void setupDisplay();

#endif
