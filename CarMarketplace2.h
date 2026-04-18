#pragma once
#include "IDisplayable.h"
#include "IPriceable.h"
#include "ISearchable.h"
#include "IReviewable.h"
#include <iostream>
#include <string>
using namespace std;

// Forward declarations
class Seller;
class Buyer;
class Vehicle;
class Car;
class Bike;
class Admin;

// ============================================================
// CLASS 1: Address
// ============================================================
class Address {
private:
    string street;
    string city;
    string province;
    string postalCode;
    const string country;

public:
    Address() : street(""), city(""), province(""), postalCode(""), country("Pakistan") {}
    Address(string st, string ct, string prov, string postal)
        : street(st), city(ct), province(prov), postalCode(postal), country("Pakistan") {}
    Address(const Address& other)
        : street(other.street), city(other.city), province(other.province),
          postalCode(other.postalCode), country(other.country) {}

    Address& operator=(const Address& other) {
        if (this != &other) {
            street = other.street; city = other.city;
            province = other.province; postalCode = other.postalCode;
        }
        return *this;
    }

    string getStreet()     const { return street; }
    string getCity()       const { return city; }
    string getProvince()   const { return province; }
    string getPostalCode() const { return postalCode; }
    string getCountry()    const { return country; }
    void   setStreet(string s)   { street = s; }
    void   setCity(string c)     { city = c; }
    void   setProvince(string p) { province = p; }
    void   setPostalCode(string p){ postalCode = p; }

    void display() const {
        cout << street << ", " << city << ", " << province
             << " - " << postalCode << ", " << country << endl;
    }

    bool isValidPostalCode()  const { return postalCode.length() == 5; }
    bool isSameCity(const Address& o) const { return city == o.city; }
    string getFullAddress()   const { return street + ", " + city + ", " + province; }

    // OPERATOR OVERLOADING #1 — == (member): compare two addresses by city
    // Reason: Lets marketplace check if buyer & seller are in same city
    bool operator==(const Address& other) const { return city == other.city && province == other.province; }

    // OPERATOR OVERLOADING #2 — != (member)
    bool operator!=(const Address& other) const { return !(*this == other); }

    // OPERATOR OVERLOADING #3 — << (global friend): stream output
    // Reason: Allows cout << address directly for clean display code
    friend ostream& operator<<(ostream& os, const Address& a) {
        os << a.street << ", " << a.city << ", " << a.province
           << " - " << a.postalCode << ", " << a.country;
        return os;
    }
};

// ============================================================
// CLASS 2: ContactInfo  
// ============================================================
class ContactInfo {
private:
    string phoneNumber;
    string email;
    bool   whatsappEnabled;
    string alternatePhone;
    const string platformCode;

public:
    ContactInfo() : phoneNumber(""), email(""), whatsappEnabled(false),
                    alternatePhone(""), platformCode("PW") {}
    ContactInfo(string phone, string em, bool wa)
        : phoneNumber(phone), email(em), whatsappEnabled(wa),
          alternatePhone(""), platformCode("PW") {}
    ContactInfo(const ContactInfo& other)
        : phoneNumber(other.phoneNumber), email(other.email),
          whatsappEnabled(other.whatsappEnabled), alternatePhone(other.alternatePhone),
          platformCode(other.platformCode) {}

    ContactInfo& operator=(const ContactInfo& other) {
        if (this != &other) {
            phoneNumber = other.phoneNumber; email = other.email;
            whatsappEnabled = other.whatsappEnabled; alternatePhone = other.alternatePhone;
        }
        return *this;
    }

    string getPhone()   const { return phoneNumber; }
    string getEmail()   const { return email; }
    bool   isWhatsapp() const { return whatsappEnabled; }
    void   setPhone(string p) { phoneNumber = p; }
    void   setEmail(string e) { email = e; }
    void   setWhatsapp(bool w){ whatsappEnabled = w; }

    void display() const {
        cout << "Phone: " << phoneNumber << " | Email: " << email;
        if (whatsappEnabled) cout << " | WhatsApp: Available";
        cout << endl;
    }

    bool isValidEmail()     const { return email.find('@') != string::npos && email.find('.') != string::npos; }
    bool isContactable()    const { return !phoneNumber.empty() || !email.empty(); }
    string getPrimaryContact() const { return whatsappEnabled ? "WhatsApp: " + phoneNumber : "Phone: " + phoneNumber; }

    // OPERATOR OVERLOADING #4 — == (member): compare contacts by phone
    // Reason: Check for duplicate registrations
    bool operator==(const ContactInfo& other) const { return phoneNumber == other.phoneNumber; }

    // OPERATOR OVERLOADING #5 — << (global friend): stream output for ContactInfo
    friend ostream& operator<<(ostream& os, const ContactInfo& c) {
        os << "Phone: " << c.phoneNumber << " | Email: " << c.email;
        if (c.whatsappEnabled) os << " | WhatsApp: Yes";
        return os;
    }
};

// ============================================================
// CLASS 3: Message  
// ============================================================
class Message {
private:
    int    messageId;
    string senderName;
    string receiverName;
    string content;
    string timestamp;
    bool   isRead;
    static int messageCount;

public:
    Message() : messageId(0), senderName(""), receiverName(""),
                content(""), timestamp(""), isRead(false) {}
    Message(int id, string sender, string receiver, string msg, string time)
        : messageId(id), senderName(sender), receiverName(receiver),
          content(msg), timestamp(time), isRead(false) { messageCount++; }

