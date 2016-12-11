
#include<vector>
#include<string>
#include<iostream>
#include<utility>

#include<boost/lexical_cast.hpp>


#include "Parser.h"
#include"Subtitle.h"

using std::vector; using std::string;
using std::cout; using std::endl;
using std::pair;

Parser::Parser()
{

}


void Parser::DoParse(const  string  &content)
{
    vector<Subtitle> subtitles;
    int number=0;
    Time start_time=Time();
    Time end_time=Time();
    int i=0;
    char ch=content[i];
    int token_count=0;
    std::string text="";
    state_=START;

    while( i != content.length() ) //1
    {
        bool move_cursor=lexical_analyser_.ReadChar(ch);
        int tokens_length=lexical_analyser_.GetTokensLength();
        if( tokens_length > token_count) //2
        {
            ++token_count;
            Token new_token=lexical_analyser_.GetLastToken();
            // judge whether it is a legal token  line48
            if(state_ == START) //3
            {
                if(  new_token.type() != TYPE_COUNTER) //4
                {
                    cout<<"Expect type counter"<<endl;
                    return ;
                }
                cout<<"COUNTER"<<new_token.value()<<endl;
                number=boost::lexical_cast<int>( new_token.value() );
                state_=COUNTER;
            }

            else if( state_ == COUNTER) //3
            {
                if( new_token.type() != TYPE_TIMESTAMP) //4
                {
                    cout<<"ERROR: EXPECT TIMESTAMP"<<endl;
                    return ;
                }
                cout<<"START TIME"<<new_token.value();
                start_time.set_time( new_token.value() );
                state_=START_TIME;
            }

            else if( state_ == START_TIME) //3
            {
                if ( new_token.type() != TYPE_TIME_ARROW) //4
                {
                    cout<<"ERROR, EXPECT ARROW"<<endl;
                    return ;
                }
               cout<<new_token.value();
               state_=ARROW;
            }

            else if( state_ == ARROW) //3
            {
                if (new_token.type() != TYPE_TIMESTAMP) //4
                {
                    cout<<"Error , TIMESTAMP expect"<<endl;
                    return ;
                }
                cout<<"End time"<<new_token.value()<<endl;
                end_time.set_time(new_token.value());
                state_=END_TIME;
            }

            else if( state_ == END_TIME || state_==TEXT)  //3
            {
                if (new_token.value() != "\n") //4
                {
                    state_=TEXT;
                    cout<<"Text :"<<new_token.value()<<endl;
                    if ( ! (new_token.value().back() == '\n') ) //5
                    {
                        string temp=new_token.value();
                        temp+="\n";
                        new_token.set_value( temp);
                    }
                    text+=new_token.value();
                }
                else //4
                {
                    state_==START;
                    cout<<"----------------A SUBTITLE-------"<<endl;
                    Subtitle temp_subtitle=Subtitle(number,start_time,end_time,text);
                    subtitles.push_back( temp_subtitle);

                    number=0;
                    start_time.clear(); end_time.clear();
                    text="";
                }


            }


        }

        if ( move_cursor )
        {
            ++i;
            if( i <  content.length())
                ch=content[i];
            else
                break;
        }
    }
    subtitles_=subtitles;

//    cout<<"Tokens"<<endl;
//    for (auto token : lexical_analyser_.GetTokens() )
//    {
//        cout<<token.PresentType()<<", "<<token.value()<<", ";
//    }
//    cout<<endl;


}


