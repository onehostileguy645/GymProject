#include<iostream>
#include<string>
#include "workout.h"
using namespace std;
// Exercise Class
// Constructors
Exercise::Exercise() {
    exerciseId = "";
    exerciseName = "";
    muscleGroup = "";
    sets = 0;
    reps = 0;
    weight = 0.0;
    restTime = 0;
}

Exercise:: Exercise(const string& id, const string& name, const string& mgroup, int s, int r, double w, int rest) {
  exerciseId = id;
  exerciseName = name;
  muscleGroup = mgroup;
  sets = s;
  reps = r;
  weight = w;
  restTime = rest;
}


// Function Definitions
 void Exercise::setExerciseId(const string& id) { 
    if (id.empty()) {
        throw "Exercise ID cannot be empty!";
    } 
    exerciseId = id; 
}
string Exercise::getExerciseId() const {
    return exerciseId; 
}

void Exercise::setExerciseName(const string& name) { 
    exerciseName = name;
 }
string Exercise::getExerciseName() const {
     return exerciseName; 
}

void Exercise::setMuscleGroup(const string& mgroup) { 
    muscleGroup = mgroup; 
}
string Exercise::getMuscleGroup() const { 
    return muscleGroup; 
}

void Exercise::setSets(int s) { 
      if (s < 0) {
        throw "Sets can't be negative!";
    }
    sets = s; 
}
int Exercise::getSets() const { 
    return sets; 
}

void Exercise::setReps(int r) {
      if (r < 0) {
        throw "Reps can't be negative!";
    } 
    reps = r; 
}
int Exercise::getReps() const { 
    return reps; 
}

void Exercise::setWeight(double w) { 
    if (w < 0) {
        throw "Weight can't be negative!";
    }
    weight = w; 
}
double Exercise::getWeight() const { 
    return weight;
}

void Exercise::setRestTime(int rest) { 
      if (rest < 0) {
        throw "Rest Time can't be negative!";
    }
    restTime = rest; 
}
int Exercise::getRestTime() const { 
    return restTime; 
}


double Exercise::calculateVolume() const {
    return sets*reps*weight;
}

bool Exercise::operator==(const Exercise& E) const {
    return exerciseId == E.exerciseId;
}

void Exercise::displayExercise()  const {
    cout << "Exercise ID: " << exerciseId << endl;
    cout << "Exercise Name: " << exerciseName << endl;
    cout << "Muscle Group: " << muscleGroup << endl;
    cout << "Sets: " << sets << endl;
    cout << "Reps: " << reps << endl;
    cout << "Weight: " << weight << " kg" << endl;
    cout << "Rest Time: " << restTime << " seconds" << endl;
}

Exercise::~Exercise() {}

ostream& operator<<(ostream& out, const Exercise& E) {
    out << E.getExerciseId() << " " << E.getExerciseName() << " " << endl;
    return out;
}

istream& operator>>(istream& in, Exercise& E) {
    string id, name, group;
    int set, rep, rest;
    double w;

    cout << "Enter Exercise ID: ";
    in >> id;
    cout << "Enter Exercise Name: ";
    getline(in >> ws, name);
    cout<<"Enter Muscle Group: ";
    getline(in >> ws, group);
    cout<<"Enter Sets: ";
    in >> set;
    cout<<"Enter Reps: ";
    in >> rep;
    cout<<"Enter Weight: ";
    in >> w;
    cout<<"Enter Rest Time: ";
    in >> rest;

    E.setExerciseId(id);
    E.setExerciseName(name);
    E.setMuscleGroup(group);
    E.setSets(set);
    E.setReps(rep);
    E.setWeight(w);
    E.setRestTime(rest);
    return in;
}


// Workout Class
// Constructors
Workout:: Workout() {
    workoutId = "";
    userId = "";
    date = "";
    workoutType = "";
    duration = 0;
    notes = "";
}

Workout::Workout(const string& wid, const string& userid, const string& d, const string& type, int durat, const string& n) {
    workoutId = wid;
    userId = userid;
    date = d;
    workoutType = type;
    duration = durat;
    notes = n;
}

void Workout::setWorkoutId(const string& wid) {
    workoutId = wid;
}
string Workout::getWorkoutId() const {
    return workoutId;
}

void Workout::setUserId(const string& userid) {
    userId = userid;
}
string Workout::getUserId() const {
    return userId;
}

void Workout::setDate(const string& d){
    date = d;
}
string Workout::getDate() const {
    return date;
}

void Workout::setWorkoutType(const string& type) {
    workoutType = type;
}
string Workout::getWorkoutType() const {
    return workoutType;
}

void Workout::setDuration(int durat) {
    duration = durat;
}
int Workout::getDuration() const {
    return duration;
}

void Workout::setNotes(const string& n) {
    notes = n;
}
string Workout::getNotes() const {
    return notes;
}

// Function Definitions
void Workout::addExercise(const Exercise& E)
{
    exercises.push_back(E);
}

double Workout::calculateTotalVolume() const {
    double totalVolume = 0;
    for(const Exercise& exercise: exercises) {
        totalVolume += exercise.calculateVolume();
    }
    return totalVolume;
}

