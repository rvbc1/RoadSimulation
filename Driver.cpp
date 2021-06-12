#include "Driver.h"

#include <QDebug>

#include "Vehicle.h"

// Driver::Driver(QPoint startCoordinates, QPoint destinationCoordinates, Map* map) {
//     this->startCoordinates = startCoordinates;
//     this->destinationCoordinates = destinationCoordinates;
//     this->map = map;

//     vehicle = new Vehicle(startCoordinates);
//     map->addObject(vehicle);
// }

Driver::Driver(Vehicle* vehicle) : MapObject(vehicle->getCoordinates()) {
    this->type = DRIVER;
    this->vehicle = vehicle;
}

Driver::Driver(Vehicle* vehicle, JsonObject jsonObject) : MapObject(vehicle->getCoordinates()) {
    this->type = DRIVER;
    this->vehicle = vehicle;

    if ((jsonObject.containsKey(DRIVER_STOPS_ARRAY_JSON_KEY)) && (jsonObject[DRIVER_STOPS_ARRAY_JSON_KEY].is<JsonArray>())) {
        JsonArray stopsArray = jsonObject[DRIVER_STOPS_ARRAY_JSON_KEY].as<JsonArray>();
        for (JsonVariant v : stopsArray) {
            if (v.is<JsonObject>()) {
                addStop(MapObject::parseCoordinates(v.as<JsonObject>()));
            }
        }
    }
}

Driver::Driver(JsonObject jsonObject, Map* map) : MapObject(jsonObject) {
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

    // vehicle = new Vehicle(getCoordinates());

    map->addObject(vehicle);
}

void Driver::process() {
    if (currentPath.isEmpty()) {
        if (stops.size() > 1) {
            if (getVehicle()->getCoordinates() != getCurrentStop()) {
                currentPath = getShortestPath(getCoordinates(), getCurrentStop());
            } else {
                currentPath = getShortestPath(getCurrentStop(), getNextStop());
                setNextStop();
            }
        } else if ((stops.size() == 1) && (getVehicle()->getCoordinates() != getCurrentStop())) {
            currentPath = getShortestPath(getCoordinates(), getCurrentStop());
        }
    }
    if (currentPath.isEmpty() == false) {
        if (currentPath.front() == getVehicle()->getCoordinates()) {
            currentPath.pop_front();
        }
        getVehicle()->setCoordinates(currentPath.front());
        currentPath.pop_front();
    }
}

void Driver::addStop(QPoint coordinates) {
    // if (map != nullptr) {
    //     if (Road* road = dynamic_cast<Road*>(map->getMapObject(coordinates, MapObject::ROAD))) {
    //         stops.push_back(road);
    //     }
    // }
    stops.push_back(coordinates);
}

QVector<QPoint> Driver::getShortestPath(QPoint startPoint, QPoint endPoint) {
    QVector<QVector<QPoint>> paths = searchAvailablePaths(startPoint, endPoint);
    QVector<QPoint> shortestPath;
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

QVector<QVector<QPoint>> Driver::getPaths() {
    return searchAvailablePaths(getCurrentStop(), getNextStop());
}

QVector<QVector<QPoint>> Driver::searchAvailablePaths(QPoint startPoint, QPoint endPoint, QVector<QPoint> path, QVector<QVector<QPoint>> foundedPaths) {
    if (getMap() != nullptr) {
        if (Road* road = dynamic_cast<Road*>(getMap()->getMapObject(startPoint, MapObject::ROAD))) {
            path.push_back(road->getCoordinates());
            if (startPoint != endPoint) {
                QVector<Road*> avilableRoads = road->getAvailableRoads();
                for (Road* avilableRoad : avilableRoads) {
                    if (path.contains(avilableRoad->getCoordinates()) == false) {
                        foundedPaths = searchAvailablePaths(avilableRoad->getCoordinates(), endPoint, path, foundedPaths);
                    }
                }
            } else {
                foundedPaths.push_back(path);
            }
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

QPoint Driver::getCurrentStop() {
    if (stops.isEmpty()) {
        //return NULL;
        qDebug() << "empty";
        return QPoint(0, 0);  //TODO CHANGE THIS
    }
    return stops[currentStopIndex];
}
QPoint Driver::getNextStop() {
    if ((currentStopIndex + 1) >= stops.size()) {
        return stops[0];
    }
    return stops[currentStopIndex + 1];
}

Vehicle* Driver::getVehicle() {
    return vehicle;
}

void Driver::prepareInheritJsonObject(JsonObject& jsonObject) {
    JsonArray stopsJsonArray = jsonObject.createNestedArray(DRIVER_STOPS_ARRAY_JSON_KEY);
    for (QPoint stop : stops) {
        JsonObject stopJsonObject = stopsJsonArray.createNestedObject();
        //stop->prepareCoordinates(stopJsonObject);
    }
}
