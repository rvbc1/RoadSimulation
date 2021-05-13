#include "SimulationManager.h"

SimulationManager::SimulationManager() {
    map = MapBuilder::loadMapFromFile("Mapa.json");
    map->print();
}