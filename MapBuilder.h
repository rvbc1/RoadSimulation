#ifndef MapBuilder_h
#define MapBuilder_h

#include <fstream>

#include "ArduinoJson-v6.18.0.h"
#include "Map.h"

#define JSON_DOCUMENT_SIZE 10000

#define MAP_WIDTH_JSON_KEY "width"
#define MAP_HEIGHT_JSON_KEY "height"

class MapBuilder {
   public:
    static Map* loadMapFromFile(std::string filepath);

   protected:
   private:
      static Map* loadMap(JsonObject jsonObject);
};

#endif