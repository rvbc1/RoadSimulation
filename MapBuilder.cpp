#include "MapBuilder.h"

#include <QDebug>
#include <iostream>

#include "Driver.h"

Map* MapBuilder::loadMapFromFile(std::string filepath) {
    StaticJsonDocument<JSON_DOCUMENT_SIZE> jsonDocument;
    std::ifstream mapJsonFile(filepath);

    DeserializationError error = deserializeJson(jsonDocument, mapJsonFile);
    if (error) {
        throw std::runtime_error("Json deserialize failed");
    } else {
        return loadMap(jsonDocument.as<JsonVariant>());
    }

    return nullptr;
}

Map* MapBuilder::loadMap(JsonObject jsonObject) {
    Map* map = new Map(jsonObject);
    if ((jsonObject.containsKey(MAP_OBJECTS_ARRAY_JSON_KEY)) && (jsonObject[MAP_OBJECTS_ARRAY_JSON_KEY].is<JsonArray>())) {
        JsonArray objectsArray = jsonObject[MAP_OBJECTS_ARRAY_JSON_KEY].as<JsonArray>();
        for (JsonVariant v : objectsArray) {
            if ((v.containsKey(MAP_OBJECT_TYPE_JSON_KEY)) && (v[MAP_OBJECT_TYPE_JSON_KEY].is<std::string>())) {
                std::string mapObjectType = v[MAP_OBJECT_TYPE_JSON_KEY].as<std::string>();
                if (mapObjectType == ROAD_OBJECT_TYPE_JSON_VALUE) {
                    map->addObject(new Road(v.as<JsonObject>()));
                } else if (mapObjectType == VEHICLE_OBJECT_TYPE_JSON_VALUE) {
                    //map->addObject(new Vehicle(v.as<JsonObject>()));
                    map->addDriver(new Driver(v.as<JsonObject>(), map));
                }

            } else {
                map->addObject(new MapObject(v.as<JsonObject>(), map));
            }
        }
    }
    return map;
}

void MapBuilder::saveMapToFile(Map* map, std::string filepath) {
    StaticJsonDocument<JSON_DOCUMENT_SIZE> jsonDocument;
    JsonObject jsonObject = jsonDocument.to<JsonObject>();

    map->prepareJsonObject(jsonObject);

    try {
        std::ofstream mapJsonFile(filepath, std::ofstream::out);

        serializeJsonPretty(jsonDocument, mapJsonFile);
        mapJsonFile.close();
    } catch (std::ios_base::failure& e) {
        qDebug() << "some wierd error";
    }
}