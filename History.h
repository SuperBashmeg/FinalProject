#ifndef HISTORY_H
#define HISTORY_H

#include "Service.h"
#include "lib.h"

struct ServiceRecord {
    Service service;

    ServiceRecord(const Service& service)
        : service(service) {
    }
};

class History {
private:
    vector<ServiceRecord> records;

public:
    void addService(const Service& service);
    void printHistory() const;
    void saveToFile(ostream& out) const;
};

#endif