    int    getId()        const { return messageId; }
    string getSender()    const { return senderName; }
    string getReceiver()  const { return receiverName; }
    string getContent()   const { return content; }
    string getTimestamp() const { return timestamp; }
    bool   getIsRead()    const { return isRead; }
    void   markAsRead()         { isRead = true; }

    static int  getTotalMessages() { return messageCount; }
    static void resetCount()       { messageCount = 0; }

    void display() const {
        cout << "[" << timestamp << "] From: " << senderName
             << " -> To: " << receiverName << endl;
        cout << "  Message: " << content << (isRead ? " [Read]" : " [Unread]") << endl;
    }

    bool containsKeyword(const string& kw) const { return content.find(kw) != string::npos; }
    string getSummary() const { return senderName + ": " + content.substr(0, 50); }

    // OPERATOR OVERLOADING #6 — << (global friend): stream output for Message
    // Reason: Consistent output format without calling display() explicitly
    friend ostream& operator<<(ostream& os, const Message& m) {
        os << "[" << m.timestamp << "] " << m.senderName << " -> "
           << m.receiverName << ": " << m.content;
        return os;
    }
};

int Message::messageCount = 0;

// ============================================================
// CLASS 4: Vehicle  (BASE class — Inheritance: Car, Bike extend this)
// Now implements 4 abstract interfaces (Abstraction)
// ============================================================
class Vehicle : public IDisplayable, public IPriceable,
                public ISearchable,  public IReviewable {
protected:
    string brand;
    string model;
    int    year;
    double price;
    int    mileage;
    string color;
    string vehicleType;         // "Car" or "Bike" — set by derived class

    // For IReviewable
    string reviewComments[20];
    int    reviewRatings[20];
    int    reviewCount;

    static int totalVehiclesListed;

public:
    // Default constructor
    Vehicle() : brand(""), model(""), year(0), price(0.0), mileage(0),
                color(""), vehicleType("Vehicle"), reviewCount(0) {}

    // Parameterized constructor
    Vehicle(string br, string mo, int yr, double pr, int mi, string col)
        : brand(br), model(mo), year(yr), price(pr), mileage(mi),
          color(col), vehicleType("Vehicle"), reviewCount(0) {
        totalVehiclesListed++;
    }

    // Copy constructor
    Vehicle(const Vehicle& v)
        : brand(v.brand), model(v.model), year(v.year), price(v.price),
          mileage(v.mileage), color(v.color), vehicleType(v.vehicleType),
          reviewCount(v.reviewCount) {
        for (int i = 0; i < reviewCount; i++) {
            reviewComments[i] = v.reviewComments[i];
            reviewRatings[i]  = v.reviewRatings[i];
        }
    }

    virtual ~Vehicle() {}

    // ---- Getters / Setters ----
    string getBrand()  const { return brand; }
    string getModel()  const { return model; }
    int    getYear()   const { return year; }
    double getPrice()  const override { return price; }
    int    getMileage()const { return mileage; }
    string getColor()  const { return color; }
    string getType()   const { return vehicleType; }

    void setBrand(string b)  { brand = b; }
    void setModel(string m)  { model = m; }
    void setYear(int y)      { year = y; }
    void setPrice(double p)  { price = p; }
    void setMileage(int m)   { mileage = m; }
    void setColor(string c)  { color = c; }

    static int getTotalVehicles() { return totalVehiclesListed; }

    // ---- IDisplayable — OVERRIDDEN by Car, Bike (Polymorphism) ----
    virtual void displayDetails() const override {
        cout << year << " " << brand << " " << model
             << " | Price: PKR " << price
             << " | Mileage: " << mileage << " km"
             << " | Color: " << color << endl;
    }

    // Kept for backward compatibility with A1 main.cpp
    void display() const { displayDetails(); }

    // ---- IPriceable ----
    void applyDiscount(double pct) override {
        price -= price * (pct / 100.0);
        cout << brand << " " << model << " discounted by " << pct
             << "%. New price: PKR " << price << endl;
    }

    // ---- ISearchable ----
    bool matchesSearch(const string& keyword) const override {
        return brand.find(keyword) != string::npos ||
               model.find(keyword) != string::npos ||
               color.find(keyword) != string::npos;
    }

    // ---- IReviewable ----
    void addReview(const string& comment, int rating) override {
        if (reviewCount < 20 && rating >= 1 && rating <= 5) {
            reviewComments[reviewCount] = comment;
            reviewRatings[reviewCount]  = rating;
            reviewCount++;
            cout << "Review added for " << brand << " " << model << endl;
        }
    }

    double getRating() const override {
        if (reviewCount == 0) return 0.0;
        double sum = 0;
        for (int i = 0; i < reviewCount; i++) sum += reviewRatings[i];
        return sum / reviewCount;
    }

    // Helper methods (used by SearchFilter — same as A1)
    bool matchesBrand(const string& b) const { return brand == b; }
    bool matchesModel(const string& m) const { return model == m; }
    bool isPriceInRange(double lo, double hi) const { return price >= lo && price <= hi; }
    bool isYearInRange(int lo, int hi)  const { return year >= lo && year <= hi; }

    // OPERATOR OVERLOADING #7 — == (member): compare by brand+model+year
    // Reason: Check if two listings are for identical vehicles
    bool operator==(const Vehicle& other) const {
        return brand == other.brand && model == other.model && year == other.year;
    }

    // OPERATOR OVERLOADING #8 — < (member): compare by price (for sorting)
    // Reason: Allows sort by cheapest vehicle first
    bool operator<(const Vehicle& other) const { return price < other.price; }

    // OPERATOR OVERLOADING #9 — > (member): compare by price
    bool operator>(const Vehicle& other) const { return price > other.price; }

    // OPERATOR OVERLOADING #10 — << (global friend): stream output for Vehicle
    // Reason: Lets any class print a vehicle with cout << v cleanly
    friend ostream& operator<<(ostream& os, const Vehicle& v) {
        os << v.year << " " << v.brand << " " << v.model
           << " | PKR " << v.price << " | " << v.mileage << " km | " << v.color;
        return os;
    }

    // FRIEND FUNCTION #1 — comparePrices
    // Reason: Needs access to the private 'price' field of BOTH vehicles simultaneously.
    //         A member function can only directly access 'this' object's price.
    //         Making it a friend allows direct comparison of both objects' private data.
    friend bool comparePrices(const Vehicle& a, const Vehicle& b);

    // FRIEND FUNCTION #2 — printVehicleSummary
    // Reason: Needs to access multiple private fields (brand, model, price, mileage, reviewCount)
    //         for a formatted report. Using only getters would work but friend gives direct
    //         access for efficiency and cleaner formatting code.
    friend void printVehicleSummary(const Vehicle& v);
};

