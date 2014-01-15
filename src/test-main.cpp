#include <iostream>
#include "../include/coolsolemodule.hpp"

using namespace Coolsole;

int main(int argc,char** argv)
{
    FormattedOutput& format_control = ConsoleOutput::Singleton.get_instance();

    format_control.background(Blue);
    std::cout<<"\tWelcome..."<<std::endl;
    format_control.previous_background();
    std::cout<<"\t";
    format_control.foreground(BrightWhite);
    format_control.background(Red);
    std::cout<<"\t\tTo the future.\t\t"<<std::endl;

}