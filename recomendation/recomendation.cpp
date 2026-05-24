#include "recomendation.h"
#include <iostream>
#include <fstream>

using namespace std;

// Initialize static member
string Recommendation::recommendationId = "REC001";

// ==================== HELPER FUNCTIONS ====================

// Split string by delimiter
vector<string> splitString(const string& str, char delimiter) {
    vector<string> result;
    string current = "";

    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == delimiter) {
            result.push_back(current);
            current = "";
        } else {
            current += str[i];
        }
    }

    // Add last part
    if (!current.empty() || str[str.length()-1] == delimiter) {
        result.push_back(current);
    }

    return result;
}

// ==================== GETTERS ====================

string Recommendation::getUserId() const {
    return userId;
}

string Recommendation::getFitnessGoal() const {
    return fitnessGoal;
}

vector<string> Recommendation::getWorkoutPlan() const {
    return workoutPlan;
}

vector<string> Recommendation::getDietPlan() const {
    return dietPlan;
}

int Recommendation::getWeeklyWorkoutDays() const {
    return weeklyWorkoutDays;
}

double Recommendation::getDailyCalorieTarget() const {
    return dailyCalorieTarget;
}

// ==================== SETTERS ====================

void Recommendation::setWeeklyWorkoutDays(int days) {
    if (days >= 0 && days <= 7) {
        weeklyWorkoutDays = days;
    } else {
        cout << "Error: Weekly workout days must be between 0 and 7." << endl;
    }
}

void Recommendation::setFittnessGoal(double newTarget) {
    // Note: This seems to be a typo in the header - should probably be string for fitnessGoal
    // For now, treating it as setting calorie target
    dailyCalorieTarget = newTarget;
}

void Recommendation::setWorkoutPlan(vector<string> newWorkoutPlan) {
    workoutPlan = newWorkoutPlan;
}

void Recommendation::setDietPlan(vector<string> newDietPlan) {
    dietPlan = newDietPlan;
}

void Recommendation::setDailyCalorieTarget(double newTarget) {
    if (newTarget > 0) {
        dailyCalorieTarget = newTarget;
    } else {
        cout << "Error: Calorie target must be positive." << endl;
    }
}

// ==================== RECOMMENDATION GENERATION ====================

void Recommendation::generateWorkoutPlan(const User& user) {
    workoutPlan.clear();

    string level = user.getFitnessLevel();

    if (level == "Beginner") {
        generateBeginnerWorkout();
    } else if (level == "Intermediate") {
        generateIntermediateWorkout();
    } else if (level == "Advanced") {
        generateAdvancedWorkout();
    } else {
        // Default to beginner if level is unknown
        generateBeginnerWorkout();
    }
}

void Recommendation::generateBeginnerWorkout() {
    workoutPlan.clear();
    weeklyWorkoutDays = 3;

    workoutPlan.push_back("DAY 1 - Full Body A:");
    workoutPlan.push_back("  - Squats: 3 sets x 10 reps");
    workoutPlan.push_back("  - Push-ups: 3 sets x 8-10 reps");
    workoutPlan.push_back("  - Dumbbell Rows: 3 sets x 10 reps");
    workoutPlan.push_back("  - Plank: 3 sets x 30 seconds");
    workoutPlan.push_back("");

    workoutPlan.push_back("DAY 2 - Cardio & Core:");
    workoutPlan.push_back("  - Walking/Jogging: 20-30 minutes");
    workoutPlan.push_back("  - Bicycle Crunches: 3 sets x 15 reps");
    workoutPlan.push_back("  - Russian Twists: 3 sets x 20 reps");
    workoutPlan.push_back("  - Mountain Climbers: 3 sets x 10 reps");
    workoutPlan.push_back("");

    workoutPlan.push_back("DAY 3 - Full Body B:");
    workoutPlan.push_back("  - Lunges: 3 sets x 10 reps per leg");
    workoutPlan.push_back("  - Dumbbell Shoulder Press: 3 sets x 10 reps");
    workoutPlan.push_back("  - Lat Pulldowns: 3 sets x 10 reps");
    workoutPlan.push_back("  - Dead Bug: 3 sets x 10 reps per side");
}

