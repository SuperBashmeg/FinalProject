#ifndef AUTOSERVICE_H
#define AUTOSERVICE_H

#include "Vehicle.h"
#include "History.h"
#include "lib.h"

class AutoService {
private:
    vector<Vehicle> vehicles; // List of registered vehicles
    unordered_map<string, History> serviceHistories; // Map of license plate to history

public:
    void addVehicle(const Vehicle& vehicle);
    bool vehicleExists(const string& licensePlate) const;
    void addServiceToVehicle(const string& licensePlate, const Service& service);
    void printServiceHistory(const string& licensePlate) const;
    void saveHistoryToFile(const string& filename) const;
	void loadHistory();
	vector<Vehicle> getVehicles() const { return vehicles; }
};

#endif // AUTOSERVICE_H