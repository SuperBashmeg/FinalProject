#define _CRT_SECURE_NO_WARNINGS

#include "History.h"

void History::addService(const Service& service) {
	records.push_back(ServiceRecord(service));
}

void History::printHistory() const {
    if (records.empty()) {
        cout << "No service history available.\n";
        return;
    }

    for (const auto& record : records) {
        cout << " - " << record.service.getName()
            << ": $" << record.service.getPrice() << "\n";
    }
}

void History::saveToFile(ostream& out) const {
    if (records.empty()) {
        out << "No service history available.\n";
        return;
    }

    for (const auto& record : records) {
        out << "," << record.service.getName()
            << "," << record.service.getPrice() << "\n";
    }
}