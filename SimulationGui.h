#ifndef SimulationGui_h
#define SimulationGui_h

#include <QLabel>
#include <QMainWindow>
#include <QWidget>

#include "SimulationManager.h"

class SimulationGui : public QMainWindow {
   public:
    SimulationGui(SimulationManager *simulationManager);

   protected:
   void paintEvent(QPaintEvent *event);
   private:
    SimulationManager *simulationManager = nullptr;
    void process();
    void createMenus();
    std::thread thread;
};

#endif