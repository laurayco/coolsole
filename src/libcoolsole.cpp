#include <iostream>
#include "../include/coolsole.hpp"

#define COPY_STRING(s) strcpy((char*)malloc(strlen(s)+1),s)

bool Coolsole::is_bright(Coolsole::Color color)
{
    return color > ((int)Coolsole::White);
}

Coolsole::Color Coolsole::base_color(Coolsole::Color color)
{
    return Coolsole::Color(color&((int)Coolsole::White));
}

Coolsole::ColorState::ColorState(Coolsole::Color initial)
{
    push_color(initial);
}

void Coolsole::ColorState::push_color(Coolsole::Color color)
{
    colors.push(color);
}

Coolsole::Color Coolsole::ColorState::pop_color()
{
    Coolsole::Color r = static_cast<Coolsole::Color>(*this);
    colors.pop();
    return r;
}

Coolsole::Color Coolsole::ColorState::current_color() const
{
    return this->colors.top();
}


Coolsole::ColorState::operator Coolsole::Color() const
{
    return this->current_color();
}

Coolsole::Color Coolsole::FormattedOutput::foreground() const
{
    return this->_foreground.current_color();
}

Coolsole::Color Coolsole::FormattedOutput::background() const
{
    return this->_background.current_color();
}

void Coolsole::FormattedOutput::foreground(Coolsole::Color c)
{
    this->_foreground.push_color(c);
    this->_background.push_color(this->_background);
    this->set_state(this->foreground(),this->background());
}

void Coolsole::FormattedOutput::background(Coolsole::Color c)
{
    this->_background.push_color(c);
    this->_foreground.push_color(this->_foreground);
    this->set_state(this->foreground(),this->background());
}

Coolsole::FormattedOutput::FormattedOutput():
    _foreground(Coolsole::White),
    _background(Coolsole::Black)
{
}

void Coolsole::FormattedOutput::previous_foreground()
{
    // notice: colors are kept consistent.
    //      ie: if foreground is set, the
    //          the background is replicated.
    this->_foreground.pop_color();
    this->_foreground.push_color(this->foreground());
    this->set_state(this->foreground(),this->background());
}

void Coolsole::FormattedOutput::previous_background()
{
    // notice: colors are kept consistent.
    //      ie: if foreground is set, the
    //          the background is replicated.
    this->_background.pop_color();
    this->_background.push_color(this->background());
    this->set_state(this->foreground(),this->background());
}

Coolsole::ConsoleOutput::ConsoleSingleton Coolsole::ConsoleOutput::Singleton;

#ifdef _WIN32

#include <windows.h>

Coolsole::ConsoleOutput::ConsoleOutput(HANDLE h):
    Coolsole::FormattedOutput()
{
    this->console_handle = h;
    GetConsoleScreenBufferInfo( this->console_handle, &(this->original_csbi) );
}

void Coolsole::ConsoleOutput::set_state(Coolsole::Color fg,Coolsole::Color bg)
{
    SetConsoleTextAttribute(
        Coolsole::ConsoleOutput::console_handle,
        (bg<<4)|fg
    );
}

Coolsole::ConsoleOutput::~ConsoleOutput()
{
    SetConsoleTextAttribute(
        this->console_handle,
        this->original_csbi.wAttributes
    );
}

#else

Coolsole::ConsoleOutput::ConsoleOutput(): Coolsole::FormattedOutput()
{
    /*
    	I don't think anything really needs to
    	be done in the constructor. Just here
    	because... ?
    */
}

void Coolsole::ConsoleOutput::set_state(Coolsole::Color fg,Coolsole::Color bg)
{
    //-------------------0123456
    const char* set_fg =      "\x1b[30m;";
    const char* set_fg_bold = "\x1b[30;1m;";
    const char* set_bg =      "\x1b[40m;";
    const char* set_bg_bold = "\x1b[40;1m;";
    const char* fg_code = Coolsole::is_bright(fg)? set_fg_bold:set_fg;
    const char* bg_code = Coolsole::is_bright(fg)? set_fg_bold:set_bg;
    char* set_fg_code = COPY_STRING(fg_code);
    char* set_bg_code = COPY_STRING(bg_code);
    /*
    	Notice: I'm modifyinga char* variable here
    	that is assigned from a const char*.
    	This is not typically a good thing to do.
    	But since these variable's should only be
    	accessed from within this function, it should
    	be perfectly okay.
    */
    set_fg_code[6] = (char)(((int)'0') + Coolsole::base_color(fg));
    set_bg_code[6] = (char)(((int)'0') + Coolsole::base_color(bg));
    std::cout<< set_fg_code << bg_code;
}

Coolsole::ConsoleOutput::~ConsoleOutput()
{
    std::cout <<  "\x1b[0m";
}

#endif
