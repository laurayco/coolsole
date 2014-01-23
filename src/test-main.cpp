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
  StreamFormatter &formatter = ConsoleOutput::Singleton.get_instance();
  out << formatter.insert(token.format) << token.str << formatter.previous() << " ";
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

class OpenScopeToken: public Token {
  public:
    OpenScopeToken():
      Token(FormatState(FormatState::White,FormatState::Black,false),"{")
    {
    }
};

class CloseScopeToken: public Token {
  public:
    CloseScopeToken():
      Token(FormatState(FormatState::White,FormatState::Black,false),"};")
    {
    }
};

class DataType;
class ClassDefinition: public DataType;
class ClassMethod;
class ParameterInfo;

class DataType
{
  private:
    const std::string __name;
    const std::string name() const
    {
      return this->__name;
    }
  protected:
    DataType(const std::string _name):
      __name(_name)
    {
    }
};

typedef std::std::vector<std::pair<ClassDefinition::AccessLevel,ClassDefinition>> ExtendList;
typedef std::std::vector<std::pair<ClassDefinition::AccessLevel,ClassDefinition>> MethodList;

class ClassDefinition: public DataType {
protected:
  ExtendList _base_types;
  MethodList _methods;
  public:

    enum {
      Public,
      Protected,
      Private
    } AccessLevel;

    ClassDefinition(const std::string _name):
      DataType(_name)
    {
    }

    ClassDefinition& extends(const ClassDefinition cls)
    {
      _base_types.add(cls);
      return *this;
    }

    ClassDefinition& implements(const ClassMethod method)
    {
      _methods.add(cls);
      return *this;
    }

    /*
    ClassDefinition& has(const InstanceVariable var)
    {
      _members.add(var);
      return *this;
    }
};

class ClassMethod {
private:
  const bool _is_static, _is_const;
  const std::string _name;
  const ClassDefinition::AccessLevel _access;
  const ParameterInfo _parameters[];//null-terminated.
};

class ParamaterInfo
{
private:
  const std::string _base_type;
  const std::string _name;
public:
  ParamaterInfo(const std::string abase_type, const std::string aname)
  {
    this->_base_type = abase_type;
    this->_name = aname;
  }
};

class ClassDefinitionOutput {
  private:
    const ClassDefinition __cd;
  protected:

  public:
    ClassDefinitionOutput(const ClassDefinition class_definition):
      __cd(class_definition)
    {
    }
    friend std::ostream &operator << ( std::ostream &, const ClassDefinitionOutput);
};

std::ostream &operator << ( std::ostream &out, const ClassDefinitionOutput cdo)
{
  const char *NEW_LINE = "\n\t";
  out << ClassToken();
  out << IdentifierToken(cdo.__cd.name());
  out << "\n";
  out << OpenScopeToken();
  for(unsigned int i = 0; i<0; i++)
  {
    // output field members.
    out << NEW_LINE;
  }
  out << "\n";
  out << CloseScopeToken();
  return out;
}

int main(int argc,char **argv)
{
  ClassDefinition animal_class = ClassDefinition("Animal");
  std::cout << ClassDefinitionOutput(animal_class) << std::endl;
  return 0;
}