int Vehicle::totalVehiclesListed = 0;

// Friend function implementations
inline bool comparePrices(const Vehicle& a, const Vehicle& b) {
    if (a.price < b.price) { cout << a.brand << " " << a.model << " is cheaper." << endl; return true; }
    else { cout << b.brand << " " << b.model << " is cheaper or same price." << endl; return false; }
}

inline void printVehicleSummary(const Vehicle& v) {
    cout << "=== Vehicle Summary ===" << endl;
    cout << "  Brand/Model : " << v.brand << " " << v.model << " (" << v.year << ")" << endl;
    cout << "  Price       : PKR " << v.price << endl;
    cout << "  Mileage     : " << v.mileage << " km | Color: " << v.color << endl;
    cout << "  Reviews     : " << v.reviewCount << " | Rating: " << v.getRating() << "/5" << endl;
}

// ============================================================
// CLASS 5: Car  (DERIVED from Vehicle — Inheritance #1)
// Adds car-specific attributes; overrides displayDetails()
// ============================================================
class Car : public Vehicle {
private:
    int    numDoors;
    string transmission;
    string bodyType;       // Sedan, SUV, Hatchback, etc.
    bool   hasSunroof;

public:
    // Default constructor
    Car() : Vehicle(), numDoors(4), transmission("Automatic"),
            bodyType("Sedan"), hasSunroof(false) {
        vehicleType = "Car";
    }

    // Parameterized constructor (Inheritance #1: calls Vehicle constructor)
    Car(string br, string mo, int yr, double pr, int mi, string col,
        int doors, string trans, string body, bool sunroof = false)
        : Vehicle(br, mo, yr, pr, mi, col),
          numDoors(doors), transmission(trans),
          bodyType(body), hasSunroof(sunroof) {
        vehicleType = "Car";
    }

    // Getters / Setters
    int    getNumDoors()     const { return numDoors; }
    string getTransmission() const { return transmission; }
    string getBodyType()     const { return bodyType; }
    bool   getHasSunroof()   const { return hasSunroof; }
    void   setTransmission(string t) { transmission = t; }
    void   setBodyType(string b)     { bodyType = b; }
    void   setHasSunroof(bool s)     { hasSunroof = s; }

    // POLYMORPHISM — Function Overriding: Car's own displayDetails()
    // Displays car-specific info (doors, transmission, body type)
    void displayDetails() const override {
        cout << "[CAR] " << year << " " << brand << " " << model
             << " (" << bodyType << ", " << numDoors << " doors)" << endl;
        cout << "      Price: PKR " << price
             << " | Mileage: " << mileage << " km"
             << " | Color: " << color << endl;
        cout << "      Transmission: " << transmission
             << " | Sunroof: " << (hasSunroof ? "Yes" : "No")
             << " | Rating: " << getRating() << "/5" << endl;
    }

    // POLYMORPHISM — Function Overloading: displayDetails(bool) with extra flag
    void displayDetails(bool showReviews) const {
        displayDetails();
        if (showReviews && reviewCount > 0) {
            cout << "      Reviews:" << endl;
            for (int i = 0; i < reviewCount; i++)
                cout << "        - " << reviewComments[i] << " (" << reviewRatings[i] << "/5)" << endl;
        }
    }

    // ISearchable — Car-specific: also search body type and transmission
    bool matchesSearch(const string& keyword) const override {
        return Vehicle::matchesSearch(keyword) ||
               bodyType.find(keyword)     != string::npos ||
               transmission.find(keyword) != string::npos;
    }

