#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "user.h"

using namespace std;

struct ProgressRecord {
    int    progressId;
    int    userId;
    double weight;
    double dailyCalories;
    double chest;
    double waist;
    double hips;
    double biceps;
    double thighs;

    ProgressRecord() {
        progressId    = 0;
        userId        = 0;
        weight        = 0.0;
        dailyCalories = 0.0;
        chest         = 0.0;
        waist         = 0.0;
        hips          = 0.0;
        biceps        = 0.0;
        thighs        = 0.0;
    }

    ProgressRecord(int pid, int uid, double w, double cal,
                   double ch, double wa, double hi, double bi, double th) {
        progressId    = pid;
        userId        = uid;
        weight        = w;
        dailyCalories = cal;
        chest         = ch;
        waist         = wa;
        hips          = hi;
        biceps        = bi;
        thighs        = th;
    }
};

class BodyMeasurements {
private:
    double chest;
    double waist;
    double hips;
    double biceps;
    double thighs;

public:
    BodyMeasurements() : chest(0), waist(0), hips(0), biceps(0), thighs(0) {}

    BodyMeasurements(double c, double w, double h, double b, double t)
        : chest(c), waist(w), hips(h), biceps(b), thighs(t) {}

    BodyMeasurements(const ProgressRecord& r)
        : chest(r.chest), waist(r.waist), hips(r.hips),
          biceps(r.biceps), thighs(r.thighs) {}

    double getChest()  const { return chest; }
    double getWaist()  const { return waist; }
    double getHips()   const { return hips; }
    double getBiceps() const { return biceps; }
    double getThighs() const { return thighs; }

    void setChest(double c)  { 
        if (c >= 0) chest  = c; 
        else cout << "Invalid chest value."  << endl; }
    void setWaist(double w)  { 
        if (w >= 0) waist  = w; 
        else cout << "Invalid waist value."  << endl; }
    void setHips(double h)   { 
        if (h >= 0) hips   = h; 
        else cout << "Invalid hips value."   << endl; }
    void setBiceps(double b) { 
        if (b >= 0) biceps = b; 
        else cout << "Invalid biceps value." << endl; }
    void setThighs(double t) { 
        if (t >= 0) thighs = t; 
        else cout << "Invalid thighs value." << endl; }

    bool operator==(const BodyMeasurements& other) const {
        return chest  == other.chest  && waist == other.waist &&
               hips   == other.hips   && biceps== other.biceps &&
               thighs == other.thighs;
    }

    BodyMeasurements operator-(const BodyMeasurements& other) const {
        return BodyMeasurements(
            chest  - other.chest,
            waist  - other.waist,
            hips   - other.hips,
            biceps - other.biceps,
            thighs - other.thighs
        );
    }

    void display() const {
        cout << "  Chest  : " << chest  << " cm" << endl;
        cout << "  Waist  : " << waist  << " cm" << endl;
        cout << "  Hips   : " << hips   << " cm" << endl;
        cout << "  Biceps : " << biceps << " cm" << endl;
        cout << "  Thighs : " << thighs << " cm" << endl;
    }
};

class ProgressException {
private:
    string message;
public:
    ProgressException(const string& msg) : message(msg) {}
    string getMessage() const { return message; }
};

class Progress {
protected:
    ProgressRecord record;
    BodyMeasurements measurements;

public:
    Progress() = default;

    Progress(const ProgressRecord& r)
        : record(r), measurements(r) {}

    Progress(int pid, int uid, double w, double cal,
             double ch, double wa, double hi, double bi, double th)
        : record(pid, uid, w, cal, ch, wa, hi, bi, th),
          measurements(ch, wa, hi, bi, th) {}

    int    getProgressId()    const { return record.progressId; }
    int    getUserId()        const { return record.userId; }
    double getWeight()        const { return record.weight; }
    double getDailyCalories() const { return record.dailyCalories; }
    const  BodyMeasurements& getMeasurements() const { return measurements; }

    void setProgressId(int id)       { record.progressId = id; }
    void setUserId(int uid)          { record.userId = uid; }
    void setWeight(double w)         { 
        if (w > 0) record.weight = w; 
        else cout << "Invalid weight." << endl; }
    void setDailyCalories(double c)  { 
        if (c >= 0) record.dailyCalories = c; 
        else cout << "Invalid calories." << endl; }
    void setMeasurements(const BodyMeasurements& m) { measurements = m; }

    bool operator<(const Progress& other) const { return record.weight < other.record.weight; }
    bool operator>(const Progress& other) const { return record.weight > other.record.weight; }

    virtual void display() const {
        cout << "Progress ID    : " << record.progressId    << endl;
        cout << "User ID        : " << record.userId        << endl;
        cout << "Weight         : " << record.weight        << " kg" << endl;
        cout << "Daily Calories : " << record.dailyCalories << " kcal" << endl;
        cout << "Measurements   :" << endl;
        measurements.display();
    }

    static double calculateWeightChange(const Progress& first, const Progress& last) {
        return last.record.weight - first.record.weight;
    }

    static void compareProgress(const Progress& p1, const Progress& p2) {
        cout << "\n--- Progress Comparison ---" << endl;
        cout << "Weight change     : " << p2.record.weight - p1.record.weight << " kg" << endl;
        cout << "Calories change   : " << p2.record.dailyCalories - p1.record.dailyCalories << " kcal" << endl;
        cout << "Measurement changes:" << endl;
        BodyMeasurements diff = p2.measurements - p1.measurements;
        diff.display();
    }

    const ProgressRecord& getRecord() const { return record; }

    virtual ~Progress() {}
};


class DetailedProgress : public Progress {
private:
    char note[100];

public:
    DetailedProgress() = default;

    DetailedProgress(int pid, int uid, double w, double cal,
                     double ch, double wa, double hi, double bi, double th,
                     const string& n)
        : Progress(pid, uid, w, cal, ch, wa, hi, bi, th)
    {
        int len = min((int)n.size(), 99);
        for (int i = 0; i < len; i++) note[i] = n[i];
        note[len] = '\0';
    }

    string getNote() const { return note; }

    void display() const override {
        Progress::display();
        cout << "Note           : " << note << endl;
    }
};