pair<string,bool> Parser::DoParse_For_Qt(const  string  &content)
{
   // bool yes=true;
    vector<Subtitle> subtitles;
    int number=0;
    Time start_time=Time();
    Time end_time=Time();
    int i=0;
    char ch=content[i];
    int token_count=0;
    std::string text="";

   // cout<<"contenct"<<content<<endl;
    while( i != content.length() ) //1
    {
        bool move_cursor=lexical_analyser_.ReadChar(ch);
        int tokens_length=lexical_analyser_.GetTokensLength();
        if( tokens_length > token_count) //2
        {
            ++token_count;
            Token new_token=lexical_analyser_.GetLastToken();
            // judge whether it is a legal token  line48
            if(state_ == START) //3
            {
               // cout<<"In start"<<endl;
                if(  new_token.type() != TYPE_COUNTER) //4
                {
                    cout<<"Expect type counter"<<endl;
                    //yes=false;
                    return pair<string,bool> (" Expect type counter ",false);
                }
                cout<<"COUNTER"<<new_token.value()<<endl;
                number=boost::lexical_cast<int>( new_token.value() );
                state_=COUNTER;
            }

            else if( state_ == COUNTER) //3
            {
                if( new_token.type() != TYPE_TIMESTAMP) //4
                {
                    cout<<"ERROR: EXPECT TIMESTAMP"<<endl;
                    return pair<string,bool> ("ERROR: EXPECT TIMESTAMP",false);
                }
                cout<<"START TIME"<<new_token.value();
                start_time.set_time( new_token.value() );
                state_=START_TIME;
            }

            else if( state_ == START_TIME) //3
            {
                if ( new_token.type() != TYPE_TIME_ARROW) //4
                {
                    cout<<"ERROR, EXPECT ARROW"<<endl;
                    return pair<string,bool> ("ERROR:EXPECT ARROW",false);
                }
               cout<<new_token.value();
               state_=ARROW;
            }

            else if( state_ == ARROW) //3
            {
                if (new_token.type() != TYPE_TIMESTAMP) //4
                {
                    cout<<"Error , TIMESTAMP expect"<<endl;
                    return pair<string,bool> ("Error, TIMESTAMP expect",false);
                }
                cout<<"End time"<<new_token.value()<<endl;
                end_time.set_time(new_token.value());
                state_=END_TIME;
            }

            else if( state_ == END_TIME || state_==TEXT)  //3
            {
                //cout<<"In END"<<state_<<endl;
                if (new_token.value() != "\n") //4
                {
                    state_=TEXT;
                    cout<<"Text :"<<new_token.value()<<endl;
                    if ( ! (new_token.value().back() == '\n') ) //5
                    {
                        string temp=new_token.value();
                        temp+="\n";
                        new_token.set_value( temp);
                    }
                    text+=new_token.value();
                }
                else
                {
                    state_=START;
                    cout<<"----------------A SUBTITLE-------"<<endl;
                    Subtitle temp_subtitle=Subtitle(number,start_time,end_time,text);
                    subtitles.push_back( temp_subtitle);

                    number=0;
                    start_time.clear(); end_time.clear();
                    text="";
                }


            }


        }

        if ( move_cursor )
        {
            ++i;
            if( i <  content.length())
                ch=content[i];
            else
                break;
        }
    }


    /*
    cout<<"Tokens"<<endl;
    string result="[";
    string double_quote="\"";
    for (auto token : lexical_analyser_.GetTokens() )
    {
        cout<<token.PresentType()<<", "<<token.value()<<", ";
        result+=double_quote+token.PresentType()+double_quote+","+double_quote+token.value()+double_quote+",";
    }
    result+="]";
    cout<<endl;
    **/
    //print_tokens();
    vector<Subtitle>::iterator begin=subtitles.begin();
    vector<Subtitle>::iterator end=subtitles.end();
    string result="";
    string newline="\n";
    cout<<"Subtitles"<<subtitles.size()<<endl;
    while ( begin != end)
    {
        cout<<endl;
        result+="-------------A subtitle------------------\n";
        result+="Counter:  "+(*begin).counter()+newline;
        result+="Start time:"+ (*begin).start_time()+newline;
        result+="End time:"+ (*begin).end_time() +newline;
        result+="Content"+(*begin).content()+newline;
        result+="-----------------------------------------------";

        ++begin;
    }

    subtitles_=subtitles;
    return pair<string,bool>(result,true);


}

void Parser::print_tokens()
{
    cout<<"Tokens"<<endl;
    string result="[";
    string double_quote="\"";
    for (auto token : lexical_analyser_.GetTokens() )
    {
        cout<<token.PresentType()<<", "<<token.value()<<", ";
        result+=double_quote+token.PresentType()+double_quote+","+double_quote+token.value()+double_quote+",";
    }
    result+="]";
    cout<<endl;

}

void Parser::test(  const string &text)
{
    DoParse(text);
}
