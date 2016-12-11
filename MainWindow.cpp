#include<string>
#include<fstream>
#include<utility>
#include<QMessageBox>
#include<QTime>
#include<QTimer>

#include "MainWindow.h"
#include "ui_MainWindow.h"



using std::string;  using std::ifstream;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_get_file_clicked()
{
    QString q_file_name=ui->lineEdit_filename->text();
    string  file_name=q_file_name.toStdString();

    file_.open(file_name);
    char ch;
    while ( file_.get(ch))
    {
        text_+=ch;
    }

    QString text=QString::fromStdString(text_);

    ui->textBrowser_source->setText(text);

    file_.close();

}



void MainWindow::on_pushButton_lexical_clicked()
{
    lexical_analyser_.clear();
    string result= lexical_analyser_.process(text_);

    QString q_result=QString(QString::fromLocal8Bit(result.c_str()));

    ui->textBrowser_result->setText(q_result);
}

void MainWindow::on_pushButton_parse_clicked()
{
    parser_.clear();
    std::pair<string,bool> result=parser_.DoParse_For_Qt(text_);
    subtitles_=parser_.subtitles();
    //parser_.clear();
    //parser_.DoParse(text_);

    if (result.second)
    {
        ui->textBrowser_result->setText( QString::fromStdString(result.first));
    }
    else
    {
        QString error=QString::fromStdString(result.first);
        QMessageBox::information(NULL,"Error",error);
        //QMessageBox(,"Error",error);
    }
}

void MainWindow::on_pushButton_clicked()  //button display
{
    if(subtitles_.size()  ==0 )
    {
        QMessageBox::information(NULL,"Error","Parse First");
    }
    else
    {
        ui->textBrowser_result->clear();
        QTimer * timer=new QTimer(this);
        connect(timer, SIGNAL(timeout()), this , SLOT(show_subtitle() )  );
        timer->start(100);

//        std::cout<<"In"<<std::endl;

//        int index=0;
//        while (index  != subtitles_.size() )
//        {
//            QTime t;
//            t.start();
//            Subtitle subtitle=subtitles_[index];
//            Time  start_time=subtitle.start_time_real();
//            Time end_time=subtitle.end_time_real();
//            bool displayed=false;



//            long int start_hour=start_time.hour();
//            long int start_minute=start_time.minute();
//            long int start_second=start_time.second();
//            long int start_msecond=start_time.msecond();

//            long int end_hour=end_time.hour();
//            long int end_minute=end_time.minute();
//            long int end_second=end_time.second();
//            long int end_msecond=end_time.msecond();

//            long int diff_time=(end_hour-start_hour)*3600*1000+
//                    (end_minute-start_minute)*60*1000+(end_second-start_second)*1000+end_msecond-start_msecond;
//            long int end_time_ms=end_hour*3600*1000+end_minute*60*1000+end_second*1000+end_msecond;

//            string str=subtitle.counter()+'\n'+subtitle.start_time()+subtitle.end_time()+subtitle.content();
//            std::cout<<"Str"<<str<<std::endl;
//            QString qstr=QString::fromStdString( str);
//            //std::cout<<"qstr"<<qstr.toStdString()<<std::endl;
////            while (true)
////            {
////               //QTime current_time=QTime::currentTime();
////               int passed_time=t.elapsed();
////              // std::cout<<passed_time<<std::endl;
////                if( (! displayed)  && ( passed_time >=diff_time))
////                {
////                    std::cout<<"show"<<std::endl;
////                    //std::cout<<str<<std::endl;
////                    ui->textBrowser_result->append(qstr);
////                    displayed=true;
////                }
////                if (passed_time > end_time_ms)
////                {
////                    ui->textBrowser_result->clear();
////                    break;
////                }
////            }


//            ++index;
        }



}


void MainWindow::show_subtitle()
{
       //std::cout<<"enter timer"<<std::endl;
        passed_second+=0.1;
       if( subtitles_index_ != subtitles_.size() )
       {
           Subtitle subtitle=subtitles_[subtitles_index_];
           Time begin_time=subtitle.start_time_real();
           Time end_time=subtitle.end_time_real();
           int begin_second=begin_time.hour()*3600+begin_time.minute()*60
                   +begin_time.second();
           //std::cout<<"begin second"<<begin_second<<std::endl;
           int end_second=end_time.hour()*3600+end_time.minute()*60
                   +end_time.second();
          if (!displayed_ && passed_second>begin_second && passed_second <end_second)
          {
              std::cout<<"print"<<std::endl;
              displayed_=true;
              string str=subtitle.counter()+"\n"+subtitle.start_time()+"--> "+subtitle.end_time()+"\n"+
                      subtitle.content();
              QString qstr=QString::fromStdString(str);
              ui->textBrowser_result->setText(qstr);
          }
          else if( passed_second >end_second && displayed_)
          {
              ui->textBrowser_result->clear();
             subtitles_index_++;
             displayed_=false;
          }
       }


}

void MainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{

}

void MainWindow::on_pushButton_2_clicked()
{
    QString qchange_time=ui->lineEdit->text();
    int change_time=boost::lexical_cast<int> ( qchange_time.toStdString() );
    //std::cout<<"change_time"<<change_time<<std::endl;
    std::vector<Subtitle>::iterator begin=subtitles_.begin();
    std::vector<Subtitle>::iterator  end=subtitles_.end();


    while( begin != end)
    {
        Time old_start=(*begin).start_time_real();
       Time old_end=(*begin).end_time_real();
       Time new_start=Time();
       Time new_end=Time();

       int old_second_start=old_start.change_to_second();
       int old_second_end=old_end.change_to_second();
       //get seconds
       //change seconds
       int new_second_start=old_second_start+change_time;
       int new_second_end=old_second_end+change_time;
       std::cout<<"new second end"<<new_second_end<<std::endl;

       int new_start_hour=new_second_start/3600;
       int new_start_minute=(new_second_start%3600)/60;
       int new_start_second=(new_second_start%3600)%60;

       int new_end_hour=new_second_end/3600;
       int new_end_minute=( new_second_end %3600)/60;
       int new_end_second=(new_second_end%3600)%60;

        std::cout<<"new_start_second"<<new_start_second<<std::endl;
        std::cout<<"new_end_second"<<new_end_second<<std::endl;

        (*begin).set_start_time( new_start_hour, new_start_minute, new_start_second)  ;
       //(*begin).set_end_time( new_end_hour, new_end_minute, new_end_second);
        (*begin).set_end_time(new_end_hour , new_end_minute ,new_end_second);
        std::cout<<"Change start"<<(*begin).start_time()<<std::endl;
        std::cout<<"Change end"<<(*begin).end_time()<<std::endl;

        ++begin;
    }

}
