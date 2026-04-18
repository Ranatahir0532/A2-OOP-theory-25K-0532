#pragma once

// ============================================================
// ABSTRACT CLASS 2: IPriceable
// Purpose: Any entity with a price must implement getPrice()
//          and applyDiscount(). Hides HOW pricing works —
//          only the interface is visible to the outside world.
// Used by: Vehicle (Car, Bike), Listing
// ============================================================
class IPriceable {
public:
    virtual double getPrice()              const = 0;  // Pure virtual
    virtual void   applyDiscount(double pct)     = 0;  // Pure virtual
    virtual ~IPriceable() {}
};
