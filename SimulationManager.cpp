#include "SimulationManager.h"

SimulationManager::SimulationManager() {
    map = MapBuilder::loadMapFromFile("Mapa.json");
    if (map != nullptr) {
        map->print();
    }
}