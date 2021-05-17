#include "Map.h"

#include <iostream>

Map::Map(QSize size) {
    this->size = size;
    createObjectsArray();
}

Map::Map(JsonObject jsonObject) {
    if ((jsonObject.containsKey(MAP_SIZE_JSON_KEY)) && (jsonObject[MAP_SIZE_JSON_KEY].is<JsonObject>())) {
        JsonObject jsonMapSize = jsonObject[MAP_SIZE_JSON_KEY].as<JsonObject>();
        if ((jsonMapSize.containsKey(MAP_WIDTH_JSON_KEY)) && (jsonMapSize[MAP_WIDTH_JSON_KEY].is<uint32_t>()) && (jsonMapSize.containsKey(MAP_HEIGHT_JSON_KEY)) && (jsonMapSize[MAP_HEIGHT_JSON_KEY].is<uint32_t>())) {
            size.setWidth(jsonObject[MAP_SIZE_JSON_KEY][MAP_WIDTH_JSON_KEY].as<uint32_t>());
            size.setHeight(jsonObject[MAP_SIZE_JSON_KEY][MAP_HEIGHT_JSON_KEY].as<uint32_t>());
            createObjectsArray();

        } else {
            throw std::invalid_argument("Wrong map size values");
        }
    } else {
        throw std::invalid_argument("Map size not declared");
    }
}

void Map::createObjectsArray() {
    for (int w = 0; w < size.width(); w++) {
        QVector<MapObject *> widthMapVector;
        for (int h = 0; h < size.height(); h++) {
            widthMapVector.push_back(nullptr);
        }
        objectsArray.push_back(widthMapVector);
    }
}

bool Map::coordsInMapSize(QPoint coords) {
    if ((coords.x() >= 0) && (coords.x() < size.width()) && (coords.y() >= 0) && (coords.y() < size.height())) {
        return true;
    }
    return false;
}

void Map::addObject(MapObject *object) {
    if (object != nullptr) {
        QPoint coords = object->getCoordinates();
        if ((coords.x() < size.width()) && (coords.y() < size.height())) {
            objectsArray[coords.x()][coords.y()] = object;
            object->setMap(this);
        }
    }
}

MapObject *Map::getMapObject(QPoint coords) {
    if (coordsInMapSize(coords)) {
        return objectsArray[coords.x()][coords.y()];
    }
    return nullptr;
}

void Map::print() {
    for (int h = 0; h < size.height(); h++) {
        for (int w = 0; w < size.width(); w++) {
            if (getMapObject(QPoint(w, h)) != nullptr) {
                std::cout << getMapObject(QPoint(w, h))->getChar();
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}