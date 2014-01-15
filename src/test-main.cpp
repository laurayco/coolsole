#include <iostream>
#include "../include/coolsolemodule.hpp"

using namespace Coolsole;

using namespace Coolsole;

int main(int argc,char** argv)
{
    FormattedOutput& format_control = ConsoleOutput::Singleton.get_instance();
    
    Color color_cycle[] = {
        Black,
        Blue,
        Red,
        White,
        Green,
        Purple,
        Aqua,
        Gray,
        BrightBlue,
        BrightRed,
        BrightWhite,
        BrightGreen,
        BrightPurple,
        BrightAqua
    };
    
    for(int i=0;i<(sizeof(color_cycle)/sizeof(Color));i++)
    {
        format_control.foreground(color_cycle[i]);
        std::cout<<"Testing:"<<color_cycle[i]<<"::"<<i<<std::endl;
        format_control.previous_foreground();
    }
    
    format_control.reset();
    
    for(int i=0;i<(sizeof(color_cycle)/sizeof(Color));i++)
    {
        format_control.background(color_cycle[i]);
        std::cout<<"Testing:"<<color_cycle[i]<<"::"<<i<<std::endl;
        format_control.previous_background();
    }
    
    return 0;
}
