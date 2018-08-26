// todo
// andere toggles (app en mcu)
// screensaver

// skip timer event on screenSaverActive (restartTimer...)
// dummy graph

// advies op info screen
// timer logic voor full cycle
// ook reset cycle als handmatig en skip + forceer = start cycle
// cloud feeding met sensor values
// advies ophalen
// data snapshot voor app
// notification on cycle start en heart beat

#include "setup.h"

void executeAction();

void setup(void) {
  setupWiFi();
  setupTime();
  setupOTA();
  setupBlynk();
  setupDebugOTA();
  setupRF24();
  setupMCP23017();
  setupDisplay();
  setupTimers();
  // initial screens
  screenSaver();
  infoScreen("NickStick IoT 2018", "SwitchBox v0.2");
  rotaryPushed = false; rotaryVirtual = 0; // loose pushes and rotates before setting menu
  setMenuState();
  drawMenu();
  reEnableRotary();
}

void loop(void) {
  ArduinoOTA.handle();
  blynkRun();
  if (rotaryChange) {
    userActivity = true;
    setMenuState();
    executeAction();
    drawMenu();
    reEnableRotary();
  }
  delay(100);
  timerRun();
  Debug.handle();
}

void executeAction() {
  // DEBUG_V("action: %d\n", action);
  if (action) {
    DEBUG_V("case: %d\n", menuTopPos*100 + action);
    switch(menuTopPos*100 + action) {
      case 1:   if (strcmp(menuMatrix[1][1], "Skip 1x   : AAN") == 0) {
                  menuMatrix[1][1] = "Skip 1x   : UIT";
                } else {
                  menuMatrix[1][1] = "Skip 1x   : AAN";
                }
                menuActive = 1; menuLastActive = 1;
                restoreMenuBeforePush();
                break;
      case 2:   if (strcmp(menuMatrix[1][2], "Forceer 1x: AAN") == 0) {
                  menuMatrix[1][2] = "Forceer 1x: UIT";
                } else {
                  menuMatrix[1][2] = "Forceer 1x: AAN";
                }
                menuActive = 1; menuLastActive = 1;
                restoreMenuBeforePush();
                break;
      case 3:   if (strcmp(menuMatrix[1][3], "Automaat  : AAN") == 0) {
                  menuMatrix[1][3] = "Automaat  : UIT";
                } else {
                  menuMatrix[1][3] = "Automaat  : AAN";
                }
                menuActive = 1; menuLastActive = 1;
                restoreMenuBeforePush();
                break;
      case 101: if (strcmp(menuMatrix[2][1], "Achter (1): AAN") == 0) {
                  valveStateChange(1, false);
                } else {
                  valveStateChange(1, true);
                }
                menuActive = 1; menuLastActive = 1;
                restoreMenuBeforePush();
                break;
      case 102: if (strcmp(menuMatrix[2][2], "Zijknt (2): AAN") == 0) {
                  valveStateChange(2, false);
                } else {
                  valveStateChange(2, true);
                }
                menuActive = 1; menuLastActive = 1;
                restoreMenuBeforePush();
                break;
      case 103: if (strcmp(menuMatrix[2][3], "Voor   (3): AAN") == 0) {
                  valveStateChange(3, false);
                } else {
                  valveStateChange(3, true);
                }
                menuActive = 1; menuLastActive = 1;
                restoreMenuBeforePush();
                break;
      case 201: reEnableRotary(); // first (re)arm rotary
                infoScreen("IP address:", ipCstring);
                rotaryPushed = false; rotaryVirtual = 0; // loose pushes and rotates before setting menu
                break;
      case 202: WiFi.disconnect();
                break;
      default:  DEBUG_V("undefined action?\n");
    }
  }
}
