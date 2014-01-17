#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../include/coolsole.hpp"

#define COPY_STRING(s) strcpy((char*)malloc(strlen(s)+1),s)
#define DIGIT_CHAR(n) ((char)(((int)'0')+n))

namespace Coolsole {

  template<>
  class SingletonContainer<ConsoleOutput> {
      ConsoleOutput *make_instance()
      {
#ifdef _WIN32
        return new ConsoleOutput(GetStdHandle( STD_OUTPUT_HANDLE ));
#else
        return new ConsoleOutput();
#endif
      }
  };

  SingletonContainer<ConsoleOutput> ConsoleOutput::Singleton;

  void ConsoleOutput::set_state(FormatState::Color fg,FormatState::Color bg, bool bold)
  {
#ifdef _WIN32
    FormatState::Color mod_fg = fg;
    if(bold) {
      mod_fg = ((FormatState::Color)(((int)fg)+8));
    }
    SetConsoleTextAttribute(
      this->console_handle,
      (bg<<4)|mod_fg
    );
#else
    char *set_fg_code = COPY_STRING(SET_FG);
    char *set_bg_code = COPY_STRING(SET_BG);
    set_fg_code[1] = DIGIT_CHAR(base_color(fg));
    set_bg_code[1] = DIGIT_CHAR(base_color(bg));
    std::cout<< START_CODE << set_fg_code << set_bg_code << (bold?SET_BOLD:"") << END_CODE;
#endif
  }

  void ConsoleOutput::reset()
  {
#ifdef _WIN32
    SetConsoleTextAttribute(
      this->console_handle,
      this->original_csbi.wAttributes
    );
#else
    std::cout <<  "\033[0m";
#endif
  }

#ifdef _WIN32
  ConsoleOutput::ConsoleOutput(HANDLE h)
  {
    this->console_handle = h;
    GetConsoleScreenBufferInfo( this->console_handle, &(this->original_csbi) );
  }
#else
  ConsoleOutput::ConsoleOutput()
  {
  }
#endif

}