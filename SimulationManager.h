#ifndef SimulationManager_h
#define SimulationManager_h

#include "Map.h"
#include "MapBuilder.h"
#include "Driver.h"

class SimulationManager {
   public:
    SimulationManager();

    Map* getMap();

   protected:
   private:
    Map* map = nullptr;
};

#endif