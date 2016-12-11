#include<string>
#include<fstream>

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

}
