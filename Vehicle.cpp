#include "Vehicle.h"

Vehicle::Vehicle(QPoint coordinates) : MapObject(coordinates) {
    type = VEHICLE;
}

Vehicle::Vehicle(JsonObject jsonObject) : MapObject(jsonObject) {
    type = VEHICLE;
}

std::string Vehicle::getChar() {
    return "v";
}