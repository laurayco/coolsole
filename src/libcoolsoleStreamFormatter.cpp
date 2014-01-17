#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../include/coolsole.hpp"


  class StreamFormatter {
  public:
    virtual void reset() = 0;
    class FormatInsertion
    {
      public:
        FormatInsertion(StreamFormatter&,FormatState&);
        friend std::ostream& operator << ( std::ostream&, const FormatInsertion&);
    };
    class FormatReset
    {
      public:
      FormatReset(StreamFormatter&);
      friend std::ostream& operator << ( std::ostream&, const FormatReset&);
    };
    const FormatInsertion Insert(const FormatState& state);
    const FormatReset Reset();
  protected:
      virtual void set_state(Color,Color,bool)=0;
  }

std::ostream& operator << ( std::ostream& out, const FormatInsertion& fi)
{
	fi.formatter.Format(fi.state);
}

std::ostream& operator << ( std::ostream& out, const FormatReset& fr)
{
	fi.formatter.revert();
}

