#include "Driver.h"

#include <QDebug>
#include <iostream>

// Driver::Driver(QPoint startCoordinates, QPoint destinationCoordinates, Map* map) {
//     this->startCoordinates = startCoordinates;
//     this->destinationCoordinates = destinationCoordinates;
//     this->map = map;

//     vehicle = new Vehicle(startCoordinates);
//     map->addObject(vehicle);
// }

Driver::Driver(JsonObject jsonObject, Map* map) : MapObject(jsonObject) {
    this->map = map;
    this->type = DRIVER;
    //this->currentStop = QVectorIterator<Road*>(stops);

    if ((jsonObject.containsKey(DRIVER_STOPS_ARRAY_JSON_KEY)) && (jsonObject[DRIVER_STOPS_ARRAY_JSON_KEY].is<JsonArray>())) {
        JsonArray stopsArray = jsonObject[DRIVER_STOPS_ARRAY_JSON_KEY].as<JsonArray>();
        for (JsonVariant v : stopsArray) {
            if (v.is<JsonObject>()) {
                addStop(MapObject::parseCoordinates(v.as<JsonObject>()));
            }
        }
    }

    vehicle = new Vehicle(getCoordinates());
    if (getCoordinates() != getCurrentStop()->getCoordinates()) {
        currentPath = getShortestPath(getCoordinates(), getCurrentStop()->getCoordinates());
    }

    map->addObject(vehicle);
}

void Driver::process() {
    if (currentPath.isEmpty()) {
        currentPath = getShortestPath(getCurrentStop()->getCoordinates(), getNextStop()->getCoordinates());
        setNextStop();
    } else {
        getVehicle()->setCoordinates(currentPath.front()->getCoordinates());
        currentPath.pop_front();
    }
}

void Driver::addStop(QPoint coordinates) {
    if (map != nullptr) {
        if (Road* road = dynamic_cast<Road*>(map->getMapObject(coordinates, MapObject::ROAD))) {
            stops.push_back(road);
        }
    }
}

QVector<Road*> Driver::getShortestPath(QPoint startPoint, QPoint endPoint) {
    QVector<QVector<Road*>> paths = searchAvailablePaths(startPoint, endPoint);
    QVector<Road*> shortestPath;
    if (paths.isEmpty() == false) {
        int shorestPathIndex = 0;
        int minmumPathLength = paths[0].size();
        for (int i = 1; i < paths.size(); i++) {
            if (paths[i].size() < minmumPathLength) {
                shorestPathIndex = i;
            }
        }
        shortestPath = paths[shorestPathIndex];
    }
    return shortestPath;
}

QVector<QVector<Road*>> Driver::getPaths() {
    return searchAvailablePaths(getCurrentStop()->getCoordinates(), getNextStop()->getCoordinates());
}

QVector<QVector<Road*>> Driver::searchAvailablePaths(QPoint startPoint, QPoint endPoint, QVector<Road*> path, QVector<QVector<Road*>> foundedPaths) {
    if (Road* road = dynamic_cast<Road*>(map->getMapObject(startPoint, MapObject::ROAD))) {
        path.push_back(road);
        if (startPoint != endPoint) {
            QVector<Road*> avilableRoads = road->getAvailableRoads();
            for (Road* avilableRoad : avilableRoads) {
                if (path.contains(avilableRoad) == false) {
                    foundedPaths = searchAvailablePaths(avilableRoad->getCoordinates(), endPoint, path, foundedPaths);
                }
            }
        } else {
            foundedPaths.push_back(path);
        }
    }
    return foundedPaths;
}

void Driver::setNextStop() {
    currentStopIndex++;
    if (currentStopIndex >= stops.size()) {
        currentStopIndex = 0;
    }
}

Road* Driver::getCurrentStop() {
    if (stops.isEmpty()) {
        return nullptr;
    }
    return stops[currentStopIndex];
}
Road* Driver::getNextStop() {
    if ((currentStopIndex + 1) >= stops.size()) {
        return stops[0];
    }
    return stops[currentStopIndex + 1];
}

Vehicle* Driver::getVehicle() {
    return vehicle;
}

void Driver::prepareInheritJsonObject(JsonObject& jsonObject){
    JsonArray stopsJsonArray = jsonObject.createNestedArray(DRIVER_STOPS_ARRAY_JSON_KEY);
    for(Road* stop: stops){
        JsonObject stopJsonObject = stopsJsonArray.createNestedObject();
        stop->prepareCoordinates(stopJsonObject);
    }
}
