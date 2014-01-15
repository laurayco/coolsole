#include <iostream>
#include <windows.h>
#include "../include/coolsole.hpp"

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

	Coolsole::ConsoleOutput& Coolsole::ConsoleOutput::get_console()
	{
		if(Coolsole::ConsoleOutput::output!=nullptr){
			return *Coolsole::ConsoleOutput::output;
		}
		Coolsole::ConsoleOutput::output = new Coolsole::ConsoleOutput();
		return *Coolsole::ConsoleOutput::output;
	}

	Coolsole::ConsoleOutput::ConsoleOutput(): Coolsole::FormattedOutput()
	{
		/*
			I don't think anything really needs to
			be done in the constructor. Just here
			because... ?
		*/
	}
#endif

int main()
{
	Coolsole::FormattedOutput& FormatControl = Coolsole::ConsoleOutput::Singleton.get_instance();

	std::cout<<"Testing formatting..."<<std::endl;

	FormatControl.foreground(Coolsole::Red);
	FormatControl.background(Coolsole::BrightWhite);

	std::cout<<"Did it work!?"<<std::endl;

	return 0;
}