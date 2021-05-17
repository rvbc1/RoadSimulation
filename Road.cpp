#include "Road.h"

Road::Road(QPoint coordinates) : MapObject(coordinates) {
    type = ROAD;
}

Road::Road(JsonObject jsonObject) : MapObject(jsonObject) {
    type = ROAD;
}

QVector<Road *> Road::getAvailableRoads() {
    QVector<Road *> availableRoads;
    if (Road *road = dynamic_cast<Road *>(getNeighborhoodMapObject(UP))) {
        availableRoads.push_back(road);
    }
    if (Road *road = dynamic_cast<Road *>(getNeighborhoodMapObject(DOWN))) {
        availableRoads.push_back(road);
    }
    if (Road *road = dynamic_cast<Road *>(getNeighborhoodMapObject(LEFT))) {
        availableRoads.push_back(road);
    }
    if (Road *road = dynamic_cast<Road *>(getNeighborhoodMapObject(RIGHT))) {
        availableRoads.push_back(road);
    }
    return availableRoads;
}

std::string Road::getChar() {
    if ((getNeighborhoodMapObject(UP) != nullptr) && (getNeighborhoodMapObject(DOWN) != nullptr) && (getNeighborhoodMapObject(LEFT) != nullptr) && (getNeighborhoodMapObject(RIGHT) != nullptr)) {
        return "╬";
    }
    if ((getNeighborhoodMapObject(UP) != nullptr) && (getNeighborhoodMapObject(LEFT) != nullptr) && (getNeighborhoodMapObject(RIGHT) != nullptr)) {
        return "╩";
    }
    if ((getNeighborhoodMapObject(UP) != nullptr) && (getNeighborhoodMapObject(DOWN) != nullptr) && (getNeighborhoodMapObject(LEFT) != nullptr)) {
        return "╣";
    }
    if ((getNeighborhoodMapObject(UP) != nullptr) && (getNeighborhoodMapObject(DOWN) != nullptr) && (getNeighborhoodMapObject(RIGHT) != nullptr)) {
        return "╠";
    }
    if ((getNeighborhoodMapObject(DOWN) != nullptr) && (getNeighborhoodMapObject(LEFT) != nullptr) && (getNeighborhoodMapObject(RIGHT) != nullptr)) {
        return "╦";
    }
    if ((getNeighborhoodMapObject(UP) != nullptr) && (getNeighborhoodMapObject(RIGHT) != nullptr)) {
        return "╚";
    }
    if ((getNeighborhoodMapObject(UP) != nullptr) && (getNeighborhoodMapObject(LEFT) != nullptr)) {
        return "╝";
    }
    if ((getNeighborhoodMapObject(DOWN) != nullptr) && (getNeighborhoodMapObject(LEFT) != nullptr)) {
        return "╗";
    }
    if ((getNeighborhoodMapObject(DOWN) != nullptr) && (getNeighborhoodMapObject(RIGHT) != nullptr)) {
        return "╔";
    }
    if ((getNeighborhoodMapObject(UP) != nullptr) || (getNeighborhoodMapObject(DOWN) != nullptr)) {
        return "║";
    }
    if ((getNeighborhoodMapObject(LEFT) != nullptr) || (getNeighborhoodMapObject(RIGHT) != nullptr)) {
        return "═";
    }

    return "╬";
}
