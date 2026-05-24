#include <iostream>
#include <fstream>
#include "membership.h"
#include "user.h"
using namespace std;

const int MAX_MEMBERSHIPS = 100;

// File operations

void MembershipFile(fstream& file) {
    file.clear();
    file.seekp(0);
    MembershipRecord empty;
    for (int i = 0; i < MAX_MEMBERSHIPS; i++) file.write(reinterpret_cast<char*>(&empty), sizeof(MembershipRecord));
}

void saveMembership(fstream& file, const Membership& m) {
    int id =m.getMembershipId();
    file.clear();
    file.seekp((id - 1) * sizeof(Membership), ios::beg);
    file.write(reinterpret_cast<const char*>(&m), sizeof(Membership));
    file.flush();
}

bool loadMembership(fstream& file, int mid, Membership& out) {
    file.clear();
    file.seekg((mid - 1)*sizeof(Membership), ios::beg);
    file.read(reinterpret_cast<char*>(&out), sizeof(Membership));
    if (out.getMembershipId()== 0) return false;
    return true;
}

bool findMembershipByUser(fstream& file, int userId, Membership& out) {
    file.clear();
    file.seekg(0);
    Membership temp;
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Membership))) {
        if (temp.getMembershipId()!= 0 &&temp.getUserId() ==userId) {
            out = temp;
            return true;
        }
    }
    return false;
}

// Menu~

void subscribeMenu(fstream& memberFile, int userId) {
    cout << "\n--- Subscribe to Membership ---\n";
    Membership existing;
    if (findMembershipByUser(memberFile, userId, existing)) {
        cout << "You already have an active membership:\n";
        existing.display();
        return;
    }

    int mid;
    cout <<"Enter Membership ID (1-" <<MAX_MEMBERSHIPS << "): ";
    cin>> mid;
    while (mid < 1 || mid > MAX_MEMBERSHIPS) {
        cout << "Must be between 1 and " << MAX_MEMBERSHIPS << ". Try again: ";
        cin >> mid;
    }
    Membership check;
    if (loadMembership(memberFile, mid, check)) {
        cout << "Membership ID #" << mid << " is already taken.\n";
        return;
    }

    string type;

    //Listings to choose from
    //Maybe add connection with recommedation?
    cout << "Choose type:\n"
         << "  Basic - $30/mo \n 2 times per week gym access, group classes, locker rooms.\n"
         << "  \nPremium - $50/mo \n 3 times per week gym access, pool, sauna, workout recommendations.\n"
         << "  \nVIP - $80/mo \n Unlimited access + personalized plans & nutrition.\n"
         << "Enter Basic, Premium, or VIP: ";
    cin  >> type;
    while (type != "Basic" && type != "Premium" && type != "VIP") {
        cout << "Invalid. Enter Basic, Premium, or VIP: ";
        cin >> type;
    }

    int months;
    cout << "Choose duration in months (1-12): ";
    cin  >> months;
    while (months < 1 ||months > 12) {
        cout << "Must be between 1 and 12. Try again: ";
        cin>> months;
    }

    Membership m(mid, userId);
    m.subscribe(type, months);
    saveMembership(memberFile, m);
    cout << "\nMembership activated!\n";
    m.display();
}

void viewMembership(fstream& memberFile,int userId) {
    Membership m;
    if (findMembershipByUser(memberFile, userId, m))
        m.display();
    else
        cout << "No membership found for User ID " <<userId <<".\n";
}
void cancelMembership(fstream& memberFile, int userId) {
    Membership m;
    if (!findMembershipByUser(memberFile, userId, m)) {
        cout << "No membership found for User ID " << userId << ".\n";
        return;
    }
    m.cancelMembership();
    saveMembership(memberFile, m);
    cout << "Membership cancelled.\n";
}

void showAllMemberships(fstream& memberFile, fstream& userFile) {
    memberFile.clear();
    memberFile.seekg(0);

    cout << "\n--------- All Memberships -------\n";
    Membership m;
    while (memberFile.read(reinterpret_cast<char*>(&m), sizeof(Membership))) {
        if (m.getMembershipId()== 0) continue;

        UserRecord user;
        userFile.clear();
        userFile.seekg((m.getUserId()- 1)*sizeof(UserRecord), ios::beg);
        userFile.read(reinterpret_cast<char*>(&user), sizeof(UserRecord));
        if (string(user.userType) == "Admin") continue;

        m.display();
            cout << "--------------\n";
    }
}


void membershipMenu(fstream& memberFile, fstream& userFile, int userId) {
    fstream memberFile("memberships.dat", ios::in | ios::out | ios::binary);
    if (!memberFile) {
        cerr << "Error opening memberships.dat" << endl;
        exit(1);}

    MembershipFile(memberFile);

    int choice, userId;
    cout << "Enter your User ID: ";
    cin  >> userId;
    while (true) {
        cout << "\n--- Membership Menu ---\n"
             << "1. Subscribe to Membership\n"
             << "2. View My Membership\n"
             << "3. Cancel Membership\n"
             << "4. View All Memberships (Admin)\n"
             << "5. Exit\n"
             << "Choose an option: ";
        cin  >> choice;

        switch (choice) {
            case 1: subscribeMenu(memberFile, userId); break;
            case 2: viewMembership(memberFile, userId); break;
            case 3: cancelMembership(memberFile, userId); break;
            case 4: showAllMemberships(memberFile, memberFile); break; // Using memberFile for both since we don't have userFile here
            case 5: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice. Try again.\n";
        }
    }

    memberFile.close();
    return 0;
}