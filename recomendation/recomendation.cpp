# include <iostream>
# include <string>
#include <vector>
#include "recomendation.h"

using namespace std;

string Recommendation::getUserId() const {return userId;};
string Recommendation::getFitnessGoal() const {return fitnessGoal;};
vector<string> Recommendation::getWorkoutPlan() const {return workoutPlan;};
vector<string> Recommendation::getDietPlan() const {return dietPlan;};
int Recommendation::getWeeklyWorkoutDays() const{return weeklyWorkoutDays;};
double Recommendation::getDailyCalorieTarget() const {return dailyCalorieTarget;};

void setWeeklyWorkoutDays(int days);
void setFittnessGoal(double newTarget);
void setWorkoutPlan(vector<string> newWorkoutPlan);
void setDietPlan(vector<string> newDietPlan);
void setDailyCalorieTarget(double newTarget);


void generateWorkoutPlan(const User& user) {
    
};
void generateDietPlan(const User& user);
void generateBeginnerWorkout();
void generateIntermediateWorkout();
void generateAdvancedWorkout();