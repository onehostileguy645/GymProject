#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "user.h"

using namespace std;

struct MembershipRecord {
    int    membershipId;
    int    userId;
    char   membershipType[10]; // "Basic", "Premium", "VIP"
    double price;
    bool   isActive;
    int    daysRemaining;

    MembershipRecord() {
        membershipId      = 0;
        userId            = 0;
        membershipType[0] = '\0';
        price             = 0.0;
        isActive          = false;
        daysRemaining     = 0;
    }

    MembershipRecord(int mid, int uid, string type, double p, bool active, int days) {
        membershipId  = mid;
        userId        = uid;
        price         = p;
        isActive      = active;
        daysRemaining = days;

        int len = min((int)type.size(), 9);
        for (int i = 0; i < len; i++) membershipType[i] = type[i];
        membershipType[len] = '\0';
    }
};

class Membership {
private:
    MembershipRecord record;

public:
    Membership() = default;

    Membership(const MembershipRecord& r) : record(r) {}

    Membership(int mid, int uid) {
        record.membershipId = mid;
        record.userId       = uid;
    }

    // --- Getters ---
    int    getMembershipId()   const { return record.membershipId; }
    int    getUserId()         const { return record.userId; }
    string getMembershipType() const { return record.membershipType; }
    double getPrice()          const { return record.price; }
    bool   getIsActive()       const { return record.isActive; }
    int    getDaysRemaining()  const { return record.daysRemaining; }

    // --- Setters ---
    void setMembershipId(int id) { record.membershipId = id; }
    void setUserId(int uid)      { record.userId = uid; }

    void setMembershipType(const string& type) {
        if (type == "Basic" || type == "Premium" || type == "VIP") {
            int len = min((int)type.size(), 9);
            for (int i = 0; i < len; i++) record.membershipType[i] = type[i];
            record.membershipType[len] = '\0';
        } else {
            cout << "Invalid type. Defaulting to Basic." << endl;
            setMembershipType("Basic");
        }
    }

    // --- Core logic ---
    static double calculatePrice(const string& type, int durationMonths) {
        double basePrice = 0.0;
        if      (type == "Basic")   basePrice = 30.0;
        else if (type == "Premium") basePrice = 50.0;
        else if (type == "VIP")     basePrice = 80.0;
        else {
            cout << "Unknown type, using Basic price." << endl;
            basePrice = 30.0;
        }
        return basePrice * durationMonths;
    }

    void subscribe(const string& type, int durationMonths) {
        setMembershipType(type);
        record.price         = calculatePrice(type, durationMonths);
        record.isActive      = true;
        record.daysRemaining = durationMonths * 30;
    }

    void decrementDay() {
        if (record.isActive && record.daysRemaining > 0) {
            record.daysRemaining--;
            if (record.daysRemaining == 0) {
                record.isActive = false;
                cout << "Your membership has expired." << endl;
            }
        }
    }

    bool checkValidity() const {
        return record.isActive && record.daysRemaining > 0;
    }

    void cancelMembership() {
        record.isActive      = false;
        record.daysRemaining = 0;
    }

    void display() const {
        cout << "Membership ID  : " << record.membershipId   << endl;
        cout << "User ID        : " << record.userId         << endl;
        cout << "Type           : " << record.membershipType << endl;
        cout << "Price          : $" << record.price         << endl;
        cout << "Status         : " << (record.isActive ? "Active" : "Inactive") << endl;
        cout << "Days Remaining : " << record.daysRemaining  << endl;
    }

    const MembershipRecord& getRecord() const { return record; }
};