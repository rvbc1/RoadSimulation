#ifndef Vehicle_h
#define Vehicle_h

#include "MapObject.h"

class Driver;

#define VEHICLE_OBJECT_TYPE_JSON_VALUE "vehicle"
#define DRIVER_JSON_KEY "driver"

class Vehicle : public MapObject {
   public:
    Vehicle(QPoint coordinates);
    Vehicle(JsonObject jsonObject);
    ~Vehicle();

    Driver* getDriver();

    std::string getChar();

   protected:
    void prepareInheritJsonObject(JsonObject& jsonObject);

   private:
    Driver* driver = nullptr;
};

#endif