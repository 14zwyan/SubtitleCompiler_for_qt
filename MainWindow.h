#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<fstream>
#include<string>

#include <QMainWindow>



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

private:
    Ui::MainWindow *ui;

    std::ifstream file_;
    std::string text_;

};

#endif // MAINWINDOW_H
