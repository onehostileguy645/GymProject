#include "membership.h"
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_MEMBERSHIPS = 100;

void initMembershipFile(fstream& file) {
    file.clear();
    file.seekp(0);
    MembershipRecord empty;
    for (int i = 0; i < MAX_MEMBERSHIPS; i++)
        file.write(reinterpret_cast<char*>(&empty), sizeof(MembershipRecord));
}

void saveMembership(fstream& file, const Membership& m) {
    MembershipRecord rec = m.getRecord();
    file.clear();
    file.seekp((rec.membershipId - 1) * sizeof(MembershipRecord), ios::beg);
    file.write(reinterpret_cast<const char*>(&rec), sizeof(MembershipRecord));
}

bool loadMembership(fstream& file, int mid, Membership& out) {
    MembershipRecord rec;
    file.clear();
    file.seekg((mid - 1) * sizeof(MembershipRecord), ios::beg);
    file.read(reinterpret_cast<char*>(&rec), sizeof(MembershipRecord));
    if (rec.membershipId == 0) return false;
    out = Membership(rec);
    return true;
}

bool findMembershipByUser(fstream& file, int userId, Membership& out) {
    file.clear();
    file.seekg(0);
    MembershipRecord rec;
    while (file.read(reinterpret_cast<char*>(&rec), sizeof(MembershipRecord))) {
        if (rec.userId == userId) {
            out = Membership(rec);
            return true;
        }
    }
    return false;
}

void subscribeMenu(fstream& memberFile, int userId) {
    cout << "\n--- Subscribe to Membership ---" << endl;

    Membership existing;
    if (findMembershipByUser(memberFile, userId, existing)) {
        cout << "You already have a membership:" << endl;
        existing.display();
        return;
    }

    int mid;
    cout << "Enter a Membership ID (1-" << MAX_MEMBERSHIPS << "): ";
    cin  >> mid;
    while (mid < 1 || mid > MAX_MEMBERSHIPS) {
        cout << "Must be 1-" << MAX_MEMBERSHIPS << ". Try again: ";
        cin  >> mid;
    }

    Membership check;
    if (loadMembership(memberFile, mid, check)) {
        cout << "Membership ID #" << mid << " is already taken." << endl;
        return;
    }

    string type;
    cout << "Choose type (Basic $30/mo | Premium $50/mo | VIP $80/mo): ";
    cin  >> type;
    while (type != "Basic" && type != "Premium" && type != "VIP") {
        cout << "Invalid. Enter Basic, Premium, or VIP: ";
        cin  >> type;
    }

    int months;
    cout << "Duration in months (1-12): ";
    cin  >> months;
    while (months < 1 || months > 12) {
        cout << "Must be 1-12. Try again: ";
        cin  >> months;
    }

    Membership m(mid, userId);
    m.subscribe(type, months);
    saveMembership(memberFile, m);

    cout << "\nMembership activated!" << endl;
    m.display();
}

void viewMembership(fstream& memberFile, int userId) {
    Membership m;
    if (findMembershipByUser(memberFile, userId, m)) {
        m.display();
    } else {
        cout << "No membership found for User ID " << userId << "." << endl;
    }
}

void cancelMembership(fstream& memberFile, int userId) {
    Membership m;
    if (!findMembershipByUser(memberFile, userId, m)) {
        cout << "No membership found for User ID " << userId << "." << endl;
        return;
    }
    m.cancelMembership();
    saveMembership(memberFile, m);
    cout << "Membership cancelled." << endl;
}

void listAllMemberships(fstream& memberFile, fstream& userFile) {
    memberFile.clear();
    memberFile.seekg(0);
    MembershipRecord rec;

    cout << "\n--- All Memberships ---" << endl;
    while (memberFile.read(reinterpret_cast<char*>(&rec), sizeof(MembershipRecord))) {
        if (rec.membershipId != 0) {
            UserRecord user;
            userFile.clear();
            userFile.seekg((rec.userId - 1) * sizeof(UserRecord), ios::beg);
            userFile.read(reinterpret_cast<char*>(&user), sizeof(UserRecord));

            if (string(user.userType) == "Admin") continue;

            Membership m(rec);
            m.display();
            cout << "-------------------" << endl;
        }
    }
}