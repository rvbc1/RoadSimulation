#ifndef SimulationGui_h
#define SimulationGui_h

#include <QLabel>
#include <QMainWindow>
#include <QWidget>

#include "SimulationManager.h"

class SimulationGui : public QMainWindow {
   public:
    SimulationGui(SimulationManager *simulationManager);

   public slots:
    void openFile();
    void saveFile();
    void startSimulation();
    void changeDrawRoad();
    void changeDrawDriver();

   protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

   private:
    SimulationManager *simulationManager = nullptr;
    void process();
    void createMenus();
    std::thread thread;
    QSize windowSize;

    unsigned int areaSize = 40;

    QAction *drawRoadAction = nullptr;
    QAction *drawDriverAction = nullptr;
    void drawMap(Map *map, QPainter &painter);
};

#endif