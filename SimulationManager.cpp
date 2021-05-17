#include "SimulationManager.h"

#include <chrono>
#include <iostream>
#include <thread>

SimulationManager::SimulationManager() {
    map = MapBuilder::loadMapFromFile("Mapa.json");
    if (map != nullptr) {
        QVector<Road*> path = map->driver->searchPath();
        std::cout << path.size();
        for (Road* road : path) {
            //std::cout << road->getCoordinates().x() << ", " << road->getCoordinates().y() << " -> ";
            map->driver->vehicle->setCoordinates(road->getCoordinates());

            map->print();

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}