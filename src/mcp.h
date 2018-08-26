#ifndef MCP_H
#define MCP_H 1

#include "constants.h"
#include <Wire.h>

void setupMCP();
void reEnableRotary();
void writeMCP(int, int);
int readGPIOB();
void mcpResetInt(); //deze 3 naar mcp.h/cpp en rotary (isr)
void isrMCPInt();

#endif