#include "MapBuilder.h"

#include <iostream>

Map* MapBuilder::loadMapFromFile(std::string filepath) {
    StaticJsonDocument<JSON_DOCUMENT_SIZE> doc;
    std::ifstream interfaceJsonFile(filepath);

    DeserializationError error = deserializeJson(doc, interfaceJsonFile);
    if (error) {
        std::cout << filepath;
        std::cout << " Json deserialize failed: ";
        std::cout << error << std::endl;
        // return nullptr;
        return new Map(QSize(4, 3));
    } else {
        return loadMap(doc.as<JsonVariant>());
    }

    return nullptr;
}

Map* MapBuilder::loadMap(JsonObject jsonObject) {
    if ((jsonObject.containsKey(MAP_WIDTH_JSON_KEY)) && (jsonObject[MAP_WIDTH_JSON_KEY].is<uint32_t>()) && (jsonObject.containsKey(MAP_HEIGHT_JSON_KEY)) && (jsonObject[MAP_HEIGHT_JSON_KEY].is<uint32_t>())) {
        QSize mapSize;
        mapSize.setWidth(jsonObject[MAP_WIDTH_JSON_KEY].as<uint32_t>());
        mapSize.setHeight(jsonObject[MAP_HEIGHT_JSON_KEY].as<uint32_t>());
        return new Map(mapSize);
    }
    return nullptr;
}