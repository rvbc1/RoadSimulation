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
    windowSize.setHeight(700);
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
        p.setY(p.y() - offsetY);
        if (map != nullptr) {
            if ((p.x() / (int)areaSize) >= map->getSize().width()) {
                p.setX((map->getSize().width() - 1) * areaSize);
            }

            if ((p.y() / (int)areaSize) >= map->getSize().height()) {
                p.setY((map->getSize().height() - 1) * areaSize);
            }
        }

        if ((p.x() > 0) && (p.y() > 0) && (p.x() < windowSize.width()) && (p.y() < windowSize.height())) {
            QRect reactangle((p.x() / areaSize) * areaSize, (p.y() / areaSize) * areaSize + offsetY, areaSize, areaSize);
            painter.drawRect(reactangle);

            QRect rectangle = QRect(0, windowSize.height() - 50, windowSize.width(), 50);
            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial", 20));
            painter.drawText(rectangle, Qt::AlignLeft, QString("x: " + QString::number(p.x() / areaSize) + " y: " + QString::number(p.y() / areaSize)));
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
    QRect reactangle(0, offsetY, map->getSize().width() * areaSize, map->getSize().height() * areaSize);
    painter.drawRect(reactangle);
    for (int w = 0; w < map->getSize().width(); w++) {
        for (int h = 0; h < map->getSize().height(); h++) {
            QVector<MapObject *> objects = map->getMapObjectVector(QPoint(w, h));
            for (MapObject *object : objects) {
                if (Road *road = dynamic_cast<Road *>(object)) {
                    painter.setPen(Qt::blue);
                    painter.setFont(QFont("Arial", 40));

                    QRect rectangle = QRect(w * areaSize, h * areaSize + offsetY, areaSize, areaSize);
                    painter.drawText(rectangle, Qt::AlignCenter, QString(road->getChar().c_str()));
                } else if (Vehicle *vehicle = dynamic_cast<Vehicle *>(object)) {
                    painter.setPen(Qt::red);
                    painter.setFont(QFont("Arial", 40));

                    QRect rectangle = QRect(w * areaSize, h * areaSize + offsetY, areaSize, areaSize);
                    painter.drawText(rectangle, Qt::AlignCenter, QString(vehicle->getChar().c_str()));
                }
            }
        }
    }
}

void SimulationGui::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPoint mousePos = event->pos();
        mousePos.setY(mousePos.y() - offsetY);
        if (simulationManager->getMap() != nullptr) {
            if ((mousePos.x() / (int)areaSize) >= simulationManager->getMap()->getSize().width()) {
                mousePos.setX((simulationManager->getMap()->getSize().width() - 1) * areaSize);
            }

            if ((mousePos.y() / (int)areaSize) >= simulationManager->getMap()->getSize().height()) {
                mousePos.setY((simulationManager->getMap()->getSize().height() - 1) * areaSize);
            }
        }
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
