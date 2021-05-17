#include "MapBuilder.h"

#include <iostream>

Map* MapBuilder::loadMapFromFile(std::string filepath) {
    StaticJsonDocument<JSON_DOCUMENT_SIZE> doc;
    std::ifstream interfaceJsonFile(filepath);

    DeserializationError error = deserializeJson(doc, interfaceJsonFile);
    if (error) {
        throw std::runtime_error("Json deserialize failed");
    } else {
        return loadMap(doc.as<JsonVariant>());
    }

    return nullptr;
}

Map* MapBuilder::loadMap(JsonObject jsonObject) {
    Map* map = new Map(jsonObject);
    if ((jsonObject.containsKey("objects")) && (jsonObject["objects"].is<JsonArray>())) {
        JsonArray objectsArray = jsonObject["objects"].as<JsonArray>();
        for (JsonVariant v : objectsArray) {
            if ((v.containsKey(MAP_OBJECT_TYPE_JSON_KEY)) && (v[MAP_OBJECT_TYPE_JSON_KEY].is<std::string>())) {
                std::string mapObjectType = v[MAP_OBJECT_TYPE_JSON_KEY].as<std::string>();
                if (mapObjectType == ROAD_OBJECT_TYPE_JSON_VALUE) {
                    map->addObject(new Road(v.as<JsonObject>()));
                }

            } else {
                map->addObject(new MapObject(v.as<JsonObject>(), map));
            }
        }
    }
    return map;
}