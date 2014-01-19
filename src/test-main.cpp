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
    //format_control.Format(formats[i]);
    std::cout << format_control.insert(formats[i]);
    std::cout << "Testing format: " << i;
    std::cout << std::endl;
    std::cout << "and...control." ;
    std::cout << format_control.previous();
    std::cout << std::endl << "How'd it do?!";
    std::cout << std::endl;
    //format_control.revert();
  }
  return 0;
}
