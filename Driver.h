#ifndef Driver_h
#define Driver_h

#include <QPoint>

#include "Map.h"
#include "Vehicle.h"

#define DRIVER_START_COORDS_JSON_KEY "startCoordinates"
#define DRIVER_DESTINATION_COORDS_JSON_KEY "destinationCoordinates"

class Driver {
   public:
    Driver(QPoint startCoordinates, QPoint destinationCoordinates, Map* map);
    Driver(JsonObject jsonObject, Map* map);

    void searchPath();

    QVector<Road*> search(QPoint startPoint, QPoint endPoint, QVector<Road*> path = QVector<Road*>());

   protected:
   private:
    QPoint startCoordinates;
    QPoint destinationCoordinates;
    Map* map;
    Vehicle* vehicle = nullptr;
};

#endif