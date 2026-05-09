#include <iostream>
#include <string>
#include <vector>
#include "user.h"

using namespace std;

class Membership {
    private:
        string membershipId;
        string userId;
        string membershipType; // "Basic", "Premium", "VIP"
        double price;
        bool isActive;
        int daysRemaining;
    public:
    Membership(string t, string sid, double p, string s, string e) : membershipType(t), userId(sid), price(p), isActive(false), daysRemaining(0) {}
    
    void setMembershipId(string id) {
        membershipId = id;
    }
    string getMembershipId() {
        return membershipId;
    }

    string getUserId() {
        return userId;
    }

    void setMembershipType(string type) {
        if (type == "Basic" || type == "Premium" || type == "VIP") {
            membershipType = type;
        } else {
            cout << "Invalid membership type. Setting to Basic by default." << endl;
            membershipType = "Basic";
        }
    }

    string getType() {
        return membershipType;
    }

    double getPrice() {
        return price;
    }

    void subscribe(string uid, string type, int durationMonths){
        userId = uid;
        setMembershipType(type);
        price = calculatePrice(type, durationMonths);
        isActive = true;
        // Set startDate and endDate based on current date and duration
        daysRemaining = durationMonth*30;
    };
    bool checkValidity() const{
        if isActive{
            return true;
        }
        else return false;
    };

    double calculatePrice(string type, int durationMonths) {
        double basePrice = 0.0;
        if (type == "Basic") {
            basePrice = 30.0;
        } else if (type == "Premium") {
            basePrice = 50.0;
        } else if (type == "VIP") {
            basePrice = 80.0;
        }

        return basePrice * durationMonths;
    }
    void display(){
        cout << "Membership Type: " << membershipType << endl;
        cout << "Price: $" << price << endl;
        cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
        cout << "Days Remaining: " << daysRemaining << endl;
    }

    

}