    // IPriceable — Car discount with luxury tax logic
    void applyDiscount(double pct) override {
        if (price > 4000000) pct *= 0.8;  // Luxury cars get smaller discount
        Vehicle::applyDiscount(pct);
    }

    // OPERATOR OVERLOADING #11 — == (member override for Car)
    // Reason: Two cars are equal if brand, model, year AND body type match
    bool operator==(const Car& other) const {
        return brand == other.brand && model == other.model &&
               year  == other.year  && bodyType == other.bodyType;
    }

    // FRIEND CLASS declaration — Admin can access Car's private fields directly
    // Reason: Admin needs to verify hasSunroof and numDoors during listing validation
    //         without exposing these through public getters (encapsulation maintained for others)
    friend class Admin;
};

// ============================================================
// CLASS 6: Bike  (DERIVED from Vehicle — Inheritance #2)
// Adds bike-specific attributes; overrides displayDetails()
// ============================================================
class Bike : public Vehicle {
private:
    string bikeType;    // Sports, Cruiser, Commuter, Off-road
    int    engineCC;
    bool   hasGear;
    string brand125cc;  // Popular 125cc brands in Pakistan

public:
    // Default constructor
    Bike() : Vehicle(), bikeType("Commuter"), engineCC(125),
             hasGear(true), brand125cc("") {
        vehicleType = "Bike";
    }

    // Parameterized constructor (Inheritance #2: calls Vehicle constructor)
    Bike(string br, string mo, int yr, double pr, int mi, string col,
         string type, int cc, bool gear)
        : Vehicle(br, mo, yr, pr, mi, col),
          bikeType(type), engineCC(cc), hasGear(gear), brand125cc("") {
        vehicleType = "Bike";
    }

    // Getters / Setters
    string getBikeType() const { return bikeType; }
    int    getEngineCC() const { return engineCC; }
    bool   getHasGear()  const { return hasGear; }
    void   setBikeType(string t){ bikeType = t; }
    void   setEngineCC(int cc)  { engineCC = cc; }
    void   setHasGear(bool g)   { hasGear = g; }

    // POLYMORPHISM — Function Overriding: Bike's own displayDetails()
    void displayDetails() const override {
        cout << "[BIKE] " << year << " " << brand << " " << model
             << " (" << bikeType << ", " << engineCC << "cc)" << endl;
        cout << "       Price: PKR " << price
             << " | Mileage: " << mileage << " km"
             << " | Color: " << color << endl;
        cout << "       Gear: " << (hasGear ? "Yes" : "No")
             << " | Rating: " << getRating() << "/5" << endl;
    }

    // POLYMORPHISM — Overloading: displayDetails with detailed flag
    void displayDetails(bool compact) const {
        if (compact)
            cout << "[BIKE] " << brand << " " << model << " " << engineCC << "cc PKR " << price << endl;
        else
            displayDetails();
    }

    // ISearchable — Bike-specific: also search by bike type and CC
    bool matchesSearch(const string& keyword) const override {
        return Vehicle::matchesSearch(keyword) ||
               bikeType.find(keyword) != string::npos ||
               to_string(engineCC).find(keyword) != string::npos;
    }

    // OPERATOR OVERLOADING #12 — + (member): combine two bikes into a "bundle deal" price
    // Reason: Dealers sometimes sell two bikes together; + gives combined asking price
    double operator+(const Bike& other) const {
        return price + other.price;
    }

    // FRIEND FUNCTION #3 — compareEngineCC
    // Reason: Needs direct access to private engineCC of BOTH bikes.
    //         As a non-member it cannot access engineCC through 'this'.
    //         Declaring it friend avoids making engineCC public.
    friend void compareEngineCC(const Bike& a, const Bike& b);
};

inline void compareEngineCC(const Bike& a, const Bike& b) {
    cout << "Engine Comparison: " << a.brand << " " << a.model
         << " (" << a.engineCC << "cc) vs "
         << b.brand << " " << b.model << " (" << b.engineCC << "cc)" << endl;
    if (a.engineCC > b.engineCC)
        cout << a.brand << " " << a.model << " has the larger engine." << endl;
    else if (b.engineCC > a.engineCC)
        cout << b.brand << " " << b.model << " has the larger engine." << endl;
    else
        cout << "Both have the same engine size." << endl;
}

// ============================================================
// CLASS 7: CarSpecifications  (unchanged from A1 — Composition in Listing)
// ============================================================
class CarSpecifications {
private:
    string engineType;
    string transmission;
    int    engineCC;
    string registrationCity;
    const int modelYear;
    string condition;

public:
    CarSpecifications() : engineType(""), transmission(""), engineCC(0),
                          registrationCity(""), modelYear(0), condition("") {}
    CarSpecifications(string eng, string trans, int cc, string regCity, int yr, string cond)
        : engineType(eng), transmission(trans), engineCC(cc),
          registrationCity(regCity), modelYear(yr), condition(cond) {}
    CarSpecifications(const CarSpecifications& s)
        : engineType(s.engineType), transmission(s.transmission), engineCC(s.engineCC),
          registrationCity(s.registrationCity), modelYear(s.modelYear), condition(s.condition) {}

