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

MapObject* MapObject::getNeighborhoodMapObject(Direction direction) {
    if (map == nullptr) {
        return nullptr;
    }
    switch (direction) {
        case UP:
            return map->getMapObject(QPoint(coordinates.x(), coordinates.y() - 1));
            break;
        case DOWN:
            return map->getMapObject(QPoint(coordinates.x(), coordinates.y() + 1));
            break;
        case LEFT:
            return map->getMapObject(QPoint(coordinates.x() - 1, coordinates.y()));
            break;
        case RIGHT:
            return map->getMapObject(QPoint(coordinates.x() + 1, coordinates.y()));
            break;
    }
}

std::string MapObject::getChar() {
    return "-";
}

void MapObject::setMap(Map* map) {
    this->map = map;
}

QPoint MapObject::getCoordinates() {
    return coordinates;
}