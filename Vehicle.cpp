#include "Vehicle.h"

#include <QDebug>

#include "Driver.h"

Vehicle::Vehicle(QPoint coordinates) : MapObject(coordinates) {
    type = VEHICLE;
    driver = new Driver(this);
}

Vehicle::Vehicle(JsonObject jsonObject) : MapObject(jsonObject) {
    type = VEHICLE;
    if (jsonObject.containsKey(DRIVER_JSON_KEY) && jsonObject[DRIVER_JSON_KEY].is<JsonObject>()) {
        driver = new Driver(this, jsonObject[DRIVER_JSON_KEY].as<JsonObject>());
    } else {
        driver = new Driver(this);
    }
}

Driver* Vehicle::getDriver() {
    return driver;
}

std::string Vehicle::getChar() {
    return "*";
}

void Vehicle::prepareInheritJsonObject(JsonObject& jsonObject) {
    // jsonObject["startCoordinates"]["x"] = getCoordinates().x();
    // jsonObject["startCoordinates"]["y"] = getCoordinates().y();

    // jsonObject["destinationCoordinates"]["x"] = 0;
    // jsonObject["destinationCoordinates"]["y"] = 1;
    JsonObject driverJsonObject = jsonObject.createNestedObject(DRIVER_JSON_KEY);
    driver->prepareJsonObject( driverJsonObject);
}

Vehicle::~Vehicle(){
    delete driver;
}