#ifndef PARSER_H
#define PARSER_H

#include<utility>
#include<string>
#include<vector>

#include"Lexical_analyser.h"
#include"Subtitle.h"


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
    std::vector<Subtitle> subtitles()    { return subtitles_; }
    void clear()   { lexical_analyser_.clear();  state_=START;  subtitles_.clear();}
private:
    Lexical_analyser lexical_analyser_;
    State state_=START;
   std::vector<Subtitle> subtitles_;


};

#endif // PARSER_H
