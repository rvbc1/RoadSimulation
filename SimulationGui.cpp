#include "SimulationGui.h"

#include <QPainter>

SimulationGui::SimulationGui(SimulationManager *simulationManager) {
    this->simulationManager = simulationManager;
    setFixedWidth(800);
    setFixedHeight(600);

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
                        // if(object->getType() == MapObject::ROAD){
                        //     //painter.drawPoint();
                        //     painter.drawRect(w*20, h*20, 20, 20);
                        // }
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

// //a simple line
// painter.drawLine(1, 1, 100, 100);

// //create a black pen that has solid line
// //and the width is 2.
// QPen myPen(Qt::black, 2, Qt::SolidLine);
// painter.setPen(myPen);
// painter.drawLine(100, 100, 100, 1);

// //draw a point
// myPen.setColor(Qt::red);
// painter.drawPoint(110, 110);

// //draw a polygon
// QPolygon polygon;
// polygon << QPoint(130, 140) << QPoint(180, 170)
//          << QPoint(180, 140) << QPoint(220, 110)
//          << QPoint(140, 100);
//  painter.drawPolygon(polygon);

//  //draw an ellipse
//  //The setRenderHint() call enables antialiasing, telling QPainter to use different
//  //color intensities on the edges to reduce the visual distortion that normally
//  //occurs when the edges of a shape are converted into pixels
//  painter.setRenderHint(QPainter::Antialiasing, true);
//  painter.setPen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap));
//  painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
//  painter.drawEllipse(200, 80, 400, 240);
//}