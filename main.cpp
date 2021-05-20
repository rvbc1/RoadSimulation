#include <QApplication>

#include "SimulationGui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SimulationGui gui(new SimulationManager());
    gui.show();
    return app.exec();
}