void Recommendation::generateIntermediateWorkout() {
    workoutPlan.clear();
    weeklyWorkoutDays = 4;

    workoutPlan.push_back("DAY 1 - Upper Body Push:");
    workoutPlan.push_back("  - Bench Press: 4 sets x 8-10 reps");
    workoutPlan.push_back("  - Overhead Press: 3 sets x 8-10 reps");
    workoutPlan.push_back("  - Incline Dumbbell Press: 3 sets x 10-12 reps");
    workoutPlan.push_back("  - Tricep Dips: 3 sets x 10-12 reps");
    workoutPlan.push_back("  - Lateral Raises: 3 sets x 12-15 reps");
    workoutPlan.push_back("");

    workoutPlan.push_back("DAY 2 - Lower Body:");
    workoutPlan.push_back("  - Squats: 4 sets x 8-10 reps");
    workoutPlan.push_back("  - Romanian Deadlifts: 3 sets x 10 reps");
    workoutPlan.push_back("  - Leg Press: 3 sets x 12 reps");
    workoutPlan.push_back("  - Leg Curls: 3 sets x 12 reps");
    workoutPlan.push_back("  - Calf Raises: 4 sets x 15 reps");
    workoutPlan.push_back("");

    workoutPlan.push_back("DAY 3 - Upper Body Pull:");
    workoutPlan.push_back("  - Deadlifts: 4 sets x 6-8 reps");
    workoutPlan.push_back("  - Pull-ups/Lat Pulldowns: 4 sets x 8-10 reps");
    workoutPlan.push_back("  - Barbell Rows: 3 sets x 8-10 reps");
    workoutPlan.push_back("  - Face Pulls: 3 sets x 12-15 reps");
    workoutPlan.push_back("  - Bicep Curls: 3 sets x 10-12 reps");
    workoutPlan.push_back("");

    workoutPlan.push_back("DAY 4 - Cardio & Core:");
    workoutPlan.push_back("  - HIIT Intervals: 20-25 minutes");
    workoutPlan.push_back("  - Ab Wheel Rollouts: 3 sets x 10 reps");
    workoutPlan.push_back("  - Hanging Leg Raises: 3 sets x 12 reps");
    workoutPlan.push_back("  - Plank Variations: 3 sets x 45 seconds");
}

void Recommendation::generateAdvancedWorkout() {
    workoutPlan.clear();
    weeklyWorkoutDays = 5;

    workoutPlan.push_back("DAY 1 - Chest & Triceps:");
    workoutPlan.push_back("  - Flat Barbell Bench Press: 4 sets x 6-8 reps");
    workoutPlan.push_back("  - Incline Dumbbell Press: 4 sets x 8-10 reps");
    workoutPlan.push_back("  - Dips (weighted): 3 sets x 8-10 reps");
    workoutPlan.push_back("  - Cable Flyes: 3 sets x 12 reps");
    workoutPlan.push_back("  - Close-Grip Bench Press: 3 sets x 8-10 reps");
    workoutPlan.push_back("  - Tricep Pushdowns: 3 sets x 12-15 reps");
    workoutPlan.push_back("");

    workoutPlan.push_back("DAY 2 - Back & Biceps:");
    workoutPlan.push_back("  - Deadlifts: 4 sets x 5-6 reps");
    workoutPlan.push_back("  - Weighted Pull-ups: 4 sets x 6-8 reps");
    workoutPlan.push_back("  - Barbell Rows: 4 sets x 8-10 reps");
    workoutPlan.push_back("  - T-Bar Rows: 3 sets x 10 reps");
    workoutPlan.push_back("  - Barbell Curls: 4 sets x 8-10 reps");
    workoutPlan.push_back("  - Hammer Curls: 3 sets x 10-12 reps");
    workoutPlan.push_back("");

    workoutPlan.push_back("DAY 3 - Legs (Quad Focus):");
    workoutPlan.push_back("  - Squats: 5 sets x 5-6 reps");
    workoutPlan.push_back("  - Front Squats: 3 sets x 8-10 reps");
    workoutPlan.push_back("  - Leg Press: 4 sets x 10-12 reps");
    workoutPlan.push_back("  - Leg Extensions: 3 sets x 12-15 reps");
    workoutPlan.push_back("  - Walking Lunges: 3 sets x 12 reps per leg");
    workoutPlan.push_back("  - Calf Raises: 4 sets x 15-20 reps");
    workoutPlan.push_back("");

    workoutPlan.push_back("DAY 4 - Shoulders & Abs:");
    workoutPlan.push_back("  - Overhead Press: 4 sets x 6-8 reps");
    workoutPlan.push_back("  - Arnold Press: 3 sets x 8-10 reps");
    workoutPlan.push_back("  - Lateral Raises: 4 sets x 12-15 reps");
    workoutPlan.push_back("  - Rear Delt Flyes: 3 sets x 12-15 reps");
    workoutPlan.push_back("  - Face Pulls: 3 sets x 15 reps");
    workoutPlan.push_back("  - Hanging Leg Raises: 4 sets x 12-15 reps");
    workoutPlan.push_back("  - Cable Crunches: 4 sets x 15 reps");
    workoutPlan.push_back("");

    workoutPlan.push_back("DAY 5 - Legs (Hamstring Focus):");
    workoutPlan.push_back("  - Romanian Deadlifts: 4 sets x 8-10 reps");
    workoutPlan.push_back("  - Leg Curls: 4 sets x 10-12 reps");
    workoutPlan.push_back("  - Bulgarian Split Squats: 3 sets x 10 reps per leg");
    workoutPlan.push_back("  - Glute-Ham Raises: 3 sets x 8-10 reps");
    workoutPlan.push_back("  - Hip Thrusts: 4 sets x 10-12 reps");
}

