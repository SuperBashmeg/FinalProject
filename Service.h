#ifndef SERVICE_H
#define SERVICE_H

#include "lib.h"

class Service {
private:
    string name;
    double price;

public:
    Service(const string& name, double price);

    string getName() const;
    double getPrice() const;
};

#endif