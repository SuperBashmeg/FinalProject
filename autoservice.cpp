#include "AutoService.h"

void AutoService::addVehicle(const Vehicle& vehicle) {
    if (vehicleExists(vehicle.getLicensePlate())) {
        throw runtime_error("Vehicle with this license plate already exists.");
    }
    vehicles.push_back(vehicle);
    serviceHistories[vehicle.getLicensePlate()] = History();
}

bool AutoService::vehicleExists(const string& licensePlate) const {
    for (const auto& vehicle : vehicles) {
        if (vehicle.getLicensePlate() == licensePlate) {
            return true;
        }
    }
    return false;
}

void AutoService::loadHistory() {
    try
    {
        ifstream file("service_history.txt");

        if (file.is_open()) {
            string line;
			string licensePlate;
			string owner;
			string model;
			bool serviceHistory = false;
            while (getline(file, line)) {
                if (line.substr(0, 14) == "License Plate:") {
                    licensePlate = line.substr(15);
				}
                else if (line.substr(0, 7) == "Owner: ") {
					if (licensePlate.empty()) {
						throw runtime_error("Owner found before license plate.");
					}
                    owner = line.substr(7);
                }
				else if (line.substr(0, 7) == "Model: ") {
					if (licensePlate.empty()) {
						throw runtime_error("Model found before license plate.");
					}
					model = line.substr(7);
                }
                else if (line == "Service History:") {
                    serviceHistory = true;
                }
                else if(serviceHistory) {
                    if (licensePlate.empty()) {
                        throw runtime_error("Service history found before license plate.");
                    }
                    if (line == "--------------------------") {
                        if (!vehicleExists(licensePlate)) {
                            Vehicle vehicle(licensePlate, owner, model);
                            addVehicle(vehicle);
                        }
                        licensePlate = "";
                        owner = "";
                        model = "";
						serviceHistory = false;
                    }
                    else if (serviceHistory) {
                        if (!vehicleExists(licensePlate)) {
							Vehicle vehicle(licensePlate, owner, model);
							addVehicle(vehicle);
                        }
                        size_t startPos = line.find(',');
                        size_t endPos = line.find(',', startPos+1);
                        string name = line.substr(startPos+1, endPos-1);
						double price = stod(line.substr(endPos + 1));
						Service service(name, price);
						addServiceToVehicle(licensePlate, service);
                    }
                }
            }
        }
        else {
			cout << "Error opening file" << endl;
        }


    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }


}

void AutoService::addServiceToVehicle(const string& licensePlate, const Service& service) {
    if (!vehicleExists(licensePlate)) {
        throw runtime_error("Vehicle not found.");
    }
    serviceHistories[licensePlate].addService(service);
}

void AutoService::printServiceHistory(const string& licensePlate) const {
    if (!vehicleExists(licensePlate)) {
        throw runtime_error("Vehicle not found.");
    }

    const auto& history = serviceHistories.at(licensePlate);
    history.printHistory();
}

void AutoService::saveHistoryToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file for writing.");
    }

    for (const auto& vehicle : vehicles) {
        const string& licensePlate = vehicle.getLicensePlate();
        file << "License Plate: " << licensePlate << "\n";
        file << "Owner: " << vehicle.getOwnerName() << "\n";
        file << "Model: " << vehicle.getModel() << "\n";
        file << "Service History:\n";
        const auto& history = serviceHistories.at(licensePlate);
        history.saveToFile(file);
        file << "--------------------------\n";
    }
    file.close();
}