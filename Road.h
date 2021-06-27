#ifndef Road_h
#define Road_h

#include <QVector>

#include "MapObject.h"

#define ROAD_OBJECT_TYPE_JSON_VALUE "road"

class Road : public MapObject {
   public:
   enum Orientation{
      HORIZONTAL_UP,
      HORIZONTAL_DOWN,
      HORIZONTAL,
      VERTICAL_LEFT,
      VERTICAL_RIGHT,
      VERTICAL,
      UP_LEFT,
      UP_RIGHT,
      DOWN_LEFT,
      DOWN_RIGHT,
      CROSS
   };
    Road(QPoint coordinates);
    Road(JsonObject jsonObject);

    std::string getChar();

    Orientation getOrientation();

    QVector<Road*> getAvailableRoads();
    QVector<Direction> getAvailableDirections();

   protected:
   private:
};

#endif