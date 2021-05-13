#ifndef SimulationManager_h
#define SimulationManager_h

#include "Map.h"

class SimulationManager {
   public:
    SimulationManager();

   protected:
   private:
    Map* map = nullptr;
};

#endif