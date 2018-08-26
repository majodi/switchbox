#include "constants.h"

//WiFi
const char* ssid = "not used";
const char* password = "not used";
char ipCstring[16];

// Rotary
const int pinInterrupt = digitalPinToInterrupt(PinMCPINT);
volatile bool rotaryChange = false;
volatile byte rotaryVirtual = 0; byte savRotaryVirtual = 0; // sav = save for toggle push
volatile bool rotaryPushed = false; // rotarySwitch

// Menu
const unsigned char* iconFont_arrow_2x = u8g2_font_open_iconic_arrow_2x_t; const byte iconFont_arrow_2xWidth = 16; const byte iconFont_arrow_2xHeight = 16;
const unsigned char* iconFont_embedded_6x = u8g2_font_open_iconic_embedded_6x_t; const byte iconFontWidth = 48; const byte iconFontHeight = 48;
const uint8_t ico_arrowLeft = 0x45; const uint8_t ico_arrowRight = 0x46;
const uint8_t ico_arrowUp = 0x43; const uint8_t ico_arrowDown = 0x40;
const unsigned char* menuFont = u8g2_font_7x14B_tf; const byte menuFontWidth = 14; const byte menuFontHeight = 14;
const unsigned char* bigFont = u8g2_font_10x20_tf;
const char* menuMatrix[][8] =  // max 8 subitems (save memory consumption)
{
  {"Automatisch", "Handmatig", "Instellingen"},
  {"Terug...", "Skip 1x   : UIT", "Forceer 1x: UIT", "Automaat  : UIT"},
  {"Terug...", "Achter (1): UIT", "Zijknt (2): UIT", "Voor   (3): UIT"},
  {"Terug...", "Info", "Reset WiFi"}
};
const byte nrOfItems[] = {3, 4, 4, 3}; // warning! has to match actual menu layout
const byte nrOfTopMenuItems = nrOfItems[0]; // doesn't work with cpp: sizeof(menuMatrix[0]) / 4; // number of 4 byte pointers...
const uint8_t pictogramsTopMenu [] = {0x43, 0x40, 0x42, 0x42, 0x42};
const byte topMargin = 3; // start submenu 3 pixels lower
byte menuActive = 0; // 0=top, 1=sub
byte menuLastActive = 0;
byte menuTopPos = 0; byte menuSubPos = 0; byte savMenuSubPos = 0; // sav = save for toggle push
byte nrOfSubMenuItems = 0;
byte menuSubOffset = 0; // choice offset in view port
byte savMenuSubOffset = 0; // save position for toggle push
byte action = 0;

// Time
int thisMinute = 0;
int thisHour = 0;

// Sensor
float sensorTemp = 20;
float sensorHum = 70;
float sensorPress = 1020;
float sensorRain = 10;
float sensorSun = 80;

byte valves = B11111111; // relais module switches on LOW (so other way around as test-leds)
// byte valves = B00000000;
char blynkAuth[] = "7f88d4d3d00644628c489ce521197f87";
bool userActivity = false;
bool screenSaverActive = false;
int minuteTimer;

U8G2_SSD1306_128X64_NONAME_2_SW_I2C u8g2(U8G2_R0, D1, D2, U8X8_PIN_NONE);   // clock, data double speed, double RAM
WiFiManager wifiManager;
RemoteDebug Debug;
RF24 radio(CE, CSN);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
char inStr[30];
char totalStr[30];
bool firstPart = false;

