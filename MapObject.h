#ifndef MapObject_h
#define MapObject_h

#include <QPoint>

#include "ArduinoJson-v6.18.0.h"

#define MAP_OBJECT_COORDS_JSON_KEY "coordinates"
#define MAP_OBJECT_COORDS_X_JSON_KEY "x"
#define MAP_OBJECT_COORDS_Y_JSON_KEY "y"

#define MAP_OBJECT_TYPE_JSON_KEY "type"

class Map;

class MapObject {
   public:
    enum Direction { UP,
                      LEFT,
                      RIGHT,
                      DOWN };
    enum Type { ROAD,
                NONE };
    MapObject(QPoint coordinates, Map* map = nullptr);
    MapObject(JsonObject jsonObject, Map* map = nullptr);

    void setMap(Map* map);
    QPoint getCoordinates();

    virtual std::string getChar();

    MapObject* getNeighborhoodMapObject(Direction direction);

   protected:
    Type type = NONE;

   private:
    QPoint coordinates;
    Map* map;
};

#endif