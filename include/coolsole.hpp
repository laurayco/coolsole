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

  extern const char *START_CODE;
  extern const char *SET_FG;
  extern const char *SET_BOLD;
  extern const char *SET_BG;
  extern  const char *END_CODE;

  class ColorState;
  class FormattedOutput;

  template<typename>
  class SingletonContainer;

  class FormatState {
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
      FormatState();
      FormatState(const FormatState &);
      FormatState(Color); //fg
      FormatState(Color,bool); //fg,bold
      FormatState(Color,Color); //fg,bg
      FormatState(Color,Color,bool); //fg,bg,bold
      virtual ~FormatState();//restore previous
      const Color foreground() const;
      const Color background() const;
      const bool bold() const;
    protected:
      const Color _fg, _bg;
      const bool _bold;
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
      const FormatState Format() const;
      void Format(const FormatState &);
      virtual void reset();//return to default formating.
      virtual void revert();
      virtual ~FormattedOutput();
    protected:
      std::stack<FormatState> History;
      //FormatState &DefaultState;
      virtual void set_state(FormatState::Color,FormatState::Color,bool)=0;
  };

  // basically provides convenience functionality for
  // std::cout << Formatter.insert(FormatState(Color)) << "colored text";
  // std::cout << Formatter.reset() << std::endl;
  class StreamFormatter: public FormattedOutput {
    public:
      class FormatInsertion {
        public:
          FormatInsertion(StreamFormatter &,const FormatState &);
          StreamFormatter &formatter;
          const FormatState &state;
          friend std::ostream &operator << ( std::ostream &, const FormatInsertion &);
      };
      class FormatReset {
        public:
          FormatReset(StreamFormatter &);
          StreamFormatter &formatter;
          friend std::ostream &operator << ( std::ostream &, const FormatReset &);
      };
      const FormatInsertion insert(const FormatState &);
      const FormatReset previous();
    protected:
      virtual void set_state(FormatState::Color,FormatState::Color,bool)=0;
  };

  template<typename Type>
  class SingletonContainer {
    protected:
      Type *instance;
      Type *make_instance();
    public:
      SingletonContainer(Type *ptr = nullptr):
        instance(ptr)
      {
      }

      Type &get_instance()
      {
        if(instance!=nullptr) {
          return *instance;
        }
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

  /*
    Because only std::out will support
    any kind of text formatting,
    we will make this a singleton type
    object. Notice however, that this
    singleton instance does inherit
    from the potentially non-singleton
    FormattedOutput class.
  */
  class ConsoleOutput: public StreamFormatter {
    public:
      virtual void set_state(FormatState::Color,FormatState::Color,bool);//fg,bg,bold
      virtual void reset();
      virtual ~ConsoleOutput();
#ifdef _WIN32
      HANDLE console_handle;
      CONSOLE_SCREEN_BUFFER_INFO original_csbi;
      ConsoleOutput(HANDLE);
#else

      ConsoleOutput();
#endif
      static SingletonContainer<ConsoleOutput> Singleton;
  };

}

#endif
