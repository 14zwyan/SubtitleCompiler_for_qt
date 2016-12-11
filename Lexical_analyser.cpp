#include "Lexical_analyser.h"

#include<string>
#include<set>
#include<iostream>
#include<vector>
#include<iomanip>

#include<boost/lexical_cast.hpp>

using std::string;  using std::set;
using std::cout;  using std::endl; using std::vector;

Lexical_analyser::Lexical_analyser()
{

}

bool isDigit(string str)
{
    string::iterator begin=str.begin();
    string::iterator end=str.end();

    while( begin != end)
    {
        if( ! ( (*begin) >='0' && (*begin )<= '9')  )
            return false;
        ++begin;
    }
    return true;
}

bool isDigit(char ch)
{
    if(  ch >='0' && ch<= '9')
        return true;
    else
        return false;
}


bool Lexical_analyser::ReadChar(char ch)
{
    bool move_cursor=true;
    TOKENTYPE createType=TYPE_NONE;
    string after_append_ch;

    if( ch)
    {
        after_append_ch=char_buffer_+ch;
        //cout<<"after_append_ch:"<<after_append_ch<<endl; //for test
    }
    else
        after_append_ch=char_buffer_;

    if( state_ == TYPE_TEXT)  //1
    {
        //strip the left part
        int  index=0;
        for( int i=0; after_append_ch[i]==' ' ; ++i) // simulate lstrip
            ++index;
        //cout<<"index: "<<index<<endl;  //for test
        string temp=string( after_append_ch.begin() + index,
                            after_append_ch.end() );
        //cout<<"temp"<<temp<<endl; // for test
        if( isDigit(temp) ) //2
        {
           // cout<<"Is digit"<<endl;
            if ( ch) //3
                char_buffer_+=ch;
            state_=TYPE_COUNTER;
        }
        else if(  ch == '-')  //2
        {
            char_buffer_+=ch;
            state_=TYPE_TIME_ARROW;
            //cout<<"Enter arrow model"<<endl;
        }
        else if(  ch == '\n' || !ch) //2
        {
            if (ch)//3
            {
                char_buffer_+=ch;
                createType=TYPE_TEXT;
            }
            else if( !ch && char_buffer_ .length() ==0 )//3
            {
                createType=TYPE_NONE;
            }
            else //3
            {
                createType=TYPE_TEXT;
                state_=TYPE_TEXT;
            }
        }
        else //2
        {
            if( ch) //3
                char_buffer_ +=ch;
        }





    }

    else if( state_ == TYPE_COUNTER ) //1
    {
         if (ch  && isDigit(ch)) //2
             char_buffer_+=ch;
         else if (ch== '\n' or  !ch) //2
         {
             createType=TYPE_COUNTER;
             state_=TYPE_TEXT;
         }
         else if ( ch == ':') //2
         {
             if( ch) //3
                 char_buffer_+=ch;
             state_=TYPE_TIMESTAMP;
         }
        else //2
         {
             if (ch) //3
                 char_buffer_+=ch;
             state_=TYPE_TEXT;
         }

         //LINE 107

    }


    else if( state_ ==TYPE_TIME_ARROW)//1
    {
        string arrow("-->");

        if (char_buffer_== "-->" && ( !ch || ch=='\n' || ch==' '))//&& ( ch || ch ==' '))//2    a little different
        {
            //cout<<"char_buffer == -->"<<endl;
                if (ch )  // different here 14:51
                    char_buffer_+=ch;
                createType=TYPE_TIME_ARROW;
                state_=TYPE_TEXT;
         }
        else if ( arrow.find( after_append_ch ) !=string::npos  ) //2 a little different
        {
            if (ch)
                char_buffer_+=ch;
            state_=TYPE_TIME_ARROW;
            //cout<<"Arrow"<<endl;
        }
        else //2
        {
            if (ch) //3
                char_buffer_+=ch;
            state_=TYPE_TEXT;
        }
    }

    else if( state_ == TYPE_TIMESTAMP ) //1
    {
        string tempString;
        //remove empty char
        int index;
        for( index=0 ; after_append_ch[index ] == ' '; ++index)
        {
            /*empty statement**/
        }
        tempString=string( after_append_ch.begin() + index,
                           after_append_ch.end());
        int temp_length =tempString.length();

        set<int> a_set={4,5,7,8,10,11,12} ;
        set<int> a_set1={3 ,6};
        if ( a_set.find( temp_length) != a_set.end()  ) //2
        {
            if( ch && isDigit(ch)) //3
            {
                char_buffer_+=ch;
                state_=TYPE_TIMESTAMP;
            }
            else //3
            {
                if(ch) //4
                    char_buffer_+=ch;
                state_=TYPE_TEXT;
            }
        }
        else if ( a_set1.find( temp_length) != a_set1.end() ) //2
        {
            if( ch== ':')  //3
            {
                if( ch) //4
                    char_buffer_+=ch;
                state_=TYPE_TIMESTAMP;
            }
            else //3
            {
                if (ch)//4
                    char_buffer_+=ch;
                state_=TYPE_TEXT;
            }
        }
        else if ( temp_length ==9)//2
        {
            if (ch == ',')//3
            {
                if( ch)
                    char_buffer_+=ch;
                state_=TYPE_TIMESTAMP;
            }
            else
            {
                if( ch)
                    char_buffer_+=ch;
                state_=TYPE_TEXT;
            }
        }
        else //length over 12
        {
            //cout<<"ch"<<ch<<endl;
            if (ch &&( ch == ' ' || ch=='\n') )// a little different line 173
            {
                createType=TYPE_TIMESTAMP;
                state_=TYPE_TEXT;
            }
            else //3
            {
                if (ch)
                    char_buffer_+=ch;
                state_=TYPE_TEXT;
            }
        }


    }

    if( createType != TYPE_NONE)//1
    {
        if( createType == TYPE_TIMESTAMP)//2
        {
            //get hour minute seconds
            string::size_type pos_hour,pos_minute,length;
            length=char_buffer_.length();
            pos_hour= char_buffer_.find_first_of(":");
            pos_minute=char_buffer_.find_first_of(":",pos_hour+1);

           // cout<<"pos_hour "<<pos_hour<<endl;
            //cout<<"pos_minute"<<pos_minute<<endl;
            string hour=char_buffer_.substr(0,pos_hour-1);
            string minute=char_buffer_.substr(pos_hour+1,
                                              pos_minute-pos_hour-1);
            string second=char_buffer_.substr(pos_minute+1);




            /*bug
            pos_minute=char_buffer_.find_first_of(":",pos_hour+1);
            string minute=char_buffer_.substr(pos_hour+1,pos_minute);
            string second=char_buffer_.substr(pos_minute+1, length-1);
            **/

            // change to int
            //cout<<char_buffer_<<endl;
            //cout<<"hour"<<hour<<endl;
            int hour_int=boost::lexical_cast<int>(hour);
            //cout<<"minute"<<minute<<endl;
            int minute_int=boost::lexical_cast<int>(minute);
            int second_int=boost::lexical_cast<int> (second.substr(0,1));

            if( minute_int > 59 || second_int >59)
                createType=TYPE_TEXT;


        }

        set<TYPE> type_set={ TYPE_COUNTER,TYPE_TIMESTAMP,
                             TYPE_TIME_ARROW};
        if ( type_set.find( createType ) != type_set.end() ) //2
        {
            string temp;
            int index;
            for(index=0; char_buffer_[index] == ' '; ++index)
            {
                /*empty**/
            }
            //cout<<"char_buffer"<<char_buffer_<<endl;
            int length=char_buffer_.length();
            char_buffer_=char_buffer_.substr(index);
        }

        tokens_.push_back( Token(createType, char_buffer_));
        //cout<<"tokens.push_back: "<<tokens_.back().type()<<
             // tokens_.back().value()<<endl;
        char_buffer_="";
    }

    return move_cursor;
}



void Lexical_analyser::test(string text)
{
    int i=0;
    char ch=text[0];

    while( i < text.length() )
    {
        //cout<<"reading char"<<ch<<endl;
        if( ReadChar(ch) )
        {
            //cout<<"ReadChar("<<ch<<")"<<" successful"<<endl;
            ++i;
            if( i <text.length() )
                ch=text[i];
            else
                break;
        }
    }

    vector<Token>::iterator begin=tokens_.begin();
    vector<Token>::iterator end=tokens_.end();

    cout<<"[";
    while( begin != end)
    {
        cout<<"\""<<(*begin).PresentType()<<"\""<<", "<<"\""<<(*begin).value()<<"\""<<endl;
        ++begin;
    }
    cout<<"]"<<endl;
    cout<<"Parse end"<<endl;
    cout<<tokens_.size()<<endl;
}
