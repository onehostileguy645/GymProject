#include <vector>
#include <string>
#include "user.h"
using namespace std;

class Recommendation {
private:
    static string recommendationId;
    string userId;
    string fitnessGoal;  // "Weight Loss", "Muscle Gain", "Maintenance", "Endurance"
    vector<string> workoutPlan;
    vector<string> dietPlan;
    int weeklyWorkoutDays;
    double dailyCalorieTarget;

public:
    // Constructors
    Recommendation(string userId, string fitnessGoal): userId(userId), fitnessGoal(fitnessGoal) {};

    // getter-setter
    string getUserId() const;
    string getFitnessGoal() const;
    vector<string> getWorkoutPlan() const;
    vector<string> getDietPlan() const;
    int getWeeklyWorkoutDays() const;
    double getDailyCalorieTarget() const;

    void setWeeklyWorkoutDays(int days);
    void setFittnessGoal(double newTarget);
    void setWorkoutPlan(vector<string> newWorkoutPlan);
    void setDietPlan(vector<string> newDietPlan);
    void setDailyCalorieTarget(double newTarget);


    // Recommendation Generation
    void generateWorkoutPlan(const User& user);
    void generateDietPlan(const User& user);
    void generateBeginnerWorkout();
    void generateIntermediateWorkout();
    void generateAdvancedWorkout();

    // Customization
    void customizeRecommendation();
    void adjustCalorieTarget(double newTarget);
    void adjustWorkoutDays(int days);

    // Display
    void displayRecommendation() const;
    void displayWorkoutPlan() const;
    void displayDietPlan() const;
};
