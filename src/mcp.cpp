#include "mcp.h"

void setupMCP() {
  Wire.begin(PinSDA, PinSCL);  
  writeMCP(IOCONA, initIOCONA); // config A/B - Disable sequential addresses = 2_ / interrupt polarity ODR = _4, active high = _2, active low = _0
  writeMCP(IOCONB, initIOCONB);
  writeMCP(IODIRA, initIODIRA); // A all out
  writeMCP(IODIRB, initIODIRB); // B all in
  writeMCP(GPPUB, initGPPUB); // B all pull-up
  writeMCP(DEFVALB, initDEFVALB); // B init DEFVAL
  writeMCP(INTCONB, initINTCONB); // B 0 = interrupt on value change (-NOT- compare with DEFVAL), 1 = compare with DEFVAL
  writeMCP(GPINTENB, initGPINTENB); // B enable interrupt for pin(s)
  pinMode(PinMCPINT, INPUT_PULLUP); // IOCON(INTPOL) = 0 --> Active Low
  attachInterrupt(pinInterrupt, isrMCPInt, FALLING); // interruptpin goes to low on interrupt (has internal pull-up activated and IOCON(INTPOL) = 0 --> Active Low)
  mcpResetInt();
}

void reEnableRotary() {
  rotaryChange = false; // reset flags
  rotaryPushed = false;
  action = 0;
  attachInterrupt(pinInterrupt, isrMCPInt, FALLING); // re-attach to listen for next rotary change
  mcpResetInt();
}

void writeMCP(int reg, int val) {
  Wire.beginTransmission(MCPaddress);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

int readGPIOB() {
  Wire.requestFrom(MCPaddress, GPIOB);
  return Wire.read();
}

void mcpResetInt() {
  // EIFR=0x01;
  delay(10);
  readGPIOB(); writeMCP(GPIOA, (int) valves); // dummy read/write
  // readGPIOB(); writeMCP(GPIOA, B00000001); // dummy read/write
  delay(10);
  readGPIOB(); writeMCP(GPIOA, (int) valves); // dummy read/write
  // readGPIOB(); writeMCP(GPIOA, B00000001); // dummy read/write
}

void isrMCPInt() {
  detachInterrupt(pinInterrupt);
  int r1 = readGPIOB(); // int r2 = readGPIOB(); int r3 = readGPIOB(); // 3 samples
  // Serial.print(r1); Serial.print(" - "); Serial.print(r2); Serial.print(" - "); Serial.println(r3);
  if (r1 == 223) {
    rotaryPushed = true;
    rotaryChange = true; // signal rotary change
    return;
  }
  rotaryPushed = false;
  if (r1 == 127) {
    rotaryVirtual++;
  } else {
    rotaryVirtual--;
  };
  rotaryChange = true; // signal rotary change
}
