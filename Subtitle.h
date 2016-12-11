#ifndef SUBTITLE_H
#define SUBTITLE_H

#include<string>
#include<sstream>

#include<boost/lexical_cast.hpp>

class Time
{
public:
    void set_hour(int hour) {    hour_=hour;}
    void set_minute(int minute)  { minute_=minute; }
    void set_second(int  second)  { second_=second; }
    void set_time(std::string time);
    void clear()   { hour_=minute_=second_=msecond_=-1; time_=""; }
    std::string time()  { return time_; }


private:
    int  hour_;
    int  minute_;
    int  second_;
    int msecond_;
    std::string time_;
};

class Subtitle
{
public:
    Subtitle(int counter,Time start, Time end,std::string content):
        counter_(counter), start_time_(start), end_time_(end) ,content_(content)
    {  /*empty **/ }

    std::string counter()  { std::stringstream ss; ss<<counter_;  return ss.str();}
    std::string start_time()  { return start_time_.time();}
    std::string end_time()   { return end_time_.time(); }
    std::string content()  { return content_; }

private:
    int counter_;
    Time start_time_;
    Time end_time_;
    std::string content_;
};

#endif // SUBTITLE_H
