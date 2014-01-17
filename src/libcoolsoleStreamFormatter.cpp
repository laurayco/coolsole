#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../include/coolsole.hpp"

namespace Coolsole {

  StreamFormatter::FormatInsertion::FormatInsertion(StreamFormatter & sf,const FormatState & fs):
    formatter(sf),
    state(fs)
  {
  }

  StreamFormatter::FormatReset::FormatReset (StreamFormatter &sf):
    formatter(sf)
  {
  }

  const StreamFormatter::FormatInsertion StreamFormatter::insert(const FormatState &state)
  {
    return FormatInsertion(*this,state);
  }

  const StreamFormatter::StreamFormatter::FormatReset StreamFormatter::previous()
  {
    return FormatReset(*this);
  }
}

std::ostream &operator << ( std::ostream &out, const Coolsole::StreamFormatter::FormatInsertion &fi)
{
  fi.formatter.Format(fi.state);
  return out;
}

std::ostream &operator << ( std::ostream &out, const Coolsole::StreamFormatter::FormatReset &fr)
{
  fr.formatter.revert();
  return out;
}