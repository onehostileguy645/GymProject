#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Membership {
    string type;
    double price;
    vector<string> features;

    public:
    Membership(string t, double p, vector<string> f) : type(t), price(p), features(f) {}
    
    string getType() {
        return type;
    }

    double getPrice() {
        return price;
    }

    void MembershipManager()

    void display(){
        cout << "Membership Type: " << type << endl;
        cout << "Price: $" << price << endl;
        cout << "Features: " << endl;
        for (const auto& feature : features) {
            cout << "- " << feature << endl;
        }
    }

}