    CarSpecifications& operator=(const CarSpecifications& s) {
        if (this != &s) {
            engineType = s.engineType; transmission = s.transmission;
            engineCC = s.engineCC; registrationCity = s.registrationCity; condition = s.condition;
        }
        return *this;
    }

    string getEngineType()       const { return engineType; }
    string getTransmission()     const { return transmission; }
    int    getEngineCC()         const { return engineCC; }
    string getRegistrationCity() const { return registrationCity; }
    int    getModelYear()        const { return modelYear; }
    string getCondition()        const { return condition; }
    void   setEngineType(string e)     { engineType = e; }
    void   setTransmission(string t)   { transmission = t; }
    void   setEngineCC(int cc)         { engineCC = cc; }
    void   setRegistrationCity(string c){ registrationCity = c; }
    void   setCondition(string c)      { condition = c; }

    void display() const {
        cout << "Engine: " << engineType << " (" << engineCC << "cc) | "
             << "Trans: " << transmission << " | "
             << "Reg: " << registrationCity << " | "
             << "Condition: " << condition << endl;
    }

    bool isAutomatic() const { return transmission == "Automatic"; }
    bool isElectric()  const { return engineType == "Electric"; }
    string getSummary()const { return engineType + " " + to_string(engineCC) + "cc " + transmission; }
};

// ============================================================
// CLASS 8: Listing  (Composition: owns Vehicle + CarSpecifications)
// Now implements IPriceable (Abstraction)
// ============================================================
class Listing : public IPriceable {
private:
    int       listingId;
    Vehicle   vehicle;          // Composition
    CarSpecifications specs;    // Composition
    string    description;
    string    status;
    string    postedDate;
    string    sellerUsername;

public:
    Listing() : listingId(0), vehicle(), specs(), description(""),
                status("Pending"), postedDate(""), sellerUsername("") {}
    Listing(int id, Vehicle v, CarSpecifications s, string desc,
            string date, string seller)
        : listingId(id), vehicle(v), specs(s), description(desc),
          status("Pending"), postedDate(date), sellerUsername(seller) {}

    int         getId()          const { return listingId; }
    Vehicle     getVehicle()     const { return vehicle; }
    CarSpecifications getSpecs() const { return specs; }
    string      getStatus()      const { return status; }
    string      getSellerName()  const { return sellerUsername; }
    string      getPostedDate()  const { return postedDate; }
    void setStatus(string s)           { status = s; }
    void setDescription(string d)      { description = d; }

    // IPriceable implementation for Listing
    double getPrice()              const override { return vehicle.getPrice(); }
    void   applyDiscount(double pct)     override { vehicle.applyDiscount(pct); }

    void display() const {
        cout << "--- Listing #" << listingId << " [" << status << "] ---" << endl;
        vehicle.displayDetails();
        specs.display();
        cout << "Description: " << description << endl;
        cout << "Seller: " << sellerUsername << " | Posted: " << postedDate << endl;
    }

    bool isApproved() const { return status == "Approved"; }
    bool isPending()  const { return status == "Pending"; }
    bool matchesBrand(const string& b) const { return vehicle.matchesBrand(b); }
    bool matchesPriceRange(double lo, double hi) const { return vehicle.isPriceInRange(lo, hi); }

    // OPERATOR OVERLOADING #13 — == (member): two listings equal if same ID
    // Reason: Prevent duplicate listing insertion in Marketplace
    bool operator==(const Listing& other) const { return listingId == other.listingId; }

    // OPERATOR OVERLOADING #14 — << (global friend): stream output for Listing
    // Reason: Allows admin/buyer to print a listing with cout << listing
    friend ostream& operator<<(ostream& os, const Listing& l) {
        os << "Listing #" << l.listingId << " [" << l.status << "] | "
           << l.vehicle << " | Seller: " << l.sellerUsername;
        return os;
    }

    // FRIEND FUNCTION #4 — transferListing
    // Reason: Needs to change the private sellerUsername and status of a listing
    //         when a car is sold and ownership transfers to a new seller.
    //         This sensitive operation should not be exposed as a public setter.
    friend void transferListing(Listing& l, const string& newSeller);
};

inline void transferListing(Listing& l, const string& newSeller) {
    cout << "Transferring Listing #" << l.listingId << " from "
         << l.sellerUsername << " to " << newSeller << endl;
    l.sellerUsername = newSeller;
    l.status = "Transferred";
}

// ============================================================
// CLASS 9: User  (BASE class — Seller, Buyer, Admin extend this)
// Now implements IDisplayable (Abstraction + Polymorphism)
// ============================================================
class User : public IDisplayable, public ISearchable {
protected:
    string      username;
    string      passwordHash;
    ContactInfo contact;   // Composition
    Address     address;   // Composition
    string      userType;
    bool        isVerified;

public:
    User() : username(""), passwordHash(""), contact(), address(),
             userType(""), isVerified(false) {}
    User(string uname, string pwd, ContactInfo ci, Address addr, string type)
        : username(uname), passwordHash(pwd), contact(ci), address(addr),
          userType(type), isVerified(false) {}

