#include<iostream>
#include<string>

#include<boost/lexical_cast.hpp>

#include "Subtitle.h"


using std::string ;

void Time::set_time(string time)
{
    int pos_hour=time.find_first_of(":") ;
    int pos_minute=time.find_first_of(":",pos_hour+1);
    int pos_second=time.find_first_of(",",pos_minute);

    string temp_hour=time.substr(0,pos_hour-1);
    string temp_minute=time.substr( pos_hour+1 , pos_minute-pos_hour-1);
    string temp_second= time.substr(pos_minute+1, pos_second-pos_minute-1 );
    string temp_msecond =time.substr(pos_second+1);

    hour_=boost::lexical_cast<int>( temp_hour);
    minute_=boost::lexical_cast<int> ( temp_minute);
    second_ = boost::lexical_cast<int> ( temp_second);
    msecond_ = boost::lexical_cast<int> (temp_msecond);

}


