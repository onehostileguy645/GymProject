#pragma once
#include <iostream>
#include <string>
#include "user.h"

using namespace std;

class MembershipRecord {
protected:
    int membershipId;
    int userId;
    char membershipType[10]; // "Basic", "Premium", "VIP"
    double price;
    bool isActive;
    int daysRemaining;

public:
    MembershipRecord(): membershipId(0), userId(0), price(0.0),isActive(false), daysRemaining(0)
    {
        membershipType[0] = '\0';
    }

    MembershipRecord(int mid, int uid, const string& type, double p, bool active, int days): membershipId(mid), userId(uid), price(p),isActive(active), daysRemaining(days)
    {
        int len = min((int)type.size(), 9);
        for (int i = 0; i < len; i++) membershipType[i] = type[i];
        membershipType[len] = '\0';
    }
};

class Membership : public MembershipRecord {
private:
    void setMembershipTypeInternal(const string& type) {
        int len = min((int)type.size(), 9);
        for (int i = 0; i < len; i++) membershipType[i] = type[i];
        membershipType[len] = '\0';
    }

public:
    Membership() = default;
    explicit Membership(const MembershipRecord& r) : MembershipRecord(r) {}

    Membership(int mid, int uid) {
        membershipId = mid;
        userId = uid;
    }

    // --- Getters ---
    int getMembershipId() const { 
        return membershipId; }
    int getUserId() const { 
        return userId; }
    string getMembershipType() const { 
        return membershipType; }
    double getPrice() const { 
        return price; }
    bool getIsActive() const { 
        return isActive; }
    int getDaysRemaining() const { 
        return daysRemaining; }

    // --- Setters ---
    void setMembershipId(int id) { membershipId = id; }
    void setUserId(int uid) { userId = uid; }

    void setMembershipType(const string& type) {
        if (type == "Basic" || type == "Premium" || type == "VIP") {
            setMembershipTypeInternal(type);
        } else {
            cout << "Invalid type. Defaulting to Basic." << endl;
            setMembershipTypeInternal("Basic");
        }
    }

    static double calculatePrice(const string& type, int durationMonths) {
        double basePrice = 0.0;

        if (type == "Basic") basePrice = 30.0;
        else if (type == "Premium") basePrice = 50.0;
        else if (type == "VIP") basePrice = 80.0;
        else {
            cout << "Unknown membership type. Using Basic price." << endl;
            basePrice = 30.0;
        }

        return basePrice * durationMonths;
    }

    void subscribe(const string& type, int durationMonths) {
        setMembershipType(type);
        price = calculatePrice(type, durationMonths);
        isActive = true;
        daysRemaining = durationMonths * 30;
    }

    void countdown() {
        if (!isActive || daysRemaining <= 0) return;

        daysRemaining--;

        if (daysRemaining == 0) {
            isActive = false;
            cout << "Your membership has expired." << endl;
        }
    }

    bool checkValidity() const {
        if (isActive && daysRemaining > 0) {
            cout << "Your membership is valid for "
                 << daysRemaining << " more days." << endl;
            return true;
        }
        return false;
    }
//in advance:
    void cancelMembership() {
        isActive = false;
        daysRemaining = 0;
    }

    void display() const {
        cout << "Membership ID: " << membershipId << "\n"
             << "User ID: " << userId << "\n"
             << "Type: " << membershipType << "\n"
             << "Price: $" << price << "\n"
             << "Status: " << (isActive ? "Active" : "Inactive") << "\n"
             << "Days Remaining: " << daysRemaining << "\n";
    }
};