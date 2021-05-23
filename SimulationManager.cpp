#include "SimulationManager.h"

#include <chrono>
#include <iostream>

#include <QDebug>

SimulationManager::SimulationManager() {
    
}

bool SimulationManager::loadMap(QString filepath){
    map = MapBuilder::loadMapFromFile(filepath.toStdString());
    //map = MapBuilder::loadMapFromFile("Mapa.json");
    if(map == nullptr){
        return false;
    }
    return true;
}

void SimulationManager::process() {
    if (map != nullptr) {
        if (map->getDrivers().isEmpty() == false) {
            Driver* driver = map->getDrivers()[0];
            QVector<QVector<Road*>> paths = driver->getPaths();
            //QVector<Road*> path = driver->getShortestPath();
            for (QVector<Road*> path : paths) {
                for (Road* road : path) {
                    driver->getVehicle()->setCoordinates(road->getCoordinates());
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }
        }
    }
}

void SimulationManager::start(){
    thread = std::thread(&SimulationManager::process, this);
}


Map* SimulationManager::getMap() {
    return map;
}