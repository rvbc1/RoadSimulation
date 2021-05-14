#include "MapObject.h"

MapObject::MapObject(QPoint coordinates) {
    this->coordinates = coordinates;
}

MapObject::MapObject(JsonObject jsonObject) {
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

char MapObject::getChar(){
    return '╬';
}

QPoint MapObject::getCoordinates() {
    return coordinates;
}