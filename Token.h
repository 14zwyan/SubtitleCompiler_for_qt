#ifndef TOKEN_H
#define TOKEN_H

#include<map>
#include<string>
#include<iostream>

enum  TYPE{
    TYPE_COUNTER,
    TYPE_TIMESTAMP,
    TYPE_TIME_ARROW,
    TYPE_TEXT,
    TYPE_EMPTY,
    TYPE_END_OF_FILE,
    TYPE_NONE
};
typedef enum TYPE TOKENTYPE;


class Token
{
private:

   std::map<TOKENTYPE ,std::string> representation_=
   {
       {TYPE_COUNTER, "NUMBER"},
       {TYPE_TIMESTAMP,"TIMESTAMP"},
       {TYPE_TIME_ARROW,"ARROW"},
       {TYPE_TEXT,"SUBTITLE"}
   };
   TOKENTYPE type_;
   std::string  value_;
public:
    Token (TOKENTYPE tp, std::string  val) : type_(tp), value_(val)  {  /*empty**/}
    void Display();

    TYPE type()  {  return type_; };
    std::string PresentType()  { return representation_[type_]; }
    std::string value() { return value_;}

    void set_value(std::string value)  { value_=value; }

};




#endif // TOKEN_H
