#include "progress.h"
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_PROGRESS = 500;

void ProgressFile(fstream& file) {
    file.clear();
    file.seekp(0);
    ProgressRecord empty;
    for (int i = 0; i < MAX_PROGRESS; i++)
        file.write(reinterpret_cast<char*>(&empty), sizeof(ProgressRecord));
}

void saveProgress(fstream& file, const Progress& p) {
    ProgressRecord rec = p.getRecord();
    file.clear();
    file.seekp((rec.progressId - 1) * sizeof(ProgressRecord), ios::beg);
    file.write(reinterpret_cast<const char*>(&rec), sizeof(ProgressRecord));
}

bool loadProgress(fstream& file, int pid, Progress& out) {
    ProgressRecord rec;
    file.clear();
    file.seekg((pid - 1) * sizeof(ProgressRecord), ios::beg);
    file.read(reinterpret_cast<char*>(&rec), sizeof(ProgressRecord));
    if (rec.progressId == 0) return false;
    out = Progress(rec);
    return true;
}

static int findFreeProgressSlot(fstream& file) {
    ProgressRecord rec;
    for (int i = 0; i < MAX_PROGRESS; i++) {
        file.clear();
        file.seekg(i * sizeof(ProgressRecord), ios::beg);
        file.read(reinterpret_cast<char*>(&rec), sizeof(ProgressRecord));
        if (rec.progressId == 0) return i + 1; // IDs start at 1
    }
    throw ProgressException("No free progress slots available.");
}

void addProgressEntry(fstream& progressFile, fstream& userFile, int userId) {
    UserRecord user;
    userFile.clear();
    userFile.seekg((userId - 1) * sizeof(UserRecord), ios::beg);
    userFile.read(reinterpret_cast<char*>(&user), sizeof(UserRecord));

    if (user.userId == 0) {
        cout << "User not found." << endl;
        return;
    }
    if (string(user.userType) == "Admin") {
        cout << "Admins do not have progress entries." << endl;
        return;
    }

    int pid;
    try {
        pid = findFreeProgressSlot(progressFile);
    } catch (ProgressException& e) {
        cout << "Error: " << e.getMessage() << endl;
        return;
    }

    double weight, calories, chest, waist, hips, biceps, thighs;

    cout << "\n--- Add Progress Entry ---" << endl;
    cout << "Weight (kg): ";
    cin  >> weight;
    while (weight <= 0) {
        cout << "Must be positive. Try again: ";
        cin  >> weight;
    }

    cout << "Daily Calories (kcal): ";
    cin  >> calories;
    while (calories < 0) {
        cout << "Must be non-negative. Try again: ";
        cin  >> calories;
    }

    cout << "\n-- Body Measurements (cm) --" << endl;
    cout << "Chest  : "; cin >> chest;
    cout << "Waist  : "; cin >> waist;
    cout << "Hips   : "; cin >> hips;
    cout << "Biceps : "; cin >> biceps;
    cout << "Thighs : "; cin >> thighs;

    Progress p(pid, userId, weight, calories, chest, waist, hips, biceps, thighs);
    saveProgress(progressFile, p);

    cout << "\nProgress entry saved!" << endl;
    p.display();
}

void viewUserProgress(fstream& progressFile, int userId) {
    progressFile.clear();
    progressFile.seekg(0);
    ProgressRecord rec;

    bool found = false;
    cout << "\n--- Progress History for User #" << userId << " ---" << endl;

    while (progressFile.read(reinterpret_cast<char*>(&rec), sizeof(ProgressRecord))) {
        if (rec.progressId != 0 && rec.userId == userId) {
            Progress p(rec);
            p.display();
            cout << "-------------------" << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No progress entries found." << endl;
}

void compareFirstAndLast(fstream& progressFile, int userId) {
    progressFile.clear();
    progressFile.seekg(0);
    ProgressRecord rec;

    ProgressRecord first, last;
    bool foundFirst = false;

    while (progressFile.read(reinterpret_cast<char*>(&rec), sizeof(ProgressRecord))) {
        if (rec.progressId != 0 && rec.userId == userId) {
            if (!foundFirst) {
                first      = rec;
                foundFirst = true;
            }
            last = rec;
        }
    }

    if (!foundFirst) {
        cout << "No progress entries found for User #" << userId << "." << endl;
        return;
    }

    Progress p1(first), p2(last);
    Progress::compareProgress(p1, p2);
    cout << "Total weight change: " << Progress::calculateWeightChange(p1, p2) << " kg" << endl;
}

void listAllProgress(fstream& progressFile, fstream& userFile) {
    progressFile.clear();
    progressFile.seekg(0);
    ProgressRecord rec;

    cout << "\n--- All Progress Entries ---" << endl;
    while (progressFile.read(reinterpret_cast<char*>(&rec), sizeof(ProgressRecord))) {
        if (rec.progressId != 0) {
            UserRecord user;
            userFile.clear();
            userFile.seekg((rec.userId - 1) * sizeof(UserRecord), ios::beg);
            userFile.read(reinterpret_cast<char*>(&user), sizeof(UserRecord));

            if (string(user.userType) == "Admin") continue;

            Progress p(rec);
            p.display();
            cout << "-------------------" << endl;
        }
    }
}

void deleteProgressEntry(fstream& progressFile, int progressId) {
    ProgressRecord empty;
    progressFile.clear();
    progressFile.seekp((progressId - 1) * sizeof(ProgressRecord), ios::beg);
    progressFile.write(reinterpret_cast<char*>(&empty), sizeof(ProgressRecord));
    cout << "Progress entry #" << progressId << " deleted." << endl;
}