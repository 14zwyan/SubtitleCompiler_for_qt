#include <iostream>
#include<string>
#include<fstream>

#include "MainWindow.h"
#include <QApplication>

#include"Lexical_analyser.h"
#include"Parser.h"


using std::ifstream; using std::string; using std::cout; using std::endl;

int main(int argc, char *argv[])
{
    /*
    ifstream    lexical_test_file("testString");
    string text;
    char ch;
    while( lexical_test_file.get(ch) )
    {
        text+=ch;
    }

    cout<<text;
    //Lexical_analyser lex_analyser;
    //lex_analyser.test(text);
    Parser parser;
    parser.test(text);
    **/


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}







