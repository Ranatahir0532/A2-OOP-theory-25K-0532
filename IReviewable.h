#pragma once
#include <string>
using namespace std;

// ============================================================
// ABSTRACT CLASS 4: IReviewable
// Purpose: Any entity that can receive user ratings/reviews
//          must define addReview() and getRating().
//          Hides internal storage of reviews from outside code.
// Used by: Vehicle (Car, Bike), Seller, Buyer
// ============================================================
class IReviewable {
public:
    virtual void   addReview(const string& comment, int rating) = 0;  // Pure virtual
    virtual double getRating()                             const = 0;  // Pure virtual
    virtual ~IReviewable() {}
};
