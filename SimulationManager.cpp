#include "SimulationManager.h"

#include <chrono>
#include <iostream>
#include <thread>

SimulationManager::SimulationManager() {
    map = MapBuilder::loadMapFromFile("Mapa.json");
    // if (map != nullptr) {
    //     if (map->getDrivers().isEmpty() == false) {
    //         Driver* driver = map->getDrivers()[0];
    //         QVector<QVector<Road*>> paths = driver->getPaths();
    //         //QVector<Road*> path = driver->getShortestPath();
    //         for (QVector<Road*> path : paths) {
    //             for (Road* road : path) {
    //                 driver->getVehicle()->setCoordinates(road->getCoordinates());

    //                 map->print();

    //                 std::this_thread::sleep_for(std::chrono::seconds(1));
    //             }
    //         }
    //     }
    // }
}

Map* SimulationManager::getMap(){
    return map;
}