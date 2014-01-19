#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../include/coolsole.hpp"

#define COPY_STRING(s) strcpy((char*)malloc(strlen(s)+1),s)

namespace Coolsole {

  const char *START_CODE = "\033[";
  const char *SET_FG =      "30;";
  const char *SET_BOLD =    "1;";
  const char *SET_BG =      "40";
  const char *END_CODE = "m";

  template<>
  ConsoleOutput *SingletonContainer<ConsoleOutput>::make_instance()
  {
#ifdef _WIN32
    return new ConsoleOutput(GetStdHandle( STD_OUTPUT_HANDLE ));
#else
    return new ConsoleOutput();
#endif
  }
}