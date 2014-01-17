#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../include/coolsole.hpp"

using namespace Coolsole;

const FormatState::Color FormatState::foreground() const
{
	return this->_fg;
}

const FormatState::Color FormatState::background() const
{
	return this->_bg;
}

const bool bold() const
{
	return this->_bold;
}

void FormatState::apply(){
	this->output.set_state(fg,bg,bold);
}

FormatState::~FormatState()
{
	if(previous!==null)
	{
		previous->apply();
	}
}

FormatState::FormatState(FormattedOutput& aOutput,FormatState::Color aFg,FormatState::Color aBg, bool aBold):
	fg(aFg),
	bg(aBg),
	bold(aBold),
	output(aOutput)
{
}

FormatState::FormatState(FormattedOutput& aOutput,FormatState::Color aFg, FormatState::Color aBg):
	fg(aFg),
	bg(aBg),
	bold(aOutput.Format().bold()),
	output(aOutput)
{
}

FormatState::FormatState(FormattedOutput& aOutput,FormatState::Color aFg):
	fg(aFg),
	bg(aOutput.Format().background()),
	bold(aOutput.Format().bold()),
	output(aOutput)
{
}

FormatState::FormatState(FormattedOutput& aOutput,FormatState::Color aFg, bool aBold):
	fg(aFg),
	bg(aOutput.Format().background()),
	bold(aBold),
	output(aOutput)
{
}
