#include <QApplication>

#include "SimulationGui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SimulationManager *simulation = new SimulationManager();
    SimulationGui gui(simulation);
    gui.show();
    return app.exec();
}