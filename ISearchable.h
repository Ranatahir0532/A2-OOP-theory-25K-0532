#pragma once
#include <string>
using namespace std;

// ============================================================
// ABSTRACT CLASS 3: ISearchable
// Purpose: Enables polymorphic searching across all entity types.
//          Each class defines its own matching logic internally.
//          The marketplace only needs to call matchesSearch().
// Used by: Car, Bike, Seller, Buyer
// ============================================================
class ISearchable {
public:
    virtual bool matchesSearch(const string& keyword) const = 0;  // Pure virtual
    virtual ~ISearchable() {}
};
