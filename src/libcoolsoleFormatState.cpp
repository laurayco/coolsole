#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../include/coolsole.hpp"

namespace Coolsole {

  const FormatState::Color FormatState::foreground() const
  {
    return this->_fg;
  }

  const FormatState::Color FormatState::background() const
  {
    return this->_bg;
  }

  const bool FormatState::bold() const
  {
    return this->_bold;
  }

  void FormatState::apply() {
    this->output.Format(*this);
  }

  FormatState::~FormatState()
  {
  }

  FormatState::FormatState(const FormatState &src):
    _fg(src._fg),
    _bg(src._bg),
    _bold(src._bold),
    output(src.output)
  {
  }

  FormatState::FormatState(FormattedOutput &aOutput,FormatState::Color aFg,FormatState::Color aBg, bool aBold):
    _fg(aFg),
    _bg(aBg),
    _bold(aBold),
    output(aOutput)
  {
  }

  FormatState::FormatState(FormattedOutput &aOutput,FormatState::Color aFg, FormatState::Color aBg):
    _fg(aFg),
    _bg(aBg),
    _bold(aOutput.Format().bold()),
    output(aOutput)
  {
  }

  FormatState::FormatState(FormattedOutput &aOutput,FormatState::Color aFg):
    _fg(aFg),
    _bg(aOutput.Format().background()),
    _bold(aOutput.Format().bold()),
    output(aOutput)
  {
  }

  FormatState::FormatState(FormattedOutput &aOutput,FormatState::Color aFg, bool aBold):
    _fg(aFg),
    _bg(aOutput.Format().background()),
    _bold(aBold),
    output(aOutput)
  {
  }

}
