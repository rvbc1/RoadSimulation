#include "Vehicle.h"
#include "Driver.h"

#include <QDebug>

Vehicle::Vehicle(QPoint coordinates) : MapObject(coordinates) {
    type = VEHICLE;
    driver = new Driver(this);
}

Vehicle::Vehicle(JsonObject jsonObject) : MapObject(jsonObject) {
    type = VEHICLE;
    if(jsonObject.containsKey(DRIVER_JSON_KEY) && jsonObject[DRIVER_JSON_KEY].is<JsonObject>()){
        driver = new Driver(this, jsonObject[DRIVER_JSON_KEY].as<JsonObject>());
    } else {
        driver = new Driver(this);
    }
}

Driver* Vehicle::getDriver(){
    return driver;
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