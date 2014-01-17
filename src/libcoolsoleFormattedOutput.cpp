#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../include/coolsole.hpp"

namespace Coolsole {

  const FormatState FormattedOutput::Format() const
  {
    return this->History.top();
  }

  void FormattedOutput::Format(const FormatState &state)
  {
    this->History.push(state);
    this->set_state(state.foreground(),state.background(),state.bold());
  }

  void FormattedOutput::revert()
  {
    this->History.pop();
    const FormatState state = this->Format();
    this->set_state(state.foreground(),state.background(),state.bold());
  }

  FormattedOutput::~FormattedOutput()
  {
    this->reset();
  }

}