    string getUsername()   const { return username; }
    string getUserType()   const { return userType; }
    bool   getIsVerified() const { return isVerified; }
    ContactInfo getContact() const { return contact; }
    Address     getAddress() const { return address; }
    void setUsername(string u) { username = u; }
    void verify()              { isVerified = true; }

    // IDisplayable — overridden by Seller, Buyer, Admin (Polymorphism)
    virtual void displayDetails() const override {
        cout << "=== " << userType << " Profile ===" << endl;
        cout << "Username: " << username << (isVerified ? " [Verified]" : "") << endl;
        contact.display();
        address.display();
    }

    // Kept for backward compat with A1 main.cpp
    virtual void displayProfile() const { displayDetails(); }

    // ISearchable — search users by username
    bool matchesSearch(const string& keyword) const override {
        return username.find(keyword) != string::npos ||
               userType.find(keyword) != string::npos;
    }

    bool   isLoggedIn()       const { return !username.empty(); }
    bool   hasValidContact()  const { return contact.isContactable(); }
    string getDisplayName()   const { return username + " (" + userType + ")"; }

    // OPERATOR OVERLOADING #15 — == (member): users equal if same username
    // Reason: Prevents duplicate user registration
    bool operator==(const User& other) const { return username == other.username; }

    // OPERATOR OVERLOADING #16 — << (global friend): stream output for User
    friend ostream& operator<<(ostream& os, const User& u) {
        os << u.userType << ": " << u.username
           << (u.isVerified ? " [Verified]" : " [Unverified]");
        return os;
    }

    virtual ~User() {}
};

// ============================================================
// CLASS 10: Seller  (DERIVED from User — Inheritance #3)
// Also implements IReviewable (sellers can be reviewed)
// ============================================================
class Seller : public User, public IReviewable {
private:
    Listing*  listings[50];   // Aggregation
    int       listingCount;
    int       totalSales;
    double    totalRevenue;
    string    sellerRating;

    // For IReviewable
    string reviewComments[10];
    int    reviewRatings[10];
    int    sellerReviewCount;

public:
    // Default constructor
    Seller() : User(), listingCount(0), totalSales(0),
               totalRevenue(0.0), sellerRating("0/5"), sellerReviewCount(0) {
        for (int i = 0; i < 50; i++) listings[i] = nullptr;
    }

    // Parameterized constructor (Inheritance #3: calls User constructor)
    Seller(string uname, string pwd, ContactInfo ci, Address addr)
        : User(uname, pwd, ci, addr, "Seller"),
          listingCount(0), totalSales(0),
          totalRevenue(0.0), sellerRating("5/5"), sellerReviewCount(0) {
        for (int i = 0; i < 50; i++) listings[i] = nullptr;
    }

    int    getListingCount()   const { return listingCount; }
    int    getTotalSales()     const { return totalSales; }
    double getTotalRevenue()   const { return totalRevenue; }
    string getSellerRating()   const { return sellerRating; }  // renamed to avoid conflict with IReviewable::getRating()
    void   setSellerRating(string r) { sellerRating = r; }

    void addListing(Listing* l) {
        if (listingCount < 50) {
            listings[listingCount++] = l;
            cout << "Listing added by " << username << endl;
        }
    }

    void removeListing(int id) {
        for (int i = 0; i < listingCount; i++) {
            if (listings[i] && listings[i]->getId() == id) {
                for (int j = i; j < listingCount - 1; j++) listings[j] = listings[j+1];
                listings[--listingCount] = nullptr;
                cout << "Listing #" << id << " removed." << endl;
                return;
            }
        }
        cout << "Listing not found." << endl;
    }

    void viewMyListings() const {
        cout << "=== Listings by " << username << " ===" << endl;
        for (int i = 0; i < listingCount; i++)
            if (listings[i]) listings[i]->display();
    }

    void recordSale(double amount) { totalSales++; totalRevenue += amount; }

    // IReviewable
    void addReview(const string& comment, int rating) override {
        if (sellerReviewCount < 10 && rating >= 1 && rating <= 5) {
            reviewComments[sellerReviewCount] = comment;
            reviewRatings[sellerReviewCount]  = rating;
            sellerReviewCount++;
        }
    }
    double getRating() const override {
        if (sellerReviewCount == 0) return 0.0;
        double sum = 0;
        for (int i = 0; i < sellerReviewCount; i++) sum += reviewRatings[i];
        return sum / sellerReviewCount;
    }

    // Polymorphism — overrides User::displayDetails()
    void displayDetails() const override {
        User::displayDetails();
        cout << "Total Listings: " << listingCount << " | Sales: " << totalSales
             << " | Revenue: PKR " << totalRevenue << " | Rating: " << sellerRating << endl;
    }

    // POLYMORPHISM — Function Overloading: displayDetails(bool)
    void displayDetails(bool showListings) const {
        displayDetails();
        if (showListings) viewMyListings();
    }

    void displayProfile() const override { displayDetails(); }
};

// ============================================================
// CLASS 11: Buyer  (DERIVED from User — Inheritance #4)
// ============================================================
class Buyer : public User {
private:
    Listing*  favorites[20];  // Aggregation
    int       favCount;
    Message   inbox[100];     // Composition
    int       inboxCount;
    double    budget;
    string    preferredCity;

public:
    Buyer() : User(), favCount(0), inboxCount(0), budget(0.0), preferredCity("") {
        for (int i = 0; i < 20; i++) favorites[i] = nullptr;
    }
    Buyer(string uname, string pwd, ContactInfo ci, Address addr, double bud)
        : User(uname, pwd, ci, addr, "Buyer"),
          favCount(0), inboxCount(0), budget(bud), preferredCity(addr.getCity()) {
        for (int i = 0; i < 20; i++) favorites[i] = nullptr;
    }

    double getBudget()        const { return budget; }
    string getPreferredCity() const { return preferredCity; }
    int    getFavCount()      const { return favCount; }
    void   setBudget(double b)      { budget = b; }
    void   setPreferredCity(string c){ preferredCity = c; }

    void saveFavorite(Listing* l) {
        if (favCount < 20) { favorites[favCount++] = l; cout << "Listing saved to favorites!" << endl; }
    }
    void removeFavorite(int listingId) {
        for (int i = 0; i < favCount; i++) {
            if (favorites[i] && favorites[i]->getId() == listingId) {
                for (int j = i; j < favCount - 1; j++) favorites[j] = favorites[j+1];
                favorites[--favCount] = nullptr;
                cout << "Removed from favorites." << endl;
                return;
            }
        }
    }
    void sendMessage(const string& sellerName, const string& content, const string& time) {
        if (inboxCount < 100) {
            int msgId = inboxCount + 1;
            inbox[inboxCount++] = Message(msgId, username, sellerName, content, time);
            cout << "Message sent to " << sellerName << endl;
        }
    }
    void viewFavorites() const {
        cout << "=== " << username << "'s Favorites ===" << endl;
        for (int i = 0; i < favCount; i++) if (favorites[i]) favorites[i]->display();
    }
    void viewInbox() const {
        cout << "=== " << username << "'s Messages ===" << endl;
        for (int i = 0; i < inboxCount; i++) inbox[i].display();
    }

    // Polymorphism — overrides User::displayDetails()
    void displayDetails() const override {
        User::displayDetails();
        cout << "Budget: PKR " << budget << " | Favorites: " << favCount
             << " | Preferred City: " << preferredCity << endl;
    }
    void displayProfile() const override { displayDetails(); }

    // POLYMORPHISM — Function Overloading: displayDetails(bool verbose)
    void displayDetails(bool showFavorites) const {
        displayDetails();
        if (showFavorites) viewFavorites();
    }

    // OPERATOR OVERLOADING #17 — + (member): increase buyer budget by amount
    // Reason: Simulates buyer adding more funds to their account; returns new Buyer copy
    Buyer operator+(double amount) const {
        Buyer copy = *this;
        copy.budget += amount;
        cout << username << "'s budget increased to PKR " << copy.budget << endl;
        return copy;
    }
};

// ============================================================
// CLASS 12: Admin  (DERIVED from User — Inheritance #5)
// Friend class of Car (can access Car's private fields)
// ============================================================
class Admin : public User {
private:
    string    adminLevel;
    int       approvedCount;
    int       rejectedCount;
    string    department;
    const string adminCode;

public:
    Admin() : User(), adminLevel(""), approvedCount(0),
              rejectedCount(0), department(""), adminCode("ADM000") {}
    Admin(string uname, string pwd, ContactInfo ci, Address addr, string level, string code)
        : User(uname, pwd, ci, addr, "Admin"),
          adminLevel(level), approvedCount(0), rejectedCount(0),
          department("Moderation"), adminCode(code) {}

    Admin& operator=(const Admin& other) {
        if (this != &other) {
            username = other.username; passwordHash = other.passwordHash;
            contact = other.contact; address = other.address;
            userType = other.userType; isVerified = other.isVerified;
            adminLevel = other.adminLevel;
            approvedCount = other.approvedCount; rejectedCount = other.rejectedCount;
            department = other.department;
        }
        return *this;
    }

    string getAdminLevel()  const { return adminLevel; }
    string getAdminCode()   const { return adminCode; }
    int    getApprovedCount() const { return approvedCount; }
    int    getRejectedCount() const { return rejectedCount; }

    void approveListing(Listing& l) {
        l.setStatus("Approved"); approvedCount++;
        cout << "Admin " << username << " approved listing #" << l.getId() << endl;
    }
    void rejectListing(Listing& l, const string& reason) {
        l.setStatus("Rejected"); rejectedCount++;
        cout << "Admin " << username << " rejected listing #" << l.getId()
             << " | Reason: " << reason << endl;
    }
    void viewStats() const {
        cout << "Admin: " << username << " | Level: " << adminLevel << endl;
        cout << "Approved: " << approvedCount << " | Rejected: " << rejectedCount << endl;
    }

    // Admin can inspect Car's private fields directly (friend class benefit)
    void validateCarListing(const Car& c) const {
        cout << "Admin validating car: " << c.brand << " " << c.model << endl;
        // Directly accessing private Car fields (possible because Admin is friend of Car)
        cout << "  Doors: " << c.numDoors << " | Sunroof: " << (c.hasSunroof ? "Yes" : "No") << endl;
        cout << "  Body: " << c.bodyType << " | Transmission: " << c.transmission << endl;
    }

    // Polymorphism — overrides User::displayDetails()
    void displayDetails() const override {
        User::displayDetails();
        cout << "Level: " << adminLevel << " | Code: " << adminCode
             << " | Dept: " << department << endl;
        viewStats();
    }
    void displayProfile() const override { displayDetails(); }
};

// ============================================================
// CLASS 13: SearchFilter  (unchanged from A1 — utility class)
// ============================================================
class SearchFilter {
private:
    string brand;
    string model;
    double minPrice;
    double maxPrice;
    int    minYear;
    int    maxYear;
    int    maxMileage;
    string city;
    const int MAX_RESULTS = 50;

public:
    SearchFilter() : brand(""), model(""), minPrice(0), maxPrice(999999999),
                     minYear(2000), maxYear(2026), maxMileage(999999), city("") {}
    SearchFilter(string br, string mo, double lo, double hi, int yrLo, int yrHi)
        : brand(br), model(mo), minPrice(lo), maxPrice(hi),
          minYear(yrLo), maxYear(yrHi), maxMileage(999999), city("") {}

    void setBrand(string b)    { brand = b; }
    void setModel(string m)    { model = m; }
    void setPriceRange(double lo, double hi) { minPrice = lo; maxPrice = hi; }
    void setYearRange(int lo, int hi)        { minYear = lo; maxYear = hi; }
    void setMaxMileage(int m)  { maxMileage = m; }
    void setCity(string c)     { city = c; }

    bool matches(const Listing& l) const {
        const Vehicle& v = l.getVehicle();
        if (!brand.empty() && !v.matchesBrand(brand)) return false;
        if (!model.empty() && !v.matchesModel(model)) return false;
        if (!v.isPriceInRange(minPrice, maxPrice)) return false;
        if (!v.isYearInRange(minYear, maxYear)) return false;
        return true;
    }

    void display() const {
        cout << "Filter: Brand=" << brand << " Model=" << model
             << " Price=[" << minPrice << "-" << maxPrice << "]"
             << " Year=[" << minYear << "-" << maxYear << "]" << endl;
    }
    void resetFilter() {
        brand = ""; model = ""; minPrice = 0; maxPrice = 999999999;
        minYear = 2000; maxYear = 2026; maxMileage = 999999; city = "";
    }
    bool hasAnyFilter() const {
        return !brand.empty() || !model.empty() || minPrice > 0 || maxPrice < 999999999;
    }
};

// ============================================================
// CLASS 14: Marketplace  (main system class — unchanged from A1 mostly)
// ============================================================
class Marketplace {
private:
    Listing  listings[200];
    int      listingCount;
    Seller   sellers[100];
    int      sellerCount;
    Buyer    buyers[100];
    int      buyerCount;
    const string platformName;

    static int totalTransactions;

public:
    Marketplace() : listingCount(0), sellerCount(0), buyerCount(0),
                    platformName("PakWheels Clone") {}

    void addListing(const Listing& l) {
        if (listingCount < 200) { listings[listingCount++] = l; cout << "Listing added to marketplace." << endl; }
    }
    void deleteListing(int id) {
        for (int i = 0; i < listingCount; i++) {
            if (listings[i].getId() == id) {
                for (int j = i; j < listingCount - 1; j++) listings[j] = listings[j+1];
                listingCount--;
                cout << "Listing #" << id << " deleted." << endl;
                return;
            }
        }
        cout << "Listing not found." << endl;
    }
    void updateListingStatus(int id, const string& status) {
        for (int i = 0; i < listingCount; i++) {
            if (listings[i].getId() == id) {
                listings[i].setStatus(status);
                cout << "Listing #" << id << " updated to: " << status << endl;
                return;
            }
        }
    }
    void searchListings(const SearchFilter& filter) const {
        cout << "\n=== Search Results ===" << endl;
        int found = 0;
        for (int i = 0; i < listingCount; i++) {
            if (filter.matches(listings[i])) { listings[i].display(); found++; }
        }
        if (found == 0) cout << "No listings match your criteria." << endl;
        else cout << found << " listing(s) found." << endl;
    }
    void displayApprovedListings() const {
        cout << "\n=== Available Vehicles ===" << endl;
        for (int i = 0; i < listingCount; i++)
            if (listings[i].isApproved()) listings[i].display();
    }
    void registerSeller(const Seller& s) { if (sellerCount < 100) sellers[sellerCount++] = s; }
    void registerBuyer(const Buyer& b)   { if (buyerCount  < 100) buyers[buyerCount++]   = b; }

    static void recordTransaction() { totalTransactions++; }
    static int  getTotalTransactions() { return totalTransactions; }
    string getPlatformName() const { return platformName; }

    void displayStats() const {
        cout << "=== " << platformName << " Stats ===" << endl;
        cout << "Listings: " << listingCount << " | Sellers: " << sellerCount
             << " | Buyers: " << buyerCount << endl;
        cout << "Total Vehicles Listed: " << Vehicle::getTotalVehicles() << endl;
        cout << "Total Messages Sent: " << Message::getTotalMessages() << endl;
        cout << "Total Transactions: " << totalTransactions << endl;
    }
};

int Marketplace::totalTransactions = 0;
