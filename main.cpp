#include <QApplication>
#include <QLabel>
#include <QVector>
#include <QWidget>

#include <iostream>

#include "ArduinoJson-v6.18.0.h"
#include <fstream>

#include "SimulationManager.h"

#define JSON_DOCUMENT_SIZE 10000

int main(int argc, char *argv[]) {
    // std::string filepath = "mapa.json";

    // StaticJsonDocument<JSON_DOCUMENT_SIZE> doc;
    // std::ifstream interfaceJsonFile(filepath);

    // DeserializationError error = deserializeJson(doc, interfaceJsonFile);
    // if (error) {
    //     std::cout << filepath;
    //     std::cout << " Json deserialize failed: ";
    //     std::cout << error << std::endl;
    // } else {
    //     //return loadMenuItem(doc.as<JsonVariant>());
    // }
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
    return 0;
}