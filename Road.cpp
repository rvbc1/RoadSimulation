#include "Road.h"

Road::Road(QPoint coordinates) : MapObject(coordinates) {
    type = ROAD;
}

Road::Road(JsonObject jsonObject) : MapObject(jsonObject) {
    type = ROAD;
}

// std::cout << "╔" << std::endl;//
// std::cout << "╚" << std::endl; //
// std::cout << "╝" << std::endl; //
// std::cout << "╗" << std::endl; //

// std::cout << "║" << std::endl; //
// std::cout << "═" << std::endl; //

// std::cout << "╠" << std::endl; //
// std::cout << "╣" << std::endl; //
// std::cout << "╦" << std::endl; //
// std::cout << "╩" << std::endl; //
// std::cout << "╬" << std::endl;

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