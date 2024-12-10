#ifndef VEHICLE_H
#define VEHICLE_H

#include "lib.h"

class Vehicle {
private:
    string licensePlate;
    string ownerName;
    string model;

public:
    Vehicle(const string& license, const string& owner, const string& model);

    string getLicensePlate() const;
    string getOwnerName() const;
    string getModel() const;
    void setOwnerName(const string& owner);
};

#endif