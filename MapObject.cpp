#include "MapObject.h"

#include <QDebug>

#include "Map.h"

MapObject::MapObject(QPoint coordinates, Map *map) {
    this->coordinates = coordinates;
    setMap(map);
}

MapObject::MapObject(JsonObject jsonObject, Map *map) {
    setMap(map);
    coordinates = MapObject::parseCoordinates(jsonObject);
}

QPoint MapObject::parseCoordinates(JsonObject jsonObject) {
    QPoint coordinates;
    if ((jsonObject.containsKey(MAP_OBJECT_COORDS_JSON_KEY)) && (jsonObject[MAP_OBJECT_COORDS_JSON_KEY].is<JsonObject>())) {
        JsonObject coordinatesJsonObject = jsonObject[MAP_OBJECT_COORDS_JSON_KEY].as<JsonObject>();
        if ((coordinatesJsonObject.containsKey(MAP_OBJECT_COORDS_X_JSON_KEY)) && (coordinatesJsonObject[MAP_OBJECT_COORDS_X_JSON_KEY].is<uint32_t>()) && (coordinatesJsonObject.containsKey(MAP_OBJECT_COORDS_Y_JSON_KEY)) && (coordinatesJsonObject[MAP_OBJECT_COORDS_Y_JSON_KEY].is<uint32_t>())) {
            coordinates.setX(coordinatesJsonObject[MAP_OBJECT_COORDS_X_JSON_KEY].as<uint32_t>());
            coordinates.setY(coordinatesJsonObject[MAP_OBJECT_COORDS_Y_JSON_KEY].as<uint32_t>());
        } else {
            throw std::invalid_argument("Wrong object coordinates values");
        }
    } else {
        throw std::invalid_argument("Object coordinates not defined");
    }
    return coordinates;
}

MapObject::Direction MapObject::getOppositeDirection(Direction direction){
    switch (direction) {
        case UP:
            return DOWN;
            break;
        case DOWN:
            return UP;
            break;
        case LEFT:
            return RIGHT;
            break;
        case RIGHT:
            return LEFT;
            break;
    }
}

MapObject *MapObject::getNeighborhoodMapObject(Direction direction, Type type) {
    if (type == WHATEVER) {
        type = this->getType();
    }
    if (map == nullptr) {
        return nullptr;
    }
    switch (direction) {
        case UP:
            return map->getMapObject(QPoint(coordinates.x(), coordinates.y() - 1), type);
            break;
        case DOWN:
            return map->getMapObject(QPoint(coordinates.x(), coordinates.y() + 1), type);
            break;
        case LEFT:
            return map->getMapObject(QPoint(coordinates.x() - 1, coordinates.y()), type);
            break;
        case RIGHT:
            return map->getMapObject(QPoint(coordinates.x() + 1, coordinates.y()), type);
            break;
    }
    return nullptr;
}

MapObject::Type MapObject::getType() {
    return type;
}

std::string MapObject::getChar() {
    return "-";
}

void MapObject::setMap(Map *map) {
    this->map = map;
}

Map *MapObject::getMap() {
    return map;
}

void MapObject::setCoordinates(QPoint coordinates) {
    this->map->moveObject(coordinates, this);
    this->coordinates = coordinates;
}

QPoint MapObject::getCoordinates() {
    return coordinates;
}

void MapObject::prepareJsonObject(JsonObject &jsonObject) {
    prepareBasicJsonObject(jsonObject);
}

void MapObject::prepareCoordinates(JsonObject &jsonObject) {
    Map::prepareCoordinatesJsonObject(getCoordinates(), jsonObject);
    // jsonObject["coordinates"]["x"] = getCoordinates().x();
    // jsonObject["coordinates"]["y"] = getCoordinates().y();
}

void MapObject::prepareBasicJsonObject(JsonObject &jsonObject) {
    prepareCoordinates(jsonObject);

    if (Road *road = dynamic_cast<Road *>(this)) {
        jsonObject["type"] = "road";
    } else if (Vehicle *vehicle = dynamic_cast<Vehicle *>(this)) {
        jsonObject["type"] = "vehicle";
    }
    prepareInheritJsonObject(jsonObject);
}

MapObject::~MapObject() {
    this->map->removeObject(this);
}