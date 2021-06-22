#ifndef Road_h
#define Road_h

#include <QVector>

#include "MapObject.h"

#define ROAD_OBJECT_TYPE_JSON_VALUE "road"

class Road : public MapObject {
   public:
    Road(QPoint coordinates);
    Road(JsonObject jsonObject);

    std::string getChar();

    QVector<Road*> getAvailableRoads();
    QVector<Direction> getAvailableDirections();

   protected:
   private:
};

#endif