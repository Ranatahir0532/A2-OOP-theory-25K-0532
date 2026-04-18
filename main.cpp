#include "CarMarketplace2.h"
#include <iostream>
using namespace std;

void printSeparator(const string& title = "") {
    cout << "\n========================================" << endl;
    if (!title.empty()) cout << "  " << title << endl;
    cout << "========================================" << endl;
}

int main() {
    printSeparator("PakWheels-Style Car Marketplace - Assignment 2");

   
    // 1. Create Marketplace

    Marketplace market;

  
    // 2. Create Sellers (Inheritance: Seller -> User)
    
    ContactInfo sellerContact("0300-1234567", "ahmed@email.com", true);
    Address sellerAddress("House 12, DHA Phase 5", "Karachi", "Sindh", "75500");
    Seller seller1("ahmed_autos", "pass123", sellerContact, sellerAddress);
    market.registerSeller(seller1);

    ContactInfo seller2Contact("0321-9876543", "cars@lahore.com", false);
    Address seller2Address("Main Boulevard", "Lahore", "Punjab", "54000");
    Seller seller2("lahore_motors", "pass456", seller2Contact, seller2Address);
    market.registerSeller(seller2);

   
    // 3. Create Buyers (Inheritance: Buyer -> User)
   
    ContactInfo buyerContact("0312-5555555", "buyer@gmail.com", true);
    Address buyerAddress("Clifton Block 4", "Karachi", "Sindh", "75600");
    Buyer buyer1("zain_buyer", "buypass", buyerContact, buyerAddress, 2500000.0);
    market.registerBuyer(buyer1);

    
    // 4. Create Admin (Inheritance: Admin -> User)
    
    ContactInfo adminContact("0333-0000001", "admin@pakwheels.pk", false);
    Address adminAddress("I.I Chundrigar Road", "Karachi", "Sindh", "74000");
    Admin admin1("super_admin", "admin123", adminContact, adminAddress, "SuperAdmin", "ADM001");

    
    // 5. Create CAR objects (Inheritance: Car -> Vehicle)
    //    Car now has extra fields: doors, transmission, bodyType, sunroof
    
    printSeparator("Creating Car & Bike Objects (Inheritance Demo)");

    Car car1("Toyota", "Corolla", 2020, 2800000, 45000, "White",
             4, "Automatic", "Sedan", false);
    Car car2("Honda", "Civic", 2022, 4200000, 22000, "Silver",
             4, "Automatic", "Sedan", true);
    Car car3("Suzuki", "Alto", 2021, 1600000, 38000, "Red",
             5, "Manual", "Hatchback", false);
    Car car4("Toyota", "Yaris", 2023, 3100000, 10000, "Black",
             4, "Automatic", "Sedan", false);
    Car car5("Kia", "Sportage", 2021, 5500000, 55000, "Blue",
             5, "Automatic", "SUV", true);

    // Create BIKE objects (Inheritance: Bike -> Vehicle)
    Bike bike1("Yamaha", "YBR125G", 2022, 280000, 12000, "Black",
               "Commuter", 125, true);
    Bike bike2("Honda", "CB150F", 2023, 380000, 8000, "Red",
               "Sports", 150, true);

    cout << "--- Polymorphism: displayDetails() called via Vehicle pointer ---" << endl;
    Vehicle* vPtr;

    
    vPtr = &car1;   vPtr->displayDetails();   // Calls Car::displayDetails()
    vPtr = &car2;   vPtr->displayDetails();   // Calls Car::displayDetails()
    vPtr = &bike1;  vPtr->displayDetails();   // Calls Bike::displayDetails()
    vPtr = &bike2;  vPtr->displayDetails();   // Calls Bike::displayDetails()

   
    // 6. Create Listings (still using Vehicle base class for compatibility)
   
    CarSpecifications s1("Petrol", "Automatic", 1800, "Karachi", 2020, "Used");
    Listing l1(1, car1, s1, "Excellent condition, 1 owner, full service history", "2026-03-01", "ahmed_autos");

    CarSpecifications s2("Petrol", "Automatic", 1500, "Lahore", 2022, "Used");
    Listing l2(2, car2, s2, "Turbo variant, almost new", "2026-03-02", "lahore_motors");

    CarSpecifications s3("Petrol", "Manual", 660, "Karachi", 2021, "Used");
    Listing l3(3, car3, s3, "Good fuel economy, perfect city car", "2026-03-02", "ahmed_autos");

    CarSpecifications s4("Hybrid", "Automatic", 1500, "Islamabad", 2023, "Used");
    Listing l4(4, car4, s4, "Hybrid variant, very low mileage", "2026-03-03", "lahore_motors");

    CarSpecifications s5("Petrol", "Automatic", 2000, "Karachi", 2021, "Used");
    Listing l5(5, car5, s5, "AWD, panoramic roof, premium sound", "2026-03-03", "ahmed_autos");

    market.addListing(l1);
    market.addListing(l2);
    market.addListing(l3);
    market.addListing(l4);
    market.addListing(l5);

    seller1.addListing(&l1); seller1.addListing(&l3); seller1.addListing(&l5);
    seller2.addListing(&l2); seller2.addListing(&l4);

    
    // 7. Admin moderation
    
    printSeparator("Admin Moderation");

    admin1.approveListing(l1);
    admin1.approveListing(l2);
    admin1.approveListing(l3);
    admin1.approveListing(l4);
    admin1.rejectListing(l5, "Incomplete documentation");
    admin1.viewStats();

    market.updateListingStatus(1, "Approved");
    market.updateListingStatus(2, "Approved");
    market.updateListingStatus(3, "Approved");
    market.updateListingStatus(4, "Approved");
    market.updateListingStatus(5, "Rejected");

   
    // 8. Admin uses friend class access to validate a Car's private fields
   
    printSeparator("Admin Friend Class — Validating Car Private Fields");
    admin1.validateCarListing(car2);  // Admin directly reads Car's private: numDoors, hasSunroof, bodyType

   
    // 9. Polymorphism — displayDetails() via IDisplayable pointer
   
    printSeparator("Polymorphism via IDisplayable Pointer");

    IDisplayable* dispPtr;
    dispPtr = &seller1;  dispPtr->displayDetails();  
    dispPtr = &buyer1;   dispPtr->displayDetails();  
    dispPtr = &admin1;   dispPtr->displayDetails();  

 
    // 10. Abstraction — IPriceable interface usage
   
    printSeparator("Abstraction via IPriceable Interface");

    IPriceable* pricePtr;
    pricePtr = &car1;    pricePtr->applyDiscount(5.0);   
    pricePtr = &bike1;   pricePtr->applyDiscount(3.0);   
    pricePtr = &l2;      pricePtr->applyDiscount(2.0);   

    /
    // 11. Operator Overloading demonstrations
    
    printSeparator("Operator Overloading Demonstrations");

    // == on Vehicle (checks brand+model+year)
    cout << "\n[OP ==] Are car1 and car3 the same vehicle? "
         << (car1 == car3 ? "Yes" : "No") << endl;

    // < and > on Vehicle (price comparison)
    cout << "[OP < ] Is car3 cheaper than car2? "
         << (car3 < car2 ? "Yes" : "No") << endl;
    cout << "[OP > ] Is car5 more expensive than car1? "
         << (car5 > car1 ? "Yes" : "No") << endl;

    // << on Vehicle (stream output)
    cout << "\n[OP <<] " << car1 << endl;
    cout << "[OP <<] " << bike1 << endl;

    // == on Address (same city check)
    cout << "\n[OP ==] Do seller1 and buyer1 share same city? "
         << (sellerAddress == buyerAddress ? "Yes" : "No") << endl;

    // == on ContactInfo (duplicate check)
    cout << "[OP ==] Same contact info? "
         << (sellerContact == seller2Contact ? "Yes (duplicate!)" : "No (unique)") << endl;

    // == on Listing (duplicate listing check)
    cout << "[OP ==] Listing l1 == l1? "
         << (l1 == l1 ? "Yes" : "No") << endl;
    cout << "[OP ==] Listing l1 == l2? "
         << (l1 == l2 ? "Yes" : "No") << endl;

    // << on Listing (stream output)
    cout << "\n[OP <<] " << l1 << endl;

    // == on User (duplicate user check)
    cout << "\n[OP ==] seller1 == seller2? "
         << (seller1 == seller2 ? "Yes (duplicate!)" : "No (unique)") << endl;

    // + on Bike (bundle price)
    double bikeBundle = bike1 + bike2;
    cout << "\n[OP + ] Bike bundle price: PKR " << bikeBundle << endl;

    // + on Buyer (add budget)
    Buyer buyer2 = buyer1 + 500000.0;
    cout << "[OP + ] " << buyer2.getUsername() << " new budget: PKR " << buyer2.getBudget() << endl;

    
    // 12. Friend Functions demonstrations
   
    printSeparator("Friend Function Demonstrations");

    // Friend function #1: comparePrices (accesses private price of both vehicles)
    cout << "\n[FRIEND] comparePrices(car3, car1):" << endl;
    comparePrices(car3, car1);

    // Friend function #2: printVehicleSummary (accesses multiple private Vehicle fields)
    cout << "\n[FRIEND] printVehicleSummary(car2):" << endl;
    printVehicleSummary(car2);

    // Friend function #3: compareEngineCC (accesses private engineCC of both Bikes)
    cout << "\n[FRIEND] compareEngineCC(bike1, bike2):" << endl;
    compareEngineCC(bike1, bike2);

    // Friend function #4: transferListing (accesses private sellerUsername and status)
    cout << "\n[FRIEND] transferListing(l3, \"new_seller_pk\"):" << endl;
    transferListing(l3, "new_seller_pk");

    // 13. IReviewable — abstract interface for reviews
   
    printSeparator("IReviewable Interface — Reviews and Ratings");

    car1.addReview("Excellent car, very comfortable", 5);
    car1.addReview("Good value for money", 4);
    bike1.addReview("Great bike for city commute", 5);
    seller1.addReview("Very honest seller", 5);
    seller1.addReview("Fast response time", 4);

    IReviewable* revPtr;
    revPtr = &car1;   cout << "car1 rating: " << revPtr->getRating() << "/5" << endl;
    revPtr = &bike1;  cout << "bike1 rating: " << revPtr->getRating() << "/5" << endl;
    revPtr = &seller1;cout << "seller1 rating: " << revPtr->getRating() << "/5" << endl;

   
    // 14. ISearchable — abstract interface for search
   
    printSeparator("ISearchable Interface — Polymorphic Search");

    ISearchable* srchPtr;
    srchPtr = &car2;   cout << "car2 matches 'Civic'? " << (srchPtr->matchesSearch("Civic") ? "Yes" : "No") << endl;
    srchPtr = &bike1;  cout << "bike1 matches '125'?  " << (srchPtr->matchesSearch("125")   ? "Yes" : "No") << endl;
    srchPtr = &seller1;cout << "seller1 matches 'ahmed'? " << (srchPtr->matchesSearch("ahmed") ? "Yes" : "No") << endl;

    
    // 15. All original A1 features 
   
    printSeparator("Buyer Search and Favorites (A1 Features)");

    SearchFilter filter1; filter1.setBrand("Toyota");
    cout << "\n>> Search: Toyota vehicles" << endl;
    market.searchListings(filter1);

    SearchFilter filter2; filter2.setPriceRange(1000000, 3000000);
    cout << "\n>> Search: Budget PKR 1M - 3M" << endl;
    market.searchListings(filter2);

    buyer1.saveFavorite(&l1);
    buyer1.saveFavorite(&l4);
    buyer1.viewFavorites();

    buyer1.sendMessage("ahmed_autos", "Hi! Is the Corolla still available?", "2026-03-04 10:30");
    buyer1.sendMessage("lahore_motors", "Interested in the Yaris Hybrid.", "2026-03-04 11:00");
    buyer1.viewInbox();

    // 16. Function Overloading (displayDetails with argument)
   
    printSeparator("Function Overloading — displayDetails(bool)");

    car1.displayDetails(true);    
    bike2.displayDetails(true);   
    seller1.displayDetails(true); 

    // 17. Seller operations and platform stats
   
    printSeparator("Seller Operations & Platform Stats");

    seller1.viewMyListings();
    seller1.removeListing(3);
    market.deleteListing(3);
    seller1.viewMyListings();

    Marketplace::recordTransaction();
    Marketplace::recordTransaction();
    market.displayStats();

   
    // 18. Copy constructor demo 
   printSeparator("Copy Constructor Demo");

    Vehicle v1Copy(car1);
    cout << "Original: "; car1.display();
    cout << "Copy:     "; v1Copy.display();

    Address addrCopy(sellerAddress);
    cout << "Original address: "; sellerAddress.display();
    cout << "Copied address:   "; addrCopy.display();

    cout << "\n=== Assignment 2 Completed Successfully ===" << endl;
    return 0;
}