int Workout::countExercisesByMuscleGroup(string muscleGroup) const {
    int count = 0;
    for(const Exercise& exercise: exercises) {
        if(exercise.getMuscleGroup() == muscleGroup) {
           count ++;
        }
    }
    return count;
}

void Workout::displayWorkout() const {
    cout<<"---Workout---\n";
    cout<<"Workout: " << workoutId << endl;
    cout<<"User ID: " << userId << endl;
    cout<<"Date: " << date << endl;
    cout<<"Workout Type: " << workoutType << endl;
    cout<<"Duration: " << duration << " minutes" << endl;
    cout<<"Notes: " << notes << endl; 
    cout<<"\n---Exercises---\n";

    for(const Exercise& exercise : exercises) {
        exercise.displayExercise();
        cout << endl;
    }
}


void Workout::displayWorkoutSummary() const {
    cout<<"Workout Summary for " << date << endl;
    cout<<"Workout Type: " << workoutType << endl;
    cout<<"Duration: " << duration << " minutes" << endl;
    cout<<"Total Volume: " << calculateTotalVolume() << " kg" << endl;
    cout<<"Exercises by Muscle Group: " << endl;
    vector<string> muscleGroups = {"Chest", "Back", "Legs", "Shoulders", "Arms", "Core"};
    for(const string& group : muscleGroups) {
    cout << group << ": " << countExercisesByMuscleGroup(group) << endl;
}
}

void Workout::saveToFile(const Workout& W) {
    ofstream file("workout.txt", ios::app | ios::out);

    if(!file) {
        cout << "File couldn't opened.\n";
        return;
    }

    file << W.workoutId << "|" << W.userId << "|" << W.date << "|" << W.workoutType << "|" << W.duration << "|" << W.notes << "|" << endl;

    for(const Exercise& E: W.exercises) {
        file << E.getExerciseId() << "|" << E.getExerciseName() << "|" << E.getMuscleGroup() << "|" << E.getSets() << "|" << E.getReps() << "|" << E.getWeight() << "|" << E.getRestTime() << endl;
    }
    file << "--------------------------------\n";

    file.close();
}

void Workout::loadByUserId(const string& uid) {
ifstream file("workout.txt");
string wid, userid, date, type, duration, notes;
string line;

bool found = false;

while(getline(file,wid, '|')) {
    getline(file, userid, '|');
    getline(file, date, '|');
    getline(file, type, '|');
    getline(file, duration, '|');
    getline(file, notes);

    if (userid == uid) {
        found = true;
        cout << "Workout Found: \n";
        cout << "Workout ID: " << wid << " - " ;
        cout << "Date: " << date << " - " ;
        cout << "Workout Type: " << type << " - " ; 
        cout << "Duration: " << duration << " - " ;
        cout << "Notes: " << notes << endl;
    }

    while(getline(file,line)) {
        if(line == "--------------------------------")
        break;
    }
}

    if (!found) {
        cout << "No workouts found for this User ID.\n";
    }

    file.close();
}

// Destructor
Workout::~Workout() {}


ostream& operator<<(ostream& out, const Workout& W) {
    out << W.getWorkoutId() << " " << endl;
    return out;
}

istream& operator>>(istream& in, Workout& W) {
    string wtid, usid, d, wtype, n;
    int durat;

    cout << "Enter Workout ID: ";
    in >> wtid;
    cout << "Enter User ID: ";
    getline(in >> ws, usid);
    cout<<"Enter Date: ";
    getline(in >> ws, d);
    cout<<"Enter Workout Type: ";
    getline(in >> ws, wtype);
    cout<<"Enter Duration Time of Workout: ";
    in >> durat;
    cout<<"Enter Notes for the Workout Day: ";
    getline(in >> ws, n);

    W.setWorkoutId(wtid);
    W.setUserId(usid);
    W.setDate(d);
    W.setWorkoutType(wtype);
    W.setDuration(durat);
    W.setNotes(n);
    return in;
}

int main() {
int choice;
string userId;
Workout workout;

do {
    cout << "\n ----- Workout Section -----\n";
    cout << "1. Add Workout.\n";
    cout << "2. Add Exercise to Workout.\n";
    cout << "3. Display Workout.\n";
    cout << "4. Display Workout Summary.\n";
    cout << "5. Save Workout.\n";
    cout << "6. Load My Workouts.\n";
    cout << "7. Exit.\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch(choice) {
    case 1:
        cin >> workout;
        break;
    case 2:{
        try {
        Exercise e;
        cin >> e;
        workout.addExercise(e);
        }
        catch(const char* message) {
            cout << "Error: " << message << endl;
            cout << "Please try again.\n";
        }
        break;
    }
    case 3:
        workout.displayWorkout();
        break;
    case 4:
        workout.displayWorkoutSummary();
        break;
    case 5:
        Workout::saveToFile(workout);
        cout << "All the info saved into the file successfully!\n";
        break;
    case 6: {
        cout << "Enter User ID: ";
        cin >> userId;
        Workout::loadByUserId(userId);
        break;
    }
    case 7:
        cout << "Thank you for entering this section!\n";
        break;
    default:
        cout << "Invalid choice!\n";
        break;
    }
}while(choice != 7 );

    return 0;
}
