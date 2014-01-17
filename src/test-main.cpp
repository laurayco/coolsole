#include <iostream>
#include "../include/coolsolemodule.hpp"

using namespace Coolsole;

using namespace Coolsole;

int main(int argc,char **argv)
{
  FormattedOutput &format_control = ConsoleOutput::Singleton.get_instance();
  FormatState formats[] = {
    FormatState(format_control,FormatState::Blue,FormatState::Green,true)
  };
  for(unsigned int i=0; i<(sizeof(formats)/sizeof(FormatState)); i++)
  {
    std::cout << format_control.insert(formats[i]);
    std::cout << "Testing format: " << i;
    std::cout << format_control.reset();
    std::cout << endl;
  }
  return 0;
}
