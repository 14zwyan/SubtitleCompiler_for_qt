#ifndef LEXICAL_ANALYSER_H
#define LEXICAL_ANALYSER_H

#include<vector>
#include<string>

#include"Token.h"



class Lexical_analyser
{    
public:
    Lexical_analyser();

    bool ReadChar(char ch);

    void test(std::string text);
    std::string process(const std::string &text);

    int  GetTokensLength()   { return tokens_.size(); }
    Token GetLastToken()   { return tokens_.back(); }
    const std::vector<Token>& GetTokens()  { return tokens_;}
private:

    std::vector<Token> tokens_;

    TOKENTYPE  state_=TYPE_TEXT;
    std::string char_buffer_="";




};

#endif // LEXICAL_ANALYSER_H
