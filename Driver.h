#ifndef Driver_h
#define Driver_h

#include <QPoint>
#include <QVector>
#include <QVectorIterator>

#include "Map.h"
#include "Road.h"
#include "MapObject.h"

class Vehicle;

#define DRIVER_OBJECT_TYPE_JSON_VALUE "driver"
#define DRIVER_STOPS_ARRAY_JSON_KEY "stops"
#define DRIVER_START_COORDS_JSON_KEY "startCoordinates"
#define DRIVER_DESTINATION_COORDS_JSON_KEY "destinationCoordinates"

class Driver : public MapObject {
   public:
    // Driver(QPoint startCoordinates, QPoint destinationCoordinates, Map* map);
    Driver(Vehicle *vehicle);
    Driver(Vehicle *vehicle, JsonObject jsonObject);
    Driver(JsonObject jsonObject, Map* map);

    Vehicle* getVehicle();

    void process();

    void addStop(QPoint coordinates);

    QVector<QPoint> getShortestPath(QPoint startPoint, QPoint endPoint);
    QVector<QVector<QPoint>> getPaths();

    QVector<QVector<QPoint>> searchAvailablePaths(QPoint startPoint, QPoint endPoint, QVector<QPoint> path = QVector<QPoint>(), QVector<QVector<QPoint>> foundedPaths = QVector<QVector<QPoint>>());

  // protected:
  // private:
  //  QVector<Road*> stops;
    QVector<QPoint> stops;
    int currentStopIndex = 0;
    QVector<QPoint> currentPath;
    Vehicle* vehicle = nullptr;

    void setNextStop();
    QPoint getCurrentStop();
    QPoint getNextStop();

    void prepareInheritJsonObject(JsonObject& jsonObject);
};

#endif