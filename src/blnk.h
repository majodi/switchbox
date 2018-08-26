#ifndef BLNK_H
#define BLNK_H 1

#include "constants.h"
#include "menu.h"
#include "general.h"

void setupBlynk();
void blynkRun();
void setupTimers();
void timerRun();
void eachMinute();
void eachQuarter();
void eachHour();
float randomAdjustment();
void WriteSenserValues(char* values);

#endif