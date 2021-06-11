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
    enum Type { WHATEVER,
                ROAD,
                DRIVER,
                VEHICLE,
                NONE };
    MapObject(QPoint coordinates, Map* map = nullptr);
    MapObject(JsonObject jsonObject, Map* map = nullptr);
    virtual ~MapObject();

    void setMap(Map* map);
    Map* getMap();

    void setCoordinates(QPoint coordinates);
    QPoint getCoordinates();

    virtual std::string getChar();

    MapObject* getNeighborhoodMapObject(Direction direction, Type type = WHATEVER);

    Type getType();

    void prepareJsonObject(JsonObject& jsonObject);

    void prepareCoordinates(JsonObject& jsonObject);
    static QPoint parseCoordinates(JsonObject jsonObject);

   protected:
    Type type = NONE;

    void prepareBasicJsonObject(JsonObject& jsonObject);
    virtual void prepareInheritJsonObject(JsonObject& jsonObject){};

   private:
    QPoint coordinates;
    Map* map;
};

#endif