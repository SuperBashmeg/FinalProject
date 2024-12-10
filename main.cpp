#include "lib.h"
#include "AutoService.h"

void printMenu() {
    cout << "\nWelcome to the Auto Service Management System\n";
    cout << "1. Register a new vehicle\n";
    cout << "2. Add a service to a vehicle\n";
    cout << "3. View service history for a vehicle\n";
    cout << "4. Save service history to file\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    try {
        AutoService autoService;
        int choice;

		autoService.loadHistory();

        do {
            printMenu();
            cin >> choice;
			if (cin.fail()) {
				cin.clear(); // Clear error flag
				cout << "Invalid choice. Please try again.\n";
			}
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

            switch (choice) {
            case 1: {
                // Register a new vehicle
                string licensePlate, owner, model;
                cout << "Enter license plate: ";
                getline(cin, licensePlate);
                cout << "Enter owner's name: ";
                getline(cin, owner);
                cout << "Enter vehicle model: ";
                getline(cin, model);

                Vehicle vehicle(licensePlate, owner, model);
                autoService.addVehicle(vehicle);
                cout << "Vehicle registered successfully!\n";
                break;
            }
            case 2: {
                // Add a service
				cout << "Existing Cars: ";
				for (Vehicle vehicle : autoService.getVehicles()) {
					cout << vehicle.getLicensePlate() << "\n";
				}
                string licensePlate, serviceName;
                double serviceCost;
                cout << "Enter license plate: ";
                getline(cin, licensePlate);

                if (!autoService.vehicleExists(licensePlate)) {
                    cout << "Vehicle not found. Please register the vehicle first.\n";
                    break;
                }

                cout << "Enter service name: ";
                getline(cin, serviceName);
                cout << "Enter service cost: ";
                do {
                    cin >> serviceCost;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
					if (cin.fail()) {
                        cin.clear();
						cout << "Error: service cost can't be a number";
                        break;
					}
					else if (serviceCost < 0) {
						cout << "Service cost cannot be negative. Please try again: ";
                        cin.clear();
					}
                } while (serviceCost < 0);
                

                Service service(serviceName, serviceCost);
                autoService.addServiceToVehicle(licensePlate, service);
                cout << "Service added successfully!\n";
                break;
            }
            case 3: {
                cout << "Existing Cars: ";
                for (Vehicle vehicle : autoService.getVehicles()) {
                    cout << vehicle.getLicensePlate() << "\n";
                }
                string licensePlate;
                cout << "Enter license plate: ";
                getline(cin, licensePlate);

                if (!autoService.vehicleExists(licensePlate)) {
                    cout << "Vehicle not found.\n";
                    break;
                }

                cout << "Service history for vehicle [" << licensePlate << "]:\n";
                autoService.printServiceHistory(licensePlate);
                break;
            }
            case 4: {
                // Save service history to file
                autoService.saveHistoryToFile("service_history.txt");
                cout << "Service history saved to file successfully!\n";
                break;
            }
            case 5:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        } while (choice != 5);
    }
    catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << '\n';
    }

    return 0;
}
