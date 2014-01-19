#include <iostream>
#include "../include/coolsolemodule.hpp"

using namespace Coolsole;

using namespace Coolsole;

int main(int argc,char **argv)
{
  StreamFormatter &format_control = ConsoleOutput::Singleton.get_instance();
  FormatState formats[] = {
    FormatState(FormatState::White,FormatState::Red,true),
    FormatState(FormatState::Blue,FormatState::White,true),
    FormatState(FormatState::White,FormatState::Blue,true)
  };
  for(unsigned int i=0; i<(sizeof(formats)/sizeof(FormatState)); i++)
  {
    auto format_holder = formats[i].format_scope(format_control);
    std::cout << "There has been formatting applied to this entire scope." << std::endl;
  }
  return 0;
}
