#ifndef SimulationManager_h
#define SimulationManager_h

#include <thread>

#include "Map.h"
#include "MapBuilder.h"
#include "Driver.h"

class SimulationManager {
   public:
    SimulationManager();

    bool loadMap(QString filepath);

    Map* getMap();

    void start();

   protected:
   private:
    Map* map = nullptr;
    void process();
    std::thread thread;
};

#endif