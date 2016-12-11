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

    int hour()  { return hour_; }
    int minute()  { return minute_; }
    int second()   { return second_; }
    int msecond()    { return msecond_; }

    int change_to_second ()  {  return hour_*3600+minute_*60+second_; }
    int change_time(int hour, int minute, int second)   { hour_=hour; minute_=minute; second_=second;};
    int change_time_string()
    {
        std::stringstream ss;
        ss<<hour_;
        std::string hour_str;  ss>>hour_str;
        if( hour_str.length() ==1)
        {
            hour_str="0"+hour_str;
        }
        ss.clear();
        ss<<minute_;
        std::string minute_str;  ss>>minute_str;
        if( minute_str.length() == 1)
        {
            minute_str="0"+minute_str;
        }
        ss.clear();
        ss<<second_;
        std::string second_str;  ss>>second_str;
        if( second_str.length() ==1)
        {
            second_str="0"+second_str;
        }
        ss.clear();
        ss<<msecond_;
        std::string msecond_str; ss>>msecond_str;
        if(msecond_str.length()==1)
        {
            msecond_str="00"+msecond_str;
        }
        else if( msecond_str.length() ==2)
        {
            msecond_str="0"+msecond_str;
        }
        time_=hour_str+":"+minute_str+":"+second_str+","+msecond_str;

    }



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
    Subtitle()  { /**/};

    std::string counter()  { std::stringstream ss; ss<<counter_;  return ss.str();}
    std::string start_time()  { return start_time_.time();}
    std::string end_time()   { return end_time_.time(); }
    std::string content()  { return content_; }

    Time   start_time_real()   { return start_time_;}
    Time end_time_real()   { return end_time_; }

    void set_start_time(int hour, int minute,int second)
    {
        start_time_.change_time(hour, minute,second);
        start_time_.change_time_string();
    }

    void set_end_time (int hour, int minute ,int second)
    {
        std::cout<<"in set end time second"<<second<<std::endl;
        end_time_.change_time(hour,minute,second);
        end_time_.change_time_string();
    }

private:
    int counter_;
    Time start_time_;
    Time end_time_;
    std::string content_;
};

#endif // SUBTITLE_H
