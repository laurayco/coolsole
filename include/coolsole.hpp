#ifndef __coolsole__hpp

#include <iostream>
#include <stack>

#ifdef _WIN32
#include <windows.h>
#endif

#ifndef nullptr
#define nullptr NULL
#endif

namespace Coolsole {

  class ColorState;
  class FormattedOutput;

  template<typename>
  class SingletonContainer;

  class FormatState
  {
    public:
      /*
        Color Codes found here:
          http://en.wikipedia.org/wiki/ANSI_escape_code#Colors
      */
      enum Color {
        #ifdef _WIN32
            Black = 0,
            Blue = 1,
            Green = 2,
            Aqua = 3,
            Red = 4,
            Purple = 5,
            Yellow = 6,
            White = 7,
            Gray = 8
        #else
            Black = 0,
            Blue = 4,
            Green = 2,
            Yellow = 3,
            Aqua = 6,
            Red = 1,
            Purple = 5,
            White = 7
        #endif
      };
      FormatState(FormattedOutput&,Color);//fg
      FormatState(FormattedOutput&,Color,bool);//fg,bold
      FormatState(FormattedOutput&,Color,Color);//fg,bg
      FormatState(FormattedOutput&,Color,Color,bool);//fg,bg,bold
      virtual ~FormatState();//restore previous 
      const Color foreground() const;
      const Color background() const;
      const bool bold() const;
    protected:
      const Color _fg, _bg;
      const bool _bold;
    private:
      FormatState* previous;
      FormattedOutput& output;
      void apply();
  };


  /*
    Here simply for the purpose
    of inheritance. Maybe adding an
    HTML-output could be a good idea.
    Could base this on detecting
    CGI, and returnning a HTML-output
    instance in the get_console()
    function or something. That would
    be pretty cool, jyah?
  */
  class FormattedOutput {
    public:
      const FormatState& Format() const;
      void Format(FormatState&);
      virtual void reset() = 0;//return to default formating.
      virtual void revert();
    protected:
      FormatState& CurrentState;
      FormatState& DefaultState;
      FormattedOutput();
      virtual void set_state(Color,Color,bool)=0;
  };

  class StreamFormatter {
  public:
    virtual void reset() = 0;
    class FormatInsertion
    {
      public:
        FormatInsertion(StreamFormatter&,FormatState&);
      private:
        StreamFormatter& formatter;
        FormatState& state;
        friend std::ostream& operator << ( std::ostream&, const FormatInsertion&);
    };
    class FormatReset
    {
      public:
        FormatReset(StreamFormatter&);
      private:
        StreamFormatter& formatter;
        friend std::ostream& operator << ( std::ostream&, const FormatReset&);
    };
    const FormatInsertion Insert(const FormatState& state);
    const FormatReset Reset();
  protected:
      virtual void set_state(Color,Color,bool)=0;
  };

  template<typename Type>
  class SingletonContainer {
    protected:
      Type *instance;
      virtual Type make_instance()
      {
        return new Type();
      }
    public:
      SingletonContainer(Type *ptr = nullptr):
        instance(ptr)
      {
      }

      Type &get_instance()
      {
        if(instance!=nullptr)
          return *instance;
        instance = make_instance();
        return *instance;
      }

      ~SingletonContainer()
      {
        if(instance!=nullptr)
        {
          delete instance;
        }
      }
  };

  ConsoleOutput* SingletonContainer<ConsoleOutput>::make_instance()
  {
    #ifdef _WIN32
          return new ConsoleOutput(GetStdHandle( STD_OUTPUT_HANDLE ));
    #else
          return new ConsoleOutput();
    #endif
  }

  /*
    Because only std::out will support
    any kind of text formatting,
    we will make this a singleton type
    object. Notice however, that this
    singleton instance does inherit
    from the potentially non-singleton
    FormattedOutput class.
  */
  class ConsoleOutput: public FormattedOutput {
    public:
      virtual void set_state(Color,Color,bool);//fg,bg,bold
      virtual void reset();
      #ifdef _WIN32
        HANDLE console_handle;
        CONSOLE_SCREEN_BUFFER_INFO original_csbi;
        ConsoleOutput(HANDLE);
      #else

        ConsoleOutput();
      #endif
      static SingletonContainer<ConsoleOutput> Singleton;
      virtual ~ConsoleOutput();
  };

}

#endif