void Recommendation::generateDietPlan(const User& user) {
    dietPlan.clear();

    // Calculate calorie target based on fitness goal and user stats
    double bmr = 0;
    if (user.getGender() == 'M') {
        bmr = 10 * user.getWeight() + 6.25 * user.getHeight() - 5 * user.getAge() + 5;
    } else {
        bmr = 10 * user.getWeight() + 6.25 * user.getHeight() - 5 * user.getAge() - 161;
    }

    // Activity multiplier based on fitness level
    double activityMultiplier = 1.375; // Light activity default
    if (user.getFitnessLevel() == "Intermediate") {
        activityMultiplier = 1.55; // Moderate activity
    } else if (user.getFitnessLevel() == "Advanced") {
        activityMultiplier = 1.725; // Very active
    }

    double tdee = bmr * activityMultiplier;

    // Adjust based on fitness goal
    if (fitnessGoal == "Weight Loss") {
        dailyCalorieTarget = tdee - 500; // 500 calorie deficit
        dietPlan.push_back("=== WEIGHT LOSS DIET PLAN ===");
        dietPlan.push_back("Goal: Create a moderate calorie deficit");
        dietPlan.push_back("");
    } else if (fitnessGoal == "Muscle Gain") {
        dailyCalorieTarget = tdee + 300; // 300 calorie surplus
        dietPlan.push_back("=== MUSCLE GAIN DIET PLAN ===");
        dietPlan.push_back("Goal: Create a moderate calorie surplus");
        dietPlan.push_back("");
    } else if (fitnessGoal == "Maintenance") {
        dailyCalorieTarget = tdee;
        dietPlan.push_back("=== MAINTENANCE DIET PLAN ===");
        dietPlan.push_back("Goal: Maintain current weight and composition");
        dietPlan.push_back("");
    } else { // Endurance
        dailyCalorieTarget = tdee + 200;
        dietPlan.push_back("=== ENDURANCE DIET PLAN ===");
        dietPlan.push_back("Goal: Support high activity levels");
        dietPlan.push_back("");
    }

    // Calculate macros
    double proteinGrams = user.getWeight() * 2.0; // 2g per kg bodyweight
    double fatGrams = (dailyCalorieTarget * 0.25) / 9; // 25% of calories from fat
    double carbGrams = (dailyCalorieTarget - (proteinGrams * 4) - (fatGrams * 9)) / 4;

    dietPlan.push_back("Daily Calorie Target: " + to_string(static_cast<int>(dailyCalorieTarget)) + " kcal");
    dietPlan.push_back("Protein: " + to_string(static_cast<int>(proteinGrams)) + "g");
    dietPlan.push_back("Carbs: " + to_string(static_cast<int>(carbGrams)) + "g");
    dietPlan.push_back("Fats: " + to_string(static_cast<int>(fatGrams)) + "g");
    dietPlan.push_back("");

    // Sample meal plan
    dietPlan.push_back("BREAKFAST (30% of daily calories):");
    if (fitnessGoal == "Muscle Gain") {
        dietPlan.push_back("  - 4 whole eggs scrambled");
        dietPlan.push_back("  - 2 slices whole grain toast");
        dietPlan.push_back("  - 1 banana");
        dietPlan.push_back("  - Protein shake");
    } else if (fitnessGoal == "Weight Loss") {
        dietPlan.push_back("  - 3 egg whites + 1 whole egg");
        dietPlan.push_back("  - 1 cup oatmeal");
        dietPlan.push_back("  - 1/2 cup berries");
    } else {
        dietPlan.push_back("  - 3 whole eggs");
        dietPlan.push_back("  - 1 cup oatmeal");
        dietPlan.push_back("  - 1 apple");
    }
    dietPlan.push_back("");

    dietPlan.push_back("LUNCH (30% of daily calories):");
    if (fitnessGoal == "Muscle Gain") {
        dietPlan.push_back("  - 200g grilled chicken breast");
        dietPlan.push_back("  - 1.5 cups brown rice");
        dietPlan.push_back("  - Mixed vegetables");
        dietPlan.push_back("  - Olive oil dressing");
    } else if (fitnessGoal == "Weight Loss") {
        dietPlan.push_back("  - 150g grilled chicken breast");
        dietPlan.push_back("  - Large mixed salad");
        dietPlan.push_back("  - 1/2 cup quinoa");
    } else {
        dietPlan.push_back("  - 175g grilled chicken breast");
        dietPlan.push_back("  - 1 cup brown rice");
        dietPlan.push_back("  - Steamed vegetables");
    }
    dietPlan.push_back("");

    dietPlan.push_back("SNACK (10% of daily calories):");
    dietPlan.push_back("  - Greek yogurt");
    dietPlan.push_back("  - Handful of almonds");
    dietPlan.push_back("  - Apple or banana");
    dietPlan.push_back("");

    dietPlan.push_back("DINNER (30% of daily calories):");
    if (fitnessGoal == "Muscle Gain") {
        dietPlan.push_back("  - 200g salmon");
        dietPlan.push_back("  - 200g sweet potato");
        dietPlan.push_back("  - Asparagus");
        dietPlan.push_back("  - Avocado");
    } else if (fitnessGoal == "Weight Loss") {
        dietPlan.push_back("  - 150g white fish");
        dietPlan.push_back("  - Large portion vegetables");
        dietPlan.push_back("  - Small sweet potato");
    } else {
        dietPlan.push_back("  - 175g lean beef");
        dietPlan.push_back("  - 150g sweet potato");
        dietPlan.push_back("  - Mixed vegetables");
    }
    dietPlan.push_back("");

    dietPlan.push_back("HYDRATION:");
    dietPlan.push_back("  - Drink at least 8-10 glasses of water daily");
    dietPlan.push_back("  - More during workout days");
}

