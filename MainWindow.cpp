#include<string>
#include<fstream>
#include<utility>
#include<QMessageBox>


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
    string result= lexical_analyser_.process(text_);

    QString q_result=QString(QString::fromLocal8Bit(result.c_str()));

    ui->textBrowser_result->setText(q_result);
}

void MainWindow::on_pushButton_parse_clicked()
{
    std::pair<string,bool> result=parser_.DoParse_For_Qt(text_);

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
