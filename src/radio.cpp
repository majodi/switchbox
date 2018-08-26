#include "radio.h"

void handleRadio() {
  // --- switch off interrupts ---
  // TODO
  // -----------------------------
  // --- show info screen ---
  // TODO
  // ------------------------
  while (radio.available()) {
    memset(inStr, 0, sizeof(inStr));
    radio.read(&inStr, sizeof(inStr));
    if(inStr[0] == 'S' && !firstPart) {
      memset(totalStr, 0, sizeof(totalStr));
      memcpy(totalStr, inStr + 1, strlen(inStr) - 1);
      firstPart = true;
      continue;
    }
    if(inStr[strlen(inStr)-1] == 'E' && firstPart) {
      strcat(totalStr, ", ");
      strcat(totalStr, inStr);
      totalStr[strlen(totalStr)-1] = 0;
      firstPart = false;
      WriteSenserValues(totalStr);
    }
    Serial.println("short delay now...");
    delay(1000); // give it some time to receive next part
  }
  // --- switch on interrupts ---
  // TODO
  // ----------------------------
}