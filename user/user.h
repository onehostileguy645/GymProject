#include <string>

using namespace std;

class User {
protected:
    string userId;
    string username;
    string password;
    string email;
    int age;
    double weight;        // in kg
    double height;        // in cm
    string gender;
    string fitnessLevel;  // "Beginner", "Intermediate", "Advanced"
    string membershipId;
    string experience;
public:
    // getter settert
    string getUserId() const;
    string getUsername() const;
    string getPassword() const;
    string getEmail() const;
    int getAge() const;
    double getWeight() const;
    double getHeight() const;
    string getGender() const;
    string getFitnessLevel() const;
    string getMembershipId() const;
    string getExperience() const;
    void setUserId();
    void setUsername();
    void setPassword();
    void setEmail();
    void setAge();
    void setWeight();
    void setHeight();
    void setGender();
    void setFitnessLevel();
    void setMembershipId();
    void setExperience();

    // Member Functions
    virtual void displayProfile() const;  // Polymorphism - virtual function
    void updateProfile();
    // login/register
};