#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<fstream>
#include<string>
#include<vector>

#include <QMainWindow>


#include"Lexical_analyser.h"
#include"Parser.h"
#include"Subtitle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_get_file_clicked();

    void on_pushButton_lexical_clicked();

    void on_pushButton_parse_clicked();

    void on_pushButton_clicked();

    void show_subtitle();
    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_2_clicked();

private:

    Ui::MainWindow *ui;

    std::ifstream file_;
    std::string text_;
    std::vector<Subtitle> subtitles_;
    Subtitle subtitle_now;
    Lexical_analyser lexical_analyser_;
    Parser parser_;

    double  passed_second=0;
    bool displayed_=false;
    int subtitles_index_=0;

};

#endif // MAINWINDOW_H