// ==================== CUSTOMIZATION ====================

void Recommendation::customizeRecommendation() {
    int choice;

    cout << "\n=== CUSTOMIZE RECOMMENDATION ===" << endl;
    cout << "1. Adjust Calorie Target" << endl;
    cout << "2. Adjust Weekly Workout Days" << endl;
    cout << "3. Change Fitness Goal" << endl;
    cout << "4. Return to Main Menu" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch(choice) {
        case 1: {
            double newCalories;
            cout << "Enter new daily calorie target: ";
            cin >> newCalories;
            adjustCalorieTarget(newCalories);
            cout << "Calorie target updated successfully!" << endl;
            break;
        }
        case 2: {
            int newDays;
            cout << "Enter new weekly workout days (0-7): ";
            cin >> newDays;
            adjustWorkoutDays(newDays);
            cout << "Workout days updated successfully!" << endl;
            break;
        }
        case 3: {
            cout << "Select new fitness goal:" << endl;
            cout << "1. Weight Loss" << endl;
            cout << "2. Muscle Gain" << endl;
            cout << "3. Maintenance" << endl;
            cout << "4. Endurance" << endl;
            int goalChoice;
            cin >> goalChoice;

            switch(goalChoice) {
                case 1: fitnessGoal = "Weight Loss"; break;
                case 2: fitnessGoal = "Muscle Gain"; break;
                case 3: fitnessGoal = "Maintenance"; break;
                case 4: fitnessGoal = "Endurance"; break;
                default: cout << "Invalid choice!" << endl; return;
            }
            cout << "Fitness goal updated to: " << fitnessGoal << endl;
            break;
        }
        case 4:
            return;
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Recommendation::adjustCalorieTarget(double newTarget) {
    setDailyCalorieTarget(newTarget);
    cout << "Daily calorie target adjusted to: " << newTarget << " kcal" << endl;
}

void Recommendation::adjustWorkoutDays(int days) {
    setWeeklyWorkoutDays(days);
    cout << "Weekly workout days adjusted to: " << days << " days" << endl;
}

// ==================== DISPLAY ====================

void Recommendation::displayRecommendation() const {
    cout << "\n╔════════════════════════════════════════════════╗" << endl;
    cout << "║        PERSONALIZED FITNESS RECOMMENDATION      ║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl;

    cout << "\nUser ID: " << userId << endl;
    cout << "Fitness Goal: " << fitnessGoal << endl;
    cout << "Weekly Workout Days: " << weeklyWorkoutDays << endl;
    cout << "Daily Calorie Target: " << static_cast<int>(dailyCalorieTarget) << " kcal" << endl;

    cout << "\n" << string(50, '=') << endl;
    displayWorkoutPlan();

    cout << "\n" << string(50, '=') << endl;
    displayDietPlan();
}

void Recommendation::displayWorkoutPlan() const {
    cout << "\n┌─────────────────────────────────────────────┐" << endl;
    cout << "│            WORKOUT PLAN                      │" << endl;
    cout << "└─────────────────────────────────────────────┘" << endl;

    if (workoutPlan.empty()) {
        cout << "No workout plan generated yet." << endl;
        return;
    }

    for (const string& line : workoutPlan) {
        cout << line << endl;
    }
}

void Recommendation::displayDietPlan() const {
    cout << "\n┌─────────────────────────────────────────────┐" << endl;
    cout << "│            DIET PLAN                         │" << endl;
    cout << "└─────────────────────────────────────────────┘" << endl;

    if (dietPlan.empty()) {
        cout << "No diet plan generated yet." << endl;
        return;
    }

    for (const string& line : dietPlan) {
        cout << line << endl;
    }
}

// ==================== FILE HANDLING ====================

void Recommendation::saveToFile() const {
    ofstream file("recommendations.txt", ios::app);

    if (!file.is_open()) {
        cout << "Error: Could not open recommendations.txt for writing." << endl;
        return;
    }

    // Write main data line
    file << recommendationId << "|"
         << userId << "|"
         << fitnessGoal << "|"
         << weeklyWorkoutDays << "|"
         << dailyCalorieTarget << endl;

    // Write workout plan (comma-separated)
    for (size_t i = 0; i < workoutPlan.size(); i++) {
        file << workoutPlan[i];
        if (i < workoutPlan.size() - 1) {
            file << ",";
        }
    }
    file << endl;

    // Write diet plan (comma-separated)
    for (size_t i = 0; i < dietPlan.size(); i++) {
        file << dietPlan[i];
        if (i < dietPlan.size() - 1) {
            file << ",";
        }
    }
    file << endl;

    // Separator between records
    file << "---" << endl;

    file.close();
    cout << "Recommendation saved successfully!" << endl;
}

vector<Recommendation> Recommendation::loadAllRecommendations() {
    vector<Recommendation> recommendations;
    ifstream file("recommendations.txt");

    if (!file.is_open()) {
        cout << "No recommendations file found or unable to open." << endl;
        return recommendations;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty() || line == "---") continue;

        // Parse main data line using splitString
        vector<string> parts = splitString(line, '|');

        if (parts.size() < 5) continue; // Invalid format

        string recId = parts[0];
        string uId = parts[1];
        string goal = parts[2];
        int weekDays = stoi(parts[3]);
        double calorieTarget = stod(parts[4]);

        Recommendation rec(uId, goal);
        rec.weeklyWorkoutDays = weekDays;
        rec.dailyCalorieTarget = calorieTarget;

        // Read workout plan line
        if (getline(file, line)) {
            if (!line.empty()) {
                vector<string> workoutItems = splitString(line, ',');
                rec.workoutPlan = workoutItems;
            }
        }

        // Read diet plan line
        if (getline(file, line)) {
            if (!line.empty()) {
                vector<string> dietItems = splitString(line, ',');
                rec.dietPlan = dietItems;
            }
        }

        recommendations.push_back(rec);
    }

    file.close();
    return recommendations;
}

vector<Recommendation> Recommendation::loadByUserId(string uid) {
    vector<Recommendation> allRecommendations = loadAllRecommendations();
    vector<Recommendation> userRecommendations;

    for (const Recommendation& rec : allRecommendations) {
        if (rec.userId == uid) {
            userRecommendations.push_back(rec);
        }
    }

    return userRecommendations;
}