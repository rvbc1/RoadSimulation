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

    Vehicle* getVehicle();

    QVector<Road*> getShortestPath();
    QVector<QVector<Road*>> getPaths();

    QVector<QVector<Road*>> searchAvailablePaths(QPoint startPoint, QPoint endPoint, QVector<Road*> path = QVector<Road*>(), QVector<QVector<Road*>> foundedPaths = QVector<QVector<Road*>>());

   protected:
   private:
    QPoint startCoordinates;
    QPoint destinationCoordinates;
    Map* map;
    Vehicle* vehicle = nullptr;
};

#endif