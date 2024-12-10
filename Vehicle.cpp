#include "Vehicle.h"

Vehicle::Vehicle(const string& license, const string& owner, const string& model)
    : licensePlate(license), ownerName(owner), model(model) {
}

string Vehicle::getLicensePlate() const {
    return licensePlate;
}

string Vehicle::getOwnerName() const {
    return ownerName;
}

string Vehicle::getModel() const {
    return model;
}

void Vehicle::setOwnerName(const string& owner) {
    ownerName = owner;
}   