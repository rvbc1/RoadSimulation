#ifndef Vehicle_h
#define Vehicle_h

#include "MapObject.h"

#define VEHICLE_OBJECT_TYPE_JSON_VALUE "vehicle"

class Vehicle : public MapObject {
   public:
    Vehicle(QPoint coordinates);
    Vehicle(JsonObject jsonObject);

    std::string getChar();

   protected:
   private:
};

#endif