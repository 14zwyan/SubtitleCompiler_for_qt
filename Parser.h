#ifndef PARSER_H
#define PARSER_H

#include<utility>
#include<string>

#include"Lexical_analyser.h"

enum State
{
    START,
    COUNTER,
    START_TIME,
    ARROW,
    END_TIME,
    TEXT
};
typedef enum State State;

class Parser
{
public:
    Parser();

    void DoParse(const std::string &content);

    void test( const  std::string &text);

    std::pair<std::string,bool> DoParse_For_Qt(const  std::string  &content);
    void print_tokens();
private:
    Lexical_analyser lexical_analyser_;
    State state_=START;

};

#endif // PARSER_H
