#pragma once
#include <iostream>
using namespace std;

// ============================================================
// ABSTRACT CLASS 1: IDisplayable
// Purpose: Forces every derived class to implement its own
//          displayDetails() function. This is pure Abstraction —
//          we define WHAT must be done, not HOW.
// Used by: Vehicle (Car, Bike), User (Buyer, Seller, Admin)
// ============================================================
class IDisplayable {
public:
    virtual void displayDetails() const = 0;   // Pure virtual function
    virtual ~IDisplayable() {}
};
