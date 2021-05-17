#ifndef Road_h
#define Road_h

#include "MapObject.h"

#define ROAD_OBJECT_TYPE_JSON_VALUE "road"

class Road : public MapObject {
   public:
    Road(QPoint coordinates);
    Road(JsonObject jsonObject);

    std::string getChar();

   protected:
   private:
};

#endif