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
        QVector<QVector<MapObject *>> widthMapVector;
        for (int h = 0; h < size.height(); h++) {
            QVector<MapObject *> areaMapVector;
            widthMapVector.push_back(areaMapVector);
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

void Map::addDriver(Driver *driver){
    driversContainer.push_back(driver);
}

QVector<Driver *> Map::getDrivers(){
    QVector<Driver *> returnVector(driversContainer);
    return returnVector;
}

void Map::addObject(MapObject *object) {
    if (object != nullptr) {
        QPoint coords = object->getCoordinates();
        if ((coords.x() < size.width()) && (coords.y() < size.height())) {
            if(getMapObject(coords, object->getType()) == nullptr){
            objectsArray[coords.x()][coords.y()].push_back(object);
            object->setMap(this);
            } else {
                throw std::runtime_error("Object exists");
            }
        }
    }
}

void Map::removeObject(MapObject *object) {
    if (object != nullptr) {
        QPoint coords = object->getCoordinates();
        if ((coords.x() < size.width()) && (coords.y() < size.height())) {
            objectsArray[coords.x()][coords.y()].removeOne(object);
        }
    }
}

MapObject *Map::getMapObject(QPoint coords, MapObject::Type type) {
    QVector<MapObject *> areaMapObjectsVector = getMapObjectVector(coords);
    for (int i = 0; i < areaMapObjectsVector.size(); i++) {
        if (type == MapObject::WHATEVER) {
            return areaMapObjectsVector[i];
        } else {
            if (areaMapObjectsVector[i]->getType() == type) {
                return areaMapObjectsVector[i];
            }
        }
    }
    return nullptr;
}

QVector<MapObject *> Map::getMapObjectVector(QPoint coords) {
    if (coordsInMapSize(coords)) {
        QVector<MapObject *> returnVector(objectsArray[coords.x()][coords.y()]);
        return returnVector;
    }
    QVector<MapObject *> emptyVector;
    return emptyVector;
}

QSize Map::getSize(){
    return size;
}

void Map::prepareJsonObject(JsonObject &jsonObject){
    JsonObject jsonSize = jsonObject.createNestedObject(MAP_SIZE_JSON_KEY);
    jsonSize[MAP_WIDTH_JSON_KEY] = size.width();
    jsonSize[MAP_HEIGHT_JSON_KEY] = size.height();

    JsonArray jsonMapObjects = jsonObject.createNestedArray(MAP_OBJECTS_ARRAY_JSON_KEY);

     for (int w = 0; w < getSize().width(); w++) {
        for (int h = 0; h < getSize().height(); h++) {
            QVector<MapObject *> objects = getMapObjectVector(QPoint(w, h));
            for (MapObject *object : objects) {
                JsonObject mapObjectJson = jsonMapObjects.createNestedObject();
                object->prepareJsonObject(mapObjectJson);
                //JsonObject mapObjectJson = jsonMapObjects.createNestedObject();
                // mapObjectJson["coordinates"]["x"] = object->getCoordinates().x();
                // mapObjectJson["coordinates"]["y"] = object->getCoordinates().y();
                // if (Road *road = dynamic_cast<Road *>(object)) {
                //     mapObjectJson["type"] = "road";
                // } else if (Vehicle *vehicle = dynamic_cast<Vehicle *>(object)) {
                //     mapObjectJson["type"] = "vehicle";
                // }
            }
        }
    }

}

void Map::print() {
    for (int h = 0; h < size.height(); h++) {
        for (int w = 0; w < size.width(); w++) {
            if (getMapObject(QPoint(w, h), MapObject::VEHICLE) != nullptr) {
                std::cout << getMapObject(QPoint(w, h), MapObject::VEHICLE)->getChar();
            } else if (getMapObject(QPoint(w, h)) != nullptr) {
                std::cout << getMapObject(QPoint(w, h))->getChar();
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}