#include "setup.h"

void setupPins() {
  // pinMode(PinA, INPUT_PULLUP);
  // pinMode(PinB, INPUT_PULLUP);
  // pinMode(PinSW, INPUT);
  // pinMode(PinLED, OUTPUT);
  // attachInterrupt(digitalPinToInterrupt(PinA), isrRotaryDial, FALLING);
  // attachInterrupt(digitalPinToInterrupt(PinSW), isrRotarySwitch, FALLING);
}

void setupWiFi() {
  Serial.begin(115200);
  wifiManager.autoConnect("NickStickIoT");
  IPAddress ip = WiFi.localIP();
  utoa(ip[0], ipCstring, 10);
  for (byte octetCounter = 1; octetCounter < 4; ++octetCounter) {
    strcat(ipCstring, ".");
    char octetCstring[4];
    utoa(ip[octetCounter], octetCstring, 10);
    strcat(ipCstring, octetCstring);
  }  
}

void setupTime() {
  configTime(2 * 3600, 0 * 3600, "0.nl.pool.ntp.org", "1.nl.pool.ntp.org", "2.nl.pool.ntp.org");
  // dst parameter doesn't work... - make time adjust setting and reset time as menu option
}

void setupDebugOTA() {
  Debug.begin(DEBUG_HOST_NAME);
}

void setupOTA() {
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }
    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    // Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    // Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    // Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    // Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      // Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      // Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      // Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      // Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      // Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
 }

void setupRF24() {
  radio.begin();
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.enableDynamicPayloads() ;
  // radio.setAutoAck( true ) ;
  radio.setDataRate( RF24_250KBPS );
  radio.setChannel(100);
  radio.powerUp() ;
  radio.startListening();
  Serial.println("RX ready...");
}

void setupMCP23017() {
  setupMCP();
}

void setupDisplay() {
  u8g2.begin();  
}
