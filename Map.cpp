#include "Map.h"

#include <iostream>

Map::Map(QSize size) {
    this->size = size;
    createObjectsArray();
}

void Map::createObjectsArray() {
    // std::cout << "w:" << size.width() << std::endl;
    // std::cout << "h:" << size.height() << std::endl;

    for (uint32_t w = 0; w < size.width(); w++) {
        QVector<MapObject*> widthMapVector;
        for (uint32_t h = 0; h < size.height(); h++) {
            widthMapVector.push_back(nullptr);
        }
        objectsArray.push_back(widthMapVector);
    }
}

void Map::print() {
    for (uint32_t w = 0; w < size.width(); w++) {
        for (uint32_t h = 0; h < size.height(); h++) {
            if (objectsArray[w][h] == nullptr) {
                std::cout << "x";
            }
        }
        std::cout << std::endl;
    }
}