#include <iostream>
#include <string>
#include "../include/coolsolemodule.hpp"

using namespace Coolsole;

class Token {
  protected:
    const FormatState format;
    const std::string str;
    Token(const FormatState fs,const std::string text):
      format(fs),
      str(text)
    {
    }
  public:
    friend std::ostream &operator << ( std::ostream &, const Token &);
};

std::ostream &operator << ( std::ostream &out, const Token &token)
{
  auto format_holder = token.format.format_scope(ConsoleOutput::Singleton.get_instance());
  out << token.str << " ";
  return out;
}

class KeywordToken:public Token {
  protected:
    KeywordToken(const std::string text):
      Token(FormatState(FormatState::Blue,FormatState::Black,true),text)
    {
    }
};

class ClassToken:public KeywordToken {
  public:
    ClassToken():
      KeywordToken("class")
    {
    }
};

class IdentifierToken: public Token {
  public:
    IdentifierToken(const std::string text):
      Token(FormatState(FormatState::Red,FormatState::Black,false),text)
    {
    }
};

int main(int argc,char **argv)
{
  std::cout << ClassToken() << IdentifierToken("Token") << std::endl;
  return 0;
}
