#ifndef Map_h
#define Map_h

#include <QSize>
#include <QVector>

#include "MapObject.h"

#define MAP_SIZE_JSON_KEY "size"
#define MAP_WIDTH_JSON_KEY "width"
#define MAP_HEIGHT_JSON_KEY "height"

class Map {
   public:
    Map(QSize size);
    Map(JsonObject jsonObject);

    void addObject(MapObject *object);

    void print();

   protected:
   private:
    QSize size;
    QVector<QVector<MapObject*>> objectsArray;

    void createObjectsArray();
};

#endif