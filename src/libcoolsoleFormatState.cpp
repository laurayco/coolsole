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

  FormatState::~FormatState()
  {
  }

  FormatState::FormatState():
    _fg(FormatState::White),
    _bg(FormatState::Black),
    _bold(false)
  {
  }

  FormatState::FormatState(const FormatState &src):
    _fg(src._fg),
    _bg(src._bg),
    _bold(src._bold)
  {
  }

  FormatState::FormatState(FormatState::Color aFg,FormatState::Color aBg, bool aBold):
    _fg(aFg),
    _bg(aBg),
    _bold(aBold)
  {
  }

  FormatState::FormatState(FormatState::Color aFg, FormatState::Color aBg):
    _fg(aFg),
    _bg(aBg),
    _bold(false)
  {
  }

  FormatState::FormatState(FormatState::Color aFg):
    _fg(aFg),
    _bg(FormatState::Black),
    _bold(false)
  {
  }

  FormatState::FormatState(FormatState::Color aFg, bool aBold):
    _fg(aFg),
    _bg(FormatState::Black),
    _bold(aBold)
  {
  }

}
