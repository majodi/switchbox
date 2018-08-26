#ifndef CONSTANTS_H
#define CONSTANTS_H 1

#include <Arduino.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <RemoteDebug.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <U8g2lib.h>

#define MCPaddress 0x20
#define DEBUG_HOST_NAME "remotedebug"

// NodeMCU pin layout
#define PinSDA D2
#define PinSCL D1
#define PinMCPINT D3
#define CE 2
#define CSN 15


// MCP23017 registers (everything except direction defaults to 0)
#define IODIRA   0x00   // IO direction  (0 = output, 1 = input (Default))
#define IODIRB   0x01
#define IOPOLA   0x02   // IO polarity   (0 = normal, 1 = inverse)
#define IOPOLB   0x03
#define GPINTENA 0x04   // Interrupt on change (0 = disable, 1 = enable)
#define GPINTENB 0x05   //
#define DEFVALA  0x06   // Default comparison for interrupt on change (interrupts on opposite)
#define DEFVALB  0x07
#define INTCONA  0x08   // Interrupt control (0 = interrupt on change from previous, 1 = interrupt on change from DEFVAL)
#define INTCONB  0x09
#define IOCONA   0x0A   // Configuration
                        // BANK 0 = same bank, addresses sequential
                        // MIRROR 0 = INT pins separate for A/B
                        // SEQOP 1 = disable (don't increment address pointer)
                        // DISSLW 0 = slew rate enabled
                        // HAEN address pins enabled/disabled (only for MCP23S17) 0 = disabled
                        // ODR 0 = Active driver (INTPOL sets polarity)
                        // INTPOL 0 = Active-low
                        // not implemented, read as 0
#define IOCONB   0x0B   // same as 0x0A is exact gelijk aan iocon 0A en hoeft niet ingesteld te worden, neemt alles over van iocon 0A.
#define GPPUA    0x0C   // Pull-up resistor (0 = disabled, 1 = enabled)
#define GPPUB    0x0D
#define INTFA    0x0E   // Interrupt flag (read only) : (0 = no interrupt, 1 = pin caused interrupt)
#define INTFB    0x0F
#define INTCAPA  0x10   // Interrupt capture (read only) : value of GPIO at time of last interrupt
#define INTCAPB  0x11
#define GPIOA    0x12   // Port value. Write to change, read to obtain value
#define GPIOB    0x13
#define OLLATA   0x14   // Output latch. Write to latch output.
#define OLLATB   0x15

// MCP23017 initialisation values
#define initIOCONA 0x20 // config A/B - Disable sequential addresses, rest default
#define initIOCONB 0x20 // probably overkill
#define initIODIRA 0x00 // A all out
#define initIODIRB 0xFF // B all in
#define initGPPUB 0xFF  // B all pull-up (besides external pull-up...)
#define initDEFVALB B00000000   // B interrupt on value change (compare value)
#define initINTCONB B00000000   // B 0 = interrupt on value change (-NOT- compare with DEFVAL), 1 = compare with DEFVAL
#define initGPINTENB B10100000  // B enable rotary interrupt for pin 7 (A/B) and 5 (SW)

//WiFi
extern const char* ssid;
extern const char* password;
extern char ipCstring[16];

// Rotary
extern const int pinInterrupt;
extern volatile bool rotaryChange;
extern volatile byte rotaryVirtual; extern byte savRotaryVirtual;
extern volatile bool rotaryPushed;

// Menu
extern const unsigned char* iconFont_arrow_2x; extern const byte iconFont_arrow_2xWidth; extern const byte iconFont_arrow_2xHeight;
extern const unsigned char* iconFont_embedded_6x; extern const byte iconFontWidth; extern const byte iconFontHeight;
extern const uint8_t ico_arrowLeft; extern const uint8_t ico_arrowRight;
extern const uint8_t ico_arrowUp; extern const uint8_t ico_arrowDown;
extern const unsigned char* menuFont; extern const byte menuFontWidth; extern const byte menuFontHeight;
extern const unsigned char* bigFont;
extern const char* menuMatrix[][8];
extern const byte nrOfItems[];
extern const byte nrOfTopMenuItems;
extern const uint8_t pictogramsTopMenu [];
extern const byte topMargin;
extern byte menuActive;
extern byte menuLastActive;
extern byte menuTopPos; extern byte menuSubPos; extern byte savMenuSubPos;
extern byte nrOfSubMenuItems;
extern byte menuSubOffset; extern byte savMenuSubOffset;
extern byte action;

// Time
extern int thisMinute;
extern int thisHour;

// Sensor
extern float sensorTemp;
extern float sensorHum;
extern float sensorPress;
extern float sensorRain;
extern float sensorSun;

extern byte valves;

extern char blynkAuth[];

extern bool userActivity;
extern bool screenSaverActive;
extern int minuteTimer;

extern U8G2_SSD1306_128X64_NONAME_2_SW_I2C u8g2;//(U8G2_R0, PinSCL, PinSDA, U8X8_PIN_NONE);   // clock, data double speed, double RAM

extern WiFiManager wifiManager;

extern RemoteDebug Debug;

extern RF24 radio;
extern const uint64_t pipes[2];
extern char inStr[30];
extern char totalStr[30];
extern bool firstPart;


#endif

// MCP GPIOA bit    UTP pin     Color                   Relais      Sprinkler
//      0               6       Groen                   IN1         K1 = Pump - 220
//      1               5       BlauwWit                IN2         K2 = Valve achter - 24
//      2               4       Blauw                   IN3         K3 = Valve zijknt - 24
//      3               3       GroenWit                IN4         K4 = Valve voor - 24
//      -               1, 8    OranjeWit   , Bruin     GND
//      -               2, 7    Oranje      , BruinWit  VCC
//