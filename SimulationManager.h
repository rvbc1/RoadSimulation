#ifndef SimulationManager_h
#define SimulationManager_h

#include <condition_variable>  // std::condition_variable
#include <mutex>               // std::mutex, std::unique_lock
#include <thread>

#include "Driver.h"
#include "Map.h"
#include "MapBuilder.h"

class SimulationManager {
   public:
    SimulationManager();

    bool loadMap(QString filepath);

    Map* getMap();

    void start();
    void pause();
    void resume();

    bool isPaused();

   protected:
   private:
    Map* map = nullptr;
    void process();

    bool threadInPause = true;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread* thread = nullptr;
};

#endif