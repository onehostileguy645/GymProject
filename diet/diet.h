#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Meal {
private:
    string mealId;
    string mealName;
    string mealTime;  // "Breakfast", "Lunch", "Dinner", "Snack"
    double calories;
    double protein;   // in grams
    double carbs;     // in grams
    double fats;      // in grams
    
public:
    // Constructors
    Meal();
    Meal(string id, string name, string time, double cal, double prot, double carb, double fat);
    
    // Getters
    string getMealId() const;
    string getMealName() const;
    string getMealTime() const;
    double getCalories() const;
    double getProtein() const;
    double getCarbs() const;
    double getFats() const;
    
    // Setters
    void setMealId(string id);
    void setMealName(string name);
    void setMealTime(string time);
    void setCalories(double cal);
    void setProtein(double prot);
    void setCarbs(double carb);
    void setFats(double fat);
    
    // Display
    void displayMeal() const;
    
    // Operator Overloading
    bool operator==(const Meal& other) const;
    Meal operator+(const Meal& other) const;  // Combine meals (add macros)
    friend ostream& operator<<(ostream& os, const Meal& meal);
};

// Diet Plan Class
class Diet {
private:
    string dietId;
    string userId;
    string date;
    vector<Meal> meals;
    double dailyCalorieGoal;
    double dailyProteinGoal;
    
public:
    // Constructors
    Diet();
    Diet(string did, string uid, string d, double calGoal, double protGoal);
    
    // Destructor
    ~Diet();
    
    // Getters
    string getDietId() const;
    string getUserId() const;
    string getDate() const;
    vector<Meal> getMeals() const;
    double getDailyCalorieGoal() const;
    double getDailyProteinGoal() const;
    
    // Setters
    void setDietId(string did);
    void setUserId(string uid);
    void setDate(string d);
    void setDailyCalorieGoal(double goal);
    void setDailyProteinGoal(double goal);
    
    // Meal Management
    void addMeal(const Meal& meal);
    void deleteMeal(string mealId);
    void updateMeal(string mealId, const Meal& updatedMeal);
    Meal findMealById(string mealId) const;
    
    // Calculations
    double calculateTotalCalories() const;
    double calculateTotalProtein() const;
    double calculateTotalCarbs() const;
    double calculateTotalFats() const;
    double getCalorieProgress() const;  // Percentage of goal achieved
    
    // Display
    void displayDietPlan() const;
    void displayMacroSummary() const;
    
    // File Operations
    void saveToFile() const;
    static vector<Diet> loadAllDiets();
    static vector<Diet> loadDietsByUserId(string uid);
    
    // Operator Overloading
    Diet& operator+=(const Meal& meal);  // Add meal to diet
    bool operator==(const Diet& other) const;
    friend ostream& operator<<(ostream& os, const Diet& diet);
};
