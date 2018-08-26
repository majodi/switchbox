#include "general.h"

void setTimeVars() {
  time_t now = time(nullptr);
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  thisMinute = timeinfo.tm_min;
  thisHour = timeinfo.tm_hour;
}

void screenSaver() {
  screenSaverActive = true;
  rotaryChange = false;
  char timeStr [6];
  u8g2.setFont(bigFont);
  u8g2.setDrawColor(2);
  while (!rotaryChange) {
    ArduinoOTA.handle();
    blynkRun();
    setTimeVars();
    sprintf (timeStr, "%02d:%02d", thisHour, thisMinute);
    int x = (int) random(80); int y = (int) random(40);
    u8g2.firstPage();
    do {
        u8g2.drawStr(x, y+30, timeStr);
    } while ( u8g2.nextPage() );
    delay(300);
    timerRun();
    Debug.handle();
  }
  screenSaverActive = false;
}

void infoScreen(const char* line1, const char* line2) {
  delay(100);
  reEnableRotary();
  u8g2.setFont(menuFont);
  u8g2.setDrawColor(2);
  int x = 1;
  while (!rotaryChange) {
    u8g2.firstPage();
    do {
      u8g2.drawStr(1, 30, line1);
      u8g2.drawStr(1, 45, line2);
      u8g2.drawStr(x, 60, "Knop voor menu");
    } while ( u8g2.nextPage() );
    delay(100);
    x = x > 10 ? 1 : x+1;
  }
}

void setValve(byte valve, bool on) {
  if (!on) {bitSet(valves, valve);} else {bitClear(valves, valve);}
  if (valves >=254) {bitSet(valves, 0);} else {bitClear(valves, 0);} // switch mains
}

void valveStateChange(byte valve, bool on) {
  switch(valve) {
    case 1: if (on) {
              menuMatrix[2][1] = "Achter (1): AAN";
              setValve(1, true);
            } else {
              menuMatrix[2][1] = "Achter (1): UIT";
              setValve(1, false);
            }
            break;
    case 2: if (on) {
              menuMatrix[2][2] = "Zijknt (2): AAN";
              setValve(2, true);
            } else {
              menuMatrix[2][2] = "Zijknt (2): UIT";
              setValve(2, false);
            }
            break;
    case 3: if (on) {
              menuMatrix[2][3] = "Voor   (3): AAN";
              setValve(3, true);
            } else {
              menuMatrix[2][3] = "Voor   (3): UIT";
              setValve(3, false);
            }
            break;
  }
  rotaryChange = true; // fake rotary change for menu refresh
}

void virtualStateChange(byte virtualPin, bool on) {
  switch(virtualPin) {
    case 4: if (on) {
              menuMatrix[1][1] = "Skip 1x   : AAN";
            } else {
              menuMatrix[1][1] = "Skip 1x   : UIT";
            }
            break;
    case 5: if (on) {
              menuMatrix[1][2] = "Forceer 1x: AAN";
            } else {
              menuMatrix[1][2] = "Forceer 1x: UIT";
            }
            break;
    case 6: if (on) {
              menuMatrix[1][3] = "Automaat  : AAN";
            } else {
              menuMatrix[1][3] = "Automaat  : UIT";
            }
            break;
  }
  rotaryChange = true; // fake rotary change for menu refresh
}
