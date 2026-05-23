#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
// Exercise Class
class Exercise {
private:
string exerciseId;

string exerciseName;
string muscleGroup; 
int sets, reps;
double weight; 
int restTime; 

public:
// Constructors
Exercise();
Exercise(const string& id, const string& name, const string& mgroup, int s, int r, double w, int rest) ;

// setter - getters
void setExerciseId(const string& id);
string getExerciseId() const;

void setExerciseName(const string& name);
string getExerciseName() const;

void setMuscleGroup(const string& mgroup);
string getMuscleGroup() const;

void setSets(int s);
int getSets() const;

void setReps(int r);
int getReps() const;

void setWeight(double w);
double getWeight() const;

void setRestTime(int rest);
int getRestTime() const;

// Functions
double calculateVolume() const;

bool operator==(const Exercise& E) const;

// Display
void displayExercise() const;

// Destructor
~Exercise();
};

// Stream Insertion Operator (<<)
ostream& operator<<(ostream& out, const Exercise& E);

// Stream Extraction Operator (>>) 
istream& operator>>(istream& in, Exercise& E);

// Workout Class
class Workout {
private:
string workoutId;
string userId;
string date;
string workoutType; 
vector<Exercise> exercises;
int duration; 
string notes;

public:
// Constructors
Workout();
Workout(const string& wid, const string& userid, const string& d, const string& type, int durat, const string& n);

// File Handling Functions
static void saveToFile(const Workout& W);
static void loadByUserId(const string& userId);

// setter - getters
void setWorkoutId (const string& wid);
string getWorkoutId() const;

void setUserId(const string& userid);
string getUserId() const;

void setDate(const string& d);
string getDate() const;

void setWorkoutType(const string& type);
string getWorkoutType() const;

void setDuration(int durat);
int getDuration() const;

void setNotes(const string& n);
string getNotes() const;

// Calculation Functions
double calculateTotalVolume() const;

int countExercisesByMuscleGroup(string muscleGroup) const;

void addExercise(const Exercise& E);

// Display
void displayWorkout() const;
void displayWorkoutSummary() const;

// Destructor
~Workout();

};

// Stream Insertion Operator (<<)
ostream& operator<<(ostream& out, const Workout& W);
// Stream Extraction Operator (>>) 
istream& operator>>(istream& in, Workout& W);
