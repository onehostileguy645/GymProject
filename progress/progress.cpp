#include "progress.h"
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_PROGRESS = 500;

// File stuff

void ProgressFile(fstream& file) {
    file.clear();
    file.seekp(0);
    Progress empty;
    for (int i = 0; i < MAX_PROGRESS; i++)
        file.write(reinterpret_cast<const char*>(&empty), sizeof(Progress));
}

void saveProgress(fstream& file, const Progress& p) {
    file.clear();
    file.seekp((p.getProgressId() - 1) * sizeof(Progress), ios::beg);
    file.write(reinterpret_cast<const char*>(&p), sizeof(Progress));
    file.flush();
}

bool loadProgress(fstream& file, int pid, Progress& out) {
    file.clear();
    file.seekg((pid - 1) * sizeof(Progress), ios::beg);
    file.read(reinterpret_cast<char*>(&out), sizeof(Progress));
    if (out.getProgressId() == 0) return false;
    return true;
}

static int findFreeProgressSlot(fstream& file) {
    Progress temp;
    for (int i = 0; i < MAX_PROGRESS; i++) {
        file.clear();
        file.seekg(i * sizeof(Progress), ios::beg);
        file.read(reinterpret_cast<char*>(&temp), sizeof(Progress));
        if (temp.getProgressId() == 0) return i + 1;
    }
    throw ProgressException("No free progress slots available.");
}

// -Menu Functions

void addProgressEntry(fstream& progressFile, fstream& userFile, int userId) {
    UserRecord user;
    userFile.clear();
    userFile.seekg((userId - 1) * sizeof(UserRecord), ios::beg);
    userFile.read(reinterpret_cast<char*>(&user), sizeof(UserRecord));

    if (user.userId == 0) {
        cout << "User not found.\n";
        return;
    }
    if (string(user.userType) == "Admin") {
        cout << "Admins do not have progress entries.\n";
        return;
    }

    int pid;
    try {
        pid = findFreeProgressSlot(progressFile);
    } catch (ProgressException& e) {
        cout << "Error: " << e.getMessage() << "\n";
        return;
    }

    double weight, chest, waist, hips, biceps, thighs;

    cout << "\n--- Add Progress Entry ---\n";
    cout << "Weight (kg): ";
    cin  >> weight;
    while (weight <= 0) {
        cout << "Must be positive. Try again: ";
        cin  >> weight;
    }

    cout << "\n-- Body Measurements (cm) --\n";
    cout << "Chest  : "; cin >> chest;
    cout << "Waist  : "; cin >> waist;
    cout << "Hips   : "; cin >> hips;
    cout << "Biceps : "; cin >> biceps;
    cout << "Thighs : "; cin >> thighs;

    Progress p(pid, userId, weight, chest, waist, hips, biceps, thighs);
    saveProgress(progressFile, p);

    cout << "\nProgress entry saved!\n";
    p.display();
}

void viewUserProgress(fstream& progressFile, int userId) {
    progressFile.clear();
    progressFile.seekg(0);

    bool found = false;
    cout << "\n--- Progress History for User #" << userId << " ---\n";

    Progress p;
    while (progressFile.read(reinterpret_cast<char*>(&p), sizeof(Progress))) {
        if (p.getProgressId() != 0 && p.getUserId() == userId) {
            p.display();
            cout << "-------------------\n";
            found = true;
        }
    }

    if (!found)
        cout << "No progress entries found.\n";
}

void compareFirstAndLast(fstream& progressFile, int userId) {
    progressFile.clear();
    progressFile.seekg(0);

    Progress first, last;
    bool foundFirst = false;

    Progress temp;
    while (progressFile.read(reinterpret_cast<char*>(&temp), sizeof(Progress))) {
        if (temp.getProgressId() != 0 && temp.getUserId() == userId) {
            if (!foundFirst) {
                first = temp;
                foundFirst = true;
            }
            last = temp;
        }
    }

    if (!foundFirst) {
        cout << "No progress entries found for User #" << userId << ".\n";
        return;
    }

    Progress::compareProgress(first, last);
    cout << "Total weight change: " << Progress::calculateWeightChange(first, last) << " kg\n";
}

void listAllProgress(fstream& progressFile, fstream& userFile) {
    progressFile.clear();
    progressFile.seekg(0);

    cout << "\n--- All Progress Entries ---\n";
    Progress p;
    while (progressFile.read(reinterpret_cast<char*>(&p), sizeof(Progress))) {
        if (p.getProgressId() == 0) continue;
        UserRecord user;
        userFile.clear();
        userFile.seekg((p.getUserId() - 1) * sizeof(UserRecord), ios::beg);
        userFile.read(reinterpret_cast<char*>(&user), sizeof(UserRecord));

        if (string(user.userType) == "Admin") continue;

        p.display();
        cout << "-------------------\n";}
}

int main() {
    fstream progressFile("progress.dat", ios::in | ios::out | ios::binary);
    if (!progressFile) {
        cout<< "Could not open progress file. Creating new one.\n";
        progressFile.open("progress.dat", ios::out | ios::binary);
        progressFile.close();
        progressFile.open("progress.dat", ios::in | ios::out | ios::binary);
        ProgressFile(progressFile);
    }

    fstream userFile("users.dat", ios::in | ios::out | ios::binary);
    if (!userFile) {
        cout << "Could not open user file. Exiting.\n";
        return 1;
    }
    
    int choice, userId;
    cout << "Enter your User ID: ";
    cin  >> userId;
    while (true) {
        cout << "\n--- Progress Menu ---\n"
             << "1. Add Progress Entry\n"
             << "2. View My Progress History\n"
             << "3. Compare First and Last Entry\n"
             << "4. List All Progress Entries\n"
             << "5. Exit\n"
             << "Choose an option: ";
        cin  >> choice;

        switch (choice) {
            case 1: addProgressEntry(progressFile, userFile, userId); break;
            case 2: viewUserProgress(progressFile, userId); break;
            case 3: compareFirstAndLast(progressFile, userId); break;
            case 4: listAllProgress(progressFile, userFile); break;
            case 5: cout << "Goodbye!\n"; progressFile.close(); userFile.close(); return 0;
            default: cout << "Invalid choice. Try again.\n";
}
    }

    progressFile.close();
    userFile.close();
    return 0;
}
