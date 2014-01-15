#coolsole

##What
Adding pretty output to your console window has always been a pain.
The goal of coolsole is to both simplify and standardize this.

##Why
Because, Windows doesn't like standard ASCII control codes,
for some ungodly reason, and NCURSES is far too complicated
/ asserts too much control. Coolsole brings in a simple,
extendable framework to C++.

##How
###implementation
On Windows, it makes use of SetTextAttribute and GET_STD_HANDLE.
On everything else, it makes use of the standard ASCII control
codes.
###extending
To extend coolsole, create a class inheriting from
Coolsole::FormattedOutput. You need to implement the
set_format, and reset methods.
###to use
To use Coolsole, you need an instance of a Coolsole::FormattedOutput.
Since this is an abstract class, you will obviously need an instance
of a class that inherits from this.

  Coolsole::FormattedOutput& format_control = Coolsole::ConsoleOutput::Singleton.get_instance();

The ConsoleOutput has a singleton because you only have a single STDOUT handle.
Then, just use your format control using the methods foreground, background, etc.

#To-Do
* Python 3.x bindings.
* Create a "FormatHold" class that can be used to apply a format
  to the output of an entire scope.
* Create a stream-based FormattedOutput class that doesn't
  actually modify output in any way at all.
* Create an HTML formatted output that inherits from a
  stream-based std::out handler. Will use inline styles,
  *or* foreground-color, background-color, and bold classes.
