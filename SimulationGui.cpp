#include "SimulationGui.h"

#include <QMenuBar>
#include <QPainter>

SimulationGui::SimulationGui(SimulationManager *simulationManager) : QMainWindow() {
    this->simulationManager = simulationManager;
    setFixedWidth(800);
    setFixedHeight(600);
    createMenus();
    thread = std::thread(&SimulationGui::process, this);
}

void SimulationGui::process() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        repaint();
    }
}

void SimulationGui::paintEvent(QPaintEvent *event) {
    //create a QPainter and pass a pointer to the device.
    //A paint device can be a QWidget, a QPixmap or a QImage
    QPainter painter(this);
    if (simulationManager != nullptr) {
        Map *map = simulationManager->getMap();
        if (map != nullptr) {
            for (int w = 0; w < map->getSize().width(); w++) {
                for (int h = 0; h < map->getSize().height(); h++) {
                    QVector<MapObject *> objects = map->getMapObjectVector(QPoint(w, h));
                    for (MapObject *object : objects) {
                        if (Road *road = dynamic_cast<Road *>(object)) {
                            painter.setPen(Qt::blue);
                            painter.setFont(QFont("Arial", 30));

                            int areaSize = 40;
                            QRect rectangle = QRect(w * areaSize, h * areaSize, areaSize, areaSize);
                            painter.drawText(rectangle, Qt::AlignCenter, QString(road->getChar().c_str()));
                        } else if (Vehicle *vehicle = dynamic_cast<Vehicle *>(object)) {
                            painter.setPen(Qt::red);
                            painter.setFont(QFont("Arial", 30));

                            int areaSize = 40;
                            QRect rectangle = QRect(w * areaSize, h * areaSize, areaSize, areaSize);
                            painter.drawText(rectangle, Qt::AlignCenter, QString(vehicle->getChar().c_str()));
                        }
                    }
                }
            }
        }
    }
}

void SimulationGui::createMenus() {
    menuBar()->addMenu(tr("&File"));
    menuBar()->addMenu(tr("Xile"));
}