#include "SimulationGui.h"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>
#include <QMouseEvent>
#include <QPainter>

SimulationGui::SimulationGui(SimulationManager *simulationManager) : QMainWindow() {
    this->simulationManager = simulationManager;
    windowSize.setWidth(800);
    windowSize.setHeight(600);
    setFixedSize(windowSize);
    createMenus();
    thread = std::thread(&SimulationGui::process, this);
}

void SimulationGui::process() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        update();
    }
}

void SimulationGui::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (simulationManager != nullptr) {
        Map *map = simulationManager->getMap();
        if (map != nullptr) {
            drawMap(map, painter);
        }
        QPoint p = mapFromGlobal(QCursor::pos());
        if ((p.x() > 0) && (p.y() > 0) && (p.x() < windowSize.width()) && (p.y() < windowSize.height())) {
            QRect reactangle((p.x() / areaSize) * areaSize, (p.y() / areaSize) * areaSize, areaSize, areaSize);
            painter.drawRect(reactangle);
        }
    }
}

void SimulationGui::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *loadFileAction = new QAction(tr("&Open"), this);
    QAction *saveFileAction = new QAction(tr("&Save"), this);
    fileMenu->addAction(loadFileAction);
    fileMenu->addAction(saveFileAction);

    QMenu *simulationMenu = menuBar()->addMenu(tr("&Simulation"));
    QAction *startSimulationAction = new QAction(tr("&Start/Stop"), this);
    simulationMenu->addAction(startSimulationAction);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    drawRoadAction = new QAction(tr("&Road"), this);
    drawDriverAction = new QAction(tr("&Driver"), this);
    drawRoadAction->setCheckable(true);
    drawDriverAction->setCheckable(true);
    editMenu->addAction(drawRoadAction);
    editMenu->addAction(drawDriverAction);

    connect(loadFileAction, &QAction::triggered, this, &SimulationGui::openFile);
    connect(saveFileAction, &QAction::triggered, this, &SimulationGui::saveFile);
    connect(startSimulationAction, &QAction::triggered, this, &SimulationGui::startSimulation);
    connect(drawRoadAction, &QAction::triggered, this, &SimulationGui::changeDrawRoad);
    connect(drawDriverAction, &QAction::triggered, this, &SimulationGui::changeDrawDriver);
}

void SimulationGui::drawMap(Map *map, QPainter &painter) {
    for (int w = 0; w < map->getSize().width(); w++) {
        for (int h = 0; h < map->getSize().height(); h++) {
            QVector<MapObject *> objects = map->getMapObjectVector(QPoint(w, h));
            for (MapObject *object : objects) {
                if (Road *road = dynamic_cast<Road *>(object)) {
                    painter.setPen(Qt::blue);
                    painter.setFont(QFont("Arial", 40));

                    QRect rectangle = QRect(w * areaSize, h * areaSize, areaSize, areaSize);
                    painter.drawText(rectangle, Qt::AlignCenter, QString(road->getChar().c_str()));
                } else if (Vehicle *vehicle = dynamic_cast<Vehicle *>(object)) {
                    painter.setPen(Qt::red);
                    painter.setFont(QFont("Arial", 40));

                    QRect rectangle = QRect(w * areaSize, h * areaSize, areaSize, areaSize);
                    painter.drawText(rectangle, Qt::AlignCenter, QString(vehicle->getChar().c_str()));
                }
            }
        }
    }
}

void SimulationGui::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPoint mousePos = event->pos();
        QPoint mapPos((mousePos.x() / areaSize), (mousePos.y() / areaSize));
        if (simulationManager != nullptr) {
            Map *map = simulationManager->getMap();
            if (map != nullptr) {
                if (drawRoadAction->isChecked()) {
                    if (map->getMapObject(mapPos, MapObject::ROAD) == nullptr) {
                        map->addObject(new Road(mapPos));
                    } else {
                        MapObject *mapObject = map->getMapObject(mapPos, MapObject::ROAD);
                        map->removeObject(mapObject);
                        delete mapObject;
                    }
                } else if (drawDriverAction->isChecked()) {
                    if (map->getMapObject(mapPos, MapObject::VEHICLE) == nullptr) {
                        map->addObject(new Vehicle(mapPos));
                    } else {
                        MapObject *mapObject = map->getMapObject(mapPos, MapObject::VEHICLE);
                        map->removeObject(mapObject);
                        delete mapObject;
                    }
                }
            }
        }
    }
}

void SimulationGui::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Map File"), "", tr("JSON Files (*.json);;All Files (*)"));
    simulationManager->loadMap(fileName);

    simulationManager->start();
}

void SimulationGui::saveFile() {
    if (simulationManager != nullptr) {
        Map *map = simulationManager->getMap();
        if (map != nullptr) {
            QString fileName = QFileDialog::getSaveFileName(this,
                                                            tr("Open Map File"), "", tr("JSON Files (*.json);;All Files (*)"));
            MapBuilder::saveMapToFile(map, fileName.toStdString());
        }
    }
}

void SimulationGui::startSimulation() {
    if (simulationManager->isPaused()) {
        simulationManager->resume();
    } else {
        simulationManager->pause();
    }
}

void SimulationGui::changeDrawRoad() {
    if (drawRoadAction->isChecked()) {
        drawDriverAction->setChecked(false);
    }
}

void SimulationGui::changeDrawDriver() {
    if (drawDriverAction->isChecked()) {
        drawRoadAction->setChecked(false);
    }
}
