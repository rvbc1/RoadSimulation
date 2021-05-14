#ifndef MapObject_h
#define MapObject_h

#include <QPoint>

#include "ArduinoJson-v6.18.0.h"

#define MAP_OBJECT_COORDS_JSON_KEY "coordinates"
#define MAP_OBJECT_COORDS_X_JSON_KEY "x"
#define MAP_OBJECT_COORDS_Y_JSON_KEY "y"

class MapObject {
   public:
    MapObject(QPoint coordinates);
    MapObject(JsonObject jsonObject);

    QPoint getCoordinates();

    virtual char getChar();

   protected:
   private:
    QPoint coordinates;
};

#endif