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
    return new Map(jsonObject);
}