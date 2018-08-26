#include "Blnk.h"
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;

void setupBlynk() {
      Blynk.config(blynkAuth);
}

void blynkRun() {
    Blynk.run();
}

void setupTimers() {
    minuteTimer = timer.setInterval(60*1000L, eachMinute);
}

void timerRun() {
    timer.run();
}

void eachMinute() {
    if (!userActivity && !screenSaverActive) {
        screenSaver();
        rotaryPushed = false; rotaryVirtual = 0; // loose pushes and rotates before setting menu
        setMenuState();
        drawMenu();
        reEnableRotary();
    }
    handleRadio();
    userActivity = false;
}

void eachQuarter() {}

void eachHour() {}

float randomAdjustment() {
    float adj1 = random(1000)/1000.0;
    float adj2 = random(1000)/1000.0;
    return adj1 - adj2;
}

void WriteSenserValues(char* values) {
  char *token = strtok(values, ",");
  if (token != NULL) {
    float floatValue = strtof(token, NULL);
    Serial.print("Hum: ");
    Serial.println(floatValue);
    // Blynk.virtualWrite(Vx, token); not written
  } else {return;}
  token = strtok(NULL, ",");
  if (token != NULL) {
    Serial.print("Temp: ");
    Serial.println(strtof(token, NULL));
    Blynk.virtualWrite(V7, strtof(token, NULL));
  } else {return;}
  token = strtok(NULL, ",");
  if (token != NULL) {
    Serial.print("Sun: ");
    Serial.println(strtof(token, NULL));
    Blynk.virtualWrite(V8, strtof(token, NULL));
  } else {return;}
  token = strtok(NULL, ",");
  if (token != NULL) {
    Serial.print("Press: ");
    Serial.println(strtof(token, NULL));
    Blynk.virtualWrite(V9, strtof(token, NULL));
  } else {return;}
  token = strtok(NULL, ",");
  if (token != NULL) {
    Serial.print("Rain: ");
    Serial.println(strtof(token, NULL));
    Blynk.virtualWrite(V10, strtof(token, NULL));
  }
}

BLYNK_WRITE(V1)
{   
  int value = param.asInt(); // Get value as integer
  // DEBUG_V("V1 asInt: %d\n", value);
  if (value == 0) {valveStateChange(1, false);} else {valveStateChange(1, true);}
}

BLYNK_WRITE(V2)
{   
  int value = param.asInt(); // Get value as integer
  if (value == 0) {valveStateChange(2, false);} else {valveStateChange(2, true);}
}

BLYNK_WRITE(V3)
{   
  int value = param.asInt(); // Get value as integer
  if (value == 0) {valveStateChange(3, false);} else {valveStateChange(3, true);}
}

BLYNK_WRITE(V4)
{   
  int value = param.asInt(); // Get value as integer
  if (value == 0) {virtualStateChange(4, false);} else {virtualStateChange(4, true);}
}

BLYNK_WRITE(V5)
{   
  int value = param.asInt(); // Get value as integer
  if (value == 0) {virtualStateChange(5, false);} else {virtualStateChange(5, true);}
}

BLYNK_WRITE(V6)
{   
  int value = param.asInt(); // Get value as integer
  if (value == 0) {virtualStateChange(6, false);} else {virtualStateChange(6, true);}
}
