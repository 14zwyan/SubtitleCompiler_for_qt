#ifndef PARSER_H
#define PARSER_H

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

private:
    Lexical_analyser lexical_analyser_;
    State state_;

};

#endif // PARSER_H
