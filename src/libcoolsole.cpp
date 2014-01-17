#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../include/coolsole.hpp"

#define COPY_STRING(s) strcpy((char*)malloc(strlen(s)+1),s)

#ifdef _WIN32
#else
const char *Coolsole::START_CODE = "\033[";
const char *Coolsole::SET_FG =      "30;";
const char *Coolsole::SET_BOLD =    "1;";
const char *Coolsole::SET_BG =      "40";
const char *Coolsole::END_CODE = "m";
#endif
