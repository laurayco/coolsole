#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../include/coolsole.hpp"

namespace Coolsole {

  StreamFormatter::FormatInsertion::FormatInsertion(StreamFormatter &sf,FormatState fs):
    formatter(sf),
    state(fs)
  {
  }

  StreamFormatter::FormatReset::FormatReset(StreamFormatter &sf):
    formatter(sf)
  {
  }

  std::ostream &operator << ( std::ostream &out, const FormatInsertion &fi)
  {
    fi.formatter.Format(fi.state);
  }

  std::ostream &operator << ( std::ostream &out, const FormatReset &fr)
  {
    fi.formatter.revert();
  }

  StreamFormatter::insert(const FormatState &state)
  {
    return StreamFormatter::FormatInsertion(*this,state);
  }

  StreamFormatter::reset()
  {
    return StreamFormatter::FormatReset(*this);
  }
}