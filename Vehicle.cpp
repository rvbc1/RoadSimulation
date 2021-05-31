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

void Vehicle::prepareInheritJsonObject(JsonObject& jsonObject) {
    jsonObject["startCoordinates"]["x"] = getCoordinates().x();
    jsonObject["startCoordinates"]["y"] = getCoordinates().y();

    jsonObject["destinationCoordinates"]["x"] = 0;
    jsonObject["destinationCoordinates"]["y"] = 1;
}