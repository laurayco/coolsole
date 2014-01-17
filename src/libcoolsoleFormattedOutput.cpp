#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../include/coolsole.hpp"

using namespace Coolsole;

const FormatState& FormattedOutput::Format() const
{
	return *(this->CurrentState);
}

void FormattedOutput::Format(FormatState* state)
{
	//state.hold(this->CurrentState);
	this->CurrentState = state;
	this->set_state(state->foreground(),state->background(),state->bool());
}

FormattedOutput::~FormattedOutput()
{
	this->reset();
}