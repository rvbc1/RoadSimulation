#ifndef Map_h
#define Map_h

#include <QSize>
#include <QVector>

#include "MapObject.h"

class Map {
   public:
    Map(QSize size);

    void print();

   protected:
   private:
    QSize size;
    QVector<QVector<MapObject*>> objectsArray;

    void createObjectsArray();
};

#endif