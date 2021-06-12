#include "SimulationManager.h"

#include <QDebug>
#include <chrono>
#include <iostream>

SimulationManager::SimulationManager() {
}

bool SimulationManager::loadMap(QString filepath) {
    if (map != nullptr) {
        delete map;
    }
    map = MapBuilder::loadMapFromFile(filepath.toStdString());
    if (map == nullptr) {
        return false;
    }
    return true;
}

void SimulationManager::process() {
    while (true) {
        if (map != nullptr) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !threadInPause; });

            for (Driver* driver : map->getDrivers()) {
                driver->process();
            }
        }
    }
}

void SimulationManager::start() {
    thread = new std::thread(&SimulationManager::process, this);
}

void SimulationManager::pause() {
    std::unique_lock<decltype(mtx)> l(mtx);
    threadInPause = true;
    cv.notify_one();
}
void SimulationManager::resume() {
    std::unique_lock<decltype(mtx)> l(mtx);
    threadInPause = false;
    cv.notify_one();
}

bool SimulationManager::isPaused() {
    return threadInPause;
}

Map* SimulationManager::getMap() {
    return map;
}