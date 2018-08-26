#ifndef GENERAL_H
#define GENERAL_H 1

#include "constants.h"
#include <ArduinoOTA.h>
#include "radio.h"
#include "mcp.h"
#include "blnk.h"
#include <time.h>

void setTimeVars();
void screenSaver();
void infoScreen(const char* line1, const char* line2);
void setValve(byte valve, bool on);
void valveStateChange(byte valve, bool on);
void virtualStateChange(byte virtualPin, bool on);

#endif