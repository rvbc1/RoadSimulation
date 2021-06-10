#ifndef Driver_h
#define Driver_h

#include <QPoint>
#include <QVector>
#include <QVectorIterator>

#include "Map.h"
#include "Road.h"
#include "MapObject.h"
#include "Vehicle.h"

#define DRIVER_OBJECT_TYPE_JSON_VALUE "driver"
#define DRIVER_STOPS_ARRAY_JSON_KEY "stops"
#define DRIVER_START_COORDS_JSON_KEY "startCoordinates"
#define DRIVER_DESTINATION_COORDS_JSON_KEY "destinationCoordinates"

class Driver : public MapObject {
   public:
    // Driver(QPoint startCoordinates, QPoint destinationCoordinates, Map* map);
    Driver(JsonObject jsonObject, Map* map);

    Vehicle* getVehicle();

    void process();

    void addStop(QPoint coordinates);

    QVector<Road*> getShortestPath(QPoint startPoint, QPoint endPoint);
    QVector<QVector<Road*>> getPaths();

    QVector<QVector<Road*>> searchAvailablePaths(QPoint startPoint, QPoint endPoint, QVector<Road*> path = QVector<Road*>(), QVector<QVector<Road*>> foundedPaths = QVector<QVector<Road*>>());

   protected:
   private:
    QVector<Road*> stops;
    int currentStopIndex = 0;
    QVector<Road*> currentPath;
    Map* map;
    Vehicle* vehicle = nullptr;

    void setNextStop();
    Road* getCurrentStop();
    Road* getNextStop();

    void prepareInheritJsonObject(JsonObject& jsonObject);
};

#endif