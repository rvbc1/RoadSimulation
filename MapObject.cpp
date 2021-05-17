#include "MapObject.h"

#include "Map.h"

MapObject::MapObject(QPoint coordinates, Map* map) {
    this->coordinates = coordinates;
    setMap(map);
}

MapObject::MapObject(JsonObject jsonObject, Map* map) {
    setMap(map);
    if ((jsonObject.containsKey(MAP_OBJECT_COORDS_JSON_KEY)) && (jsonObject[MAP_OBJECT_COORDS_JSON_KEY].is<JsonObject>())) {
        JsonObject jsonMapObjectCoords = jsonObject[MAP_OBJECT_COORDS_JSON_KEY].as<JsonObject>();
        if ((jsonMapObjectCoords.containsKey(MAP_OBJECT_COORDS_X_JSON_KEY)) && (jsonMapObjectCoords[MAP_OBJECT_COORDS_X_JSON_KEY].is<uint32_t>()) && (jsonMapObjectCoords.containsKey(MAP_OBJECT_COORDS_Y_JSON_KEY)) && (jsonMapObjectCoords[MAP_OBJECT_COORDS_Y_JSON_KEY].is<uint32_t>())) {
            coordinates.setX(jsonMapObjectCoords[MAP_OBJECT_COORDS_X_JSON_KEY].as<uint32_t>());
            coordinates.setY(jsonMapObjectCoords[MAP_OBJECT_COORDS_Y_JSON_KEY].as<uint32_t>());
        } else {
            throw std::invalid_argument("Wrong object coordinates values");
        }

    } else {
        throw std::invalid_argument("Object coordinates not defined");
    }
}

MapObject* MapObject::getNeighborhoodMapObject(Direction direction, Type type) {
    if(type == WHATEVER){
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

MapObject::Type MapObject::getType(){
    return type;
}

std::string MapObject::getChar() {
    return "-";
}

void MapObject::setMap(Map* map) {
    this->map = map;
}

Map*  MapObject::getMap(){
    return map;
}

QPoint MapObject::getCoordinates() {
    return coordinates;
}