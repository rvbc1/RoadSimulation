#include "Driver.h"

#include <iostream>

Driver::Driver(QPoint startCoordinates, QPoint destinationCoordinates, Map* map) {
    this->startCoordinates = startCoordinates;
    this->destinationCoordinates = destinationCoordinates;
    this->map = map;

    vehicle = new Vehicle(startCoordinates);
    map->addObject(vehicle);
}

Driver::Driver(JsonObject jsonObject, Map* map) {
    this->map = map;

    if ((jsonObject.containsKey(DRIVER_START_COORDS_JSON_KEY)) && (jsonObject[DRIVER_START_COORDS_JSON_KEY].is<JsonObject>())) {
        JsonObject jsonCoordsObject = jsonObject[DRIVER_START_COORDS_JSON_KEY].as<JsonObject>();
        if ((jsonCoordsObject.containsKey(MAP_OBJECT_COORDS_X_JSON_KEY)) && (jsonCoordsObject[MAP_OBJECT_COORDS_X_JSON_KEY].is<uint32_t>()) && (jsonCoordsObject.containsKey(MAP_OBJECT_COORDS_Y_JSON_KEY)) && (jsonCoordsObject[MAP_OBJECT_COORDS_Y_JSON_KEY].is<uint32_t>())) {
            startCoordinates.setX(jsonCoordsObject[MAP_OBJECT_COORDS_X_JSON_KEY].as<uint32_t>());
            startCoordinates.setY(jsonCoordsObject[MAP_OBJECT_COORDS_Y_JSON_KEY].as<uint32_t>());
        } else {
            throw std::invalid_argument("Wrong object coordinates values");
        }

    } else {
        throw std::invalid_argument("Driver start coordinates not defined");
    }

    if ((jsonObject.containsKey(DRIVER_DESTINATION_COORDS_JSON_KEY)) && (jsonObject[DRIVER_DESTINATION_COORDS_JSON_KEY].is<JsonObject>())) {
        JsonObject jsonCoordsObject = jsonObject[DRIVER_DESTINATION_COORDS_JSON_KEY].as<JsonObject>();
        if ((jsonCoordsObject.containsKey(MAP_OBJECT_COORDS_X_JSON_KEY)) && (jsonCoordsObject[MAP_OBJECT_COORDS_X_JSON_KEY].is<uint32_t>()) && (jsonCoordsObject.containsKey(MAP_OBJECT_COORDS_Y_JSON_KEY)) && (jsonCoordsObject[MAP_OBJECT_COORDS_Y_JSON_KEY].is<uint32_t>())) {
            destinationCoordinates.setX(jsonCoordsObject[MAP_OBJECT_COORDS_X_JSON_KEY].as<uint32_t>());
            destinationCoordinates.setY(jsonCoordsObject[MAP_OBJECT_COORDS_Y_JSON_KEY].as<uint32_t>());
        } else {
            throw std::invalid_argument("Wrong object coordinates values");
        }

    } else {
        throw std::invalid_argument("Driver destiantion coordinates not defined");
    }

    vehicle = new Vehicle(startCoordinates);
    map->addObject(vehicle);
}

void Driver::searchPath() {
    if (Road* road = dynamic_cast<Road*>(map->getMapObject(startCoordinates, MapObject::ROAD))) {
        // QVector<Road*> avilableRoads = road->getAvailableRoads();

        // for (Road* avilableRoad : avilableRoads) {
        //     std::cout << avilableRoad->getCoordinates().x() << ", " << avilableRoad->getCoordinates().y() << std::endl;
        // }
        QVector<Road*> path = search(startCoordinates, destinationCoordinates);

        // std::cout << road->getCoordinates().x() << ", " << road->getCoordinates().y();
        // for (Road* roads : path) {
        //     std::cout << " -> " << roads->getCoordinates().x() << ", " << roads->getCoordinates().y();
        // }
    } else {
        throw std::runtime_error("Driver not on the road");
    }
}

QVector<Road*> Driver::search(QPoint startPoint, QPoint endPoint, QVector<Road*> path) {
    if (Road* road = dynamic_cast<Road*>(map->getMapObject(startPoint, MapObject::ROAD))) {
        path.push_back(road);
        if (startPoint != endPoint) {
            QVector<Road*> avilableRoads = road->getAvailableRoads();
            for (Road* avilableRoad : avilableRoads) {
                if (path.contains(avilableRoad) == false) {
                    //path.push_back(avilableRoad);
                    QVector<Road*> foundedPath = search(avilableRoad->getCoordinates(), endPoint, path);
                }
            }
        }else {
            std::cout << "Jest ";
        }
    }

    for (Road* roads : path) {
        std::cout << roads->getCoordinates().x() << ", " << roads->getCoordinates().y() << " -> ";
    }
    std::cout << std::endl;
    return path;
}