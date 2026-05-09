#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class UserRecord {
public:
    int userId;
    char username[30];
    char password[15];
    char email[50];
    char userType[10];       // "Member", "Admin"
    int age;
    double weight;        // in kg
    double height;        // in cm
    char gender;       // "M", "F", "O" (Other)
    char fitnessLevel[15];  // "Beginner", "Intermediate", "Advanced"
    char membershipId[10];
    int experience;      // in years, for trainers

    // Default constructor
    UserRecord() {
        userId = 0;
        username[0] = '\0';
        password[0] = '\0';
        email[0] = '\0';
        userType[0] = '\0';
        age = 0;
        weight = 0.0;
        height = 0.0;
        gender = 'O';
        fitnessLevel[0] = '\0';
        membershipId[0] = '\0';
        experience = 0;
    }

    // Constructor to match the usage in user.cpp
    UserRecord(int id, string ut, string un, string pw, string em, int a, double w, double h, char g, string fl, string mi, int ex) {
        userId = id;
        int len = min((int)ut.size(), 9);
        for(int i = 0; i < len; i++) userType[i] = ut[i];
        userType[len] = '\0';

        len = min((int)un.size(), 29);
        for(int i = 0; i < len; i++) username[i] = un[i];
        username[len] = '\0';

        len = min((int)pw.size(), 14);
        for(int i = 0; i < len; i++) password[i] = pw[i];
        password[len] = '\0';

        len = min((int)em.size(), 49);
        for(int i = 0; i < len; i++) email[i] = em[i];
        email[len] = '\0';

        age = a;
        weight = w;
        height = h;
        gender = g;

        len = min((int)fl.size(), 14);
        for(int i = 0; i < len; i++) fitnessLevel[i] = fl[i];
        fitnessLevel[len] = '\0';

        len = min((int)mi.size(), 9);
        for(int i = 0; i < len; i++) membershipId[i] = mi[i];
        membershipId[len] = '\0';

        experience = ex;
    }
    
};

class User {
 UserRecord userRecords;  // Composition - User has a UserRecord
public:
    // getter setters

    int getUserId() const;
    string getUsername() const;
    string getPassword() const;
    string getEmail() const;
    string getUserType() const;
    int getAge() const;
    double getWeight() const;
    double getHeight() const;
    char getGender() const;
    string getFitnessLevel() const;
    string getMembershipId() const;
    int getExperience() const;
    void setUserId(int IdUser);
    void setUserType(string typeUser);
    void setUsername(string name);
    void setPassword(string passwrd);
    void setEmail(string mail);
    void setAge(int Age);
    void setWeight(double Weight);
    void setHeight(double Height);
    void setGender(char gen);
    void setFitnessLevel(string lvl);
    void setMembershipId(string memId);
    void setExperience(int exp);
    

    // Member Functions
    virtual void displayProfile() const;
      // Polymorphism - virtual function
    void updateProfile(fstream& userFile);
    void deleteProfile(fstream& userFile);
    // login/register

   User(int IdUser = 0, string typeUser="", string name = "", string passwrd = "", string mail = "", int Age = 0, double Weight = 0.0, double Height = 0.0, char gen = 'O', string lvl = "", string memId = "", int exp = 0) {
        setUserId(IdUser);
        setUserType(typeUser);
        setUsername(name);
        setPassword(passwrd);
        setEmail(mail);
        setAge(Age);
        setWeight(Weight);
        setHeight(Height);
        setGender(gen);
        setFitnessLevel(lvl);
        setMembershipId(memId);
        setExperience(exp);
       
    }
    virtual ~User() {}
};
class Admin : public User {

public:
    void displayProfile() const override;  // Override for Admin profile display // Admin-specific function to manage users
    void addUser(fstream& userFile);
    void removeUser(fstream& userFile);
    void updateUser(fstream& userFile);
    void reviewUserInfo(fstream& userFile);
private:
};
class Trainer : public User{
    protected:
    string specialization;   // e.g. "Weight Loss", "Strength", "Cardio"
    int yearsOfExperience;
    vector<string> assignedMembers; // list of user IDs
    double rating;
    double salary;

    public: 
    void displayProfile() const override;
};