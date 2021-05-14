#include <QApplication>
#include <QLabel>
#include <QVector>
#include <QWidget>
#include <fstream>
#include <iostream>

#include "SimulationManager.h"

int main(int argc, char *argv[]) {
    // std::string filepath = "mapa.json";

    // // QVector<QVector<int> > array[3][3];
    // QVector<int> integerVector;
    // //integerVector.push_back(7);
    // std::cout << integerVector.size();

    // QApplication app(argc, argv);
    // QLabel hello("<center>Welcome to my first Qt program</center>");
    // hello.setWindowTitle("My First Qt Program");
    // hello.resize(400, 400);
    // hello.show();
    //return app.exec();

    new SimulationManager();

    // std::cout << "╔" << std::endl;
    // std::cout << "╚" << std::endl;
    // std::cout << "╝" << std::endl;
    // std::cout << "╗" << std::endl;

    // std::cout << "║" << std::endl;
    // std::cout << "═" << std::endl;

    // std::cout << "╠" << std::endl;
    // std::cout << "╣" << std::endl;
    // std::cout << "╦" << std::endl;
    // std::cout << "╩" << std::endl;
    // std::cout << "╬" << std::endl;
    return 0;
}