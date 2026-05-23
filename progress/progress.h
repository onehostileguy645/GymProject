#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "user.h"

using namespace std;

class Measurements {
    double chest, waist, hips, biceps, thighs;

public:
    measurements() : chest(0), waist(0), hips(0), biceps(0), thighs(0) {}

    measurements(double c, double w, double h, double b, double t)
        : chest(c), waist(w), hips(h), biceps(b), thighs(t) {}

    // Getters
    double getChest() const { 
        return chest; }
    double getWaist() const { 
        return waist; }
    double getHips() const { 
        return hips; }
    double getBiceps() const { 
        return biceps; }
    double getThighs() const { 
        return thighs; }

    // Setters
    void setChest(double c)  { 
        if (c >= 0) chest  = c; 
        else cout << "Invalid chest value.\n"; }
    void setWaist(double w)  { 
        if (w >= 0) waist  = w; 
        else cout << "Invalid waist value.\n"; }
    void setHips(double h)   { 
        if (h >= 0) hips   = h; 
        else cout << "Invalid hips value.\n"; }
    void setBiceps(double b) { 
        if (b >= 0) biceps = b; 
        else cout << "Invalid biceps value.\n"; }
    void setThighs(double t) { 
        if (t >= 0) thighs = t; 
        else cout << "Invalid thighs value.\n"; }
    
        //overloading and etc
        bool operator==(const Measurements& other) const {
        return chest == other.chest &&
               waist == other.waist &&
               hips == other.hips &&
               biceps == other.biceps &&
               thighs == other.thighs;}
        Measurements operator-(const Measurements& other) const {
        return Measurements(chest - other.chest,
                            waist - other.waist,
                            hips - other.hips,
                            biceps - other.biceps,
                            thighs - other.thighs);
        }
        void display() const {
        cout << "Chest: " << chest << " cm\n"
             << "Waist: " << waist << " cm\n"
             << "Hips: " << hips << " cm\n"
             << "Biceps: " << biceps << " cm\n"
             << "Thighs: " << thighs << " cm\n";}};

class Progress {
    int progressId, userId;
    double weight, chest, waist, hips, biceps, thighs;
    Measurements bMeasurements;
public:
    Progress() : progressId(0), userId(0), weight(0), chest(0), waist(0), hips(0), biceps(0), thighs(0), bMeasurements() {}

    Progress(int pid, int uid, double w, double c, double wa, double h, double b, double t, Measurements bm): progressId(pid), userId(uid), weight(w), chest(c), waist(wa), hips(h), biceps(b), thighs(t), bMeasurements(bm) {    }

    // Getters
    int getProgressId() const { 
        return progressId; }
    int getUserId()     const { 
        return userId; }
    double getWeight()  const { 
        return weight; }
    Measurements getMeasurements() const { 
        return bMeasurements; }

    // Setters
    void setProgressId(int pid) { progressId = pid; }
    void setUserId(int uid) { userId = uid; }
    void setWeight(double w)     { 
        if (w >= 0) weight = w; 
        else cout << "Invalid weight value.\n"; }
    void setMeasurements(const Measurements& m) { bMeasurements = m; }

    bool operator<(const Progress& other) const {
        return weight < other.weight;
    }
    bool operator>(const Progress& other) const {
        return weight > other.weight;
    }

    static double calculateWeightChange(const Progress& first, const Progress& last) {
        return last.weight - first.weight;
    }

    static void compareProgress(const Progress& first, const Progress& last) {
        cout << "First Entry:\n";
        first.display();
        cout << "\nLast Entry:\n";
        last.display();

        if (first < last) {
            cout << "\nYour weight has increased by " << calculateWeightChange(first, last) << " kg.\n";
        } else if (first > last) {
            cout << "\nYour weight has decreased by " << calculateWeightChange(last, first) << " kg.\n";
        } else {
            cout << "\nYour weight has remained the same.\n";
        }}
    void display() const {
        cout << "Progress ID: " << progressId << "\n"
             << "User ID: " << userId << "\n"
             << "Weight: " << weight << " kg\n";
        bMeasurements.display();}

    virtual ~Progress() {}
};
