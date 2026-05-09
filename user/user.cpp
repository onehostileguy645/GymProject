
#include "user.h"
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <iomanip>


int enterChoiceMenu();
const int maxRecords = 100;
void Register(fstream& outUserInfo);
void Login(fstream& userInfo);
void initializeFile(fstream& file);
int  enterChoiceMenu();
void userMenu(User& user, fstream& userInfo);
void adminMenu(Admin& admin, fstream& userInfo);
void trainerMenu(Trainer& trainer, fstream& userInfo);

void User::setUserId(int IdUser){
    userRecords.userId = IdUser;
}
void User::setUserType(string typeUser){
    // if(typeUser != "Member" && typeUser != "Admin" && typeUser != "Trainer"){
    //     cout << "Invalid user type! (Recommened checking for typo). Setting to 'Member' by default." << endl;
    //     typeUser = "Member";
    // }else{}
    int length = (typeUser.size() < 10) ? typeUser.size() : 9;
    for (int i = 0; i < length; ++i)
            userRecords.userType[i]= typeUser[i];
    userRecords.userType[length] = '\0';
    
}
void User::setUsername(string name){
    //  memset(username, 0, sizeof(username));
    int length = (name.size() < 30) ? name.size() : 29;
    for (int i = 0; i < length; ++i)
            userRecords.username[i] = name[i];
    userRecords.username[length] = '\0';
    
}
void User::setPassword(string passwrd){

    int length = (passwrd.size() < 15) ? passwrd.size() : 14;
    for (int i = 0; i < length; ++i)
            userRecords.password[i] = passwrd[i];
    userRecords.password[length] = '\0';
}
void User::setEmail(string mail){
    int length = (mail.size() < 50) ? mail.size() : 49;
    for (int i = 0; i < length; ++i)
            userRecords.email[i] = mail[i];
    userRecords.email[length] = '\0';
}
void User::setAge(int Age){
    // if(Age < 0) {
    //     cout << "Invalid age! Setting your age to 0 by default." << endl;
    //     age = 0;
    // } else
    userRecords.age = Age;
}
void User::setWeight(double Weight){
    // if(userWeight < 0) {
    //     cout << "Invalid weight! Setting your weight to 0 by default." << endl;
    //     weight = 0;
    // } else
    userRecords.weight = Weight;
}
void User::setHeight(double Height){
    // if(Height < 0) {
    //     cout << "Invalid height! Setting your height to 0 by default." << endl;
    //     height = 0;
    // } else
    userRecords.height = Height;
}
void User::setGender(char gen){
    // if(gen != 'M' && gen != 'F' && gen != 'O') {
    //     cout << "Invalid gender! Setting your gender to 'O' (Other) by default." << endl;
    // } else {
        userRecords.gender = gen;
    // }
}
void User::setFitnessLevel(string lvl){
    // if(level != 'B' && level != 'I' && level != 'A') {
    //     cout << "Invalid fitness level! Setting your fitness level to 'B' (Beginner) by default." << endl;
    //     fitnessLevel = 'B';
    // } else
     int length = (lvl.size() < 15) ? lvl.size() : 14;
    for (int i = 0; i < length; ++i)
            userRecords.fitnessLevel[i] = lvl[i];
    userRecords.fitnessLevel[length] = '\0';
    
}
void User::setMembershipId(string memId){
    int length = (memId.size() < 10) ? memId.size() : 9;
    for (int i = 0; i < length; ++i)
            userRecords.membershipId[i] = memId[i];
    userRecords.membershipId[length] = '\0';
}
void User::setExperience(int exp){
    userRecords.experience = exp;
}



int User::getUserId() const {
    return userRecords.userId;
}
string User::getUsername() const {
    return userRecords.username;
}
string User::getPassword() const {
    return userRecords.password;
}   
string User::getEmail() const {
    return userRecords.email;
}   
string User::getUserType() const {
    return userRecords.userType;
}
int User::getAge() const {
    return userRecords.age;
}
double User::getWeight() const {
    return userRecords.weight;
}
double User::getHeight() const {
    return userRecords.height;
}
char User::getGender() const {
    return userRecords.gender;
}
string User::getFitnessLevel() const {
    return userRecords.fitnessLevel;
}
string User::getMembershipId() const {
    return userRecords.membershipId;
} 
int User::getExperience() const {
    return userRecords.experience;
}

void User::updateProfile(fstream& userFile) {
   int userId = getUserId();
   cout<<"\nUpdating the proifle..." << endl;
   cout<<"What would you like to update?" << endl;
    cout << "1. Username"<< endl;
    cout << "2. Password"<< endl;
    cout << "3. Email"<< endl;
    cout << "4. Weight"<< endl;
    cout << "5. Height"<< endl;
    cout << "6. Fitness Level"<< endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    UserRecord user;
    userFile.clear();
    userFile.seekg((userId - 1) * sizeof(UserRecord), ios::beg);    
    userFile.read(reinterpret_cast<char*>(&userRecords), sizeof(UserRecord));
    
    
    switch(choice){
    case 1:
    {
        string newUsername;
        cout << "Enter your new username: ";
        cin >> newUsername;
        setUsername(newUsername);
        
        break;}
    case 2:{
        string newPassword;
        cout << "Enter your new password: ";
        cin >> newPassword;
        while(newPassword.size() < 8){
            cout<< "Password should contain at least 8 characters! Try again..." << endl;
            cin >> newPassword;
        }
        setPassword(newPassword);
        break;}
    case 3:{
        string newEmail;
        cout << "Enter your new email: ";
        cin >> newEmail;
        setEmail(newEmail);
        break;}
    case 4:
    {
        double newWeight;
        cout << "Enter your new weight(kg): ";
        cin >> newWeight;
        while(newWeight<0){
            cout<< "Invalid input! Your weight must be a positive number. Try again..." << endl;
            cin >> newWeight;
        }
        setWeight(newWeight);
        break;
    }
    case 5:
    {
        double newHeight;
        cout << "Enter your new height(cm): ";
        cin >> newHeight;
        while(newHeight<0){
            cout<< "Invalid input! Your height must be a positive number. Try again..." << endl;
            cin >> newHeight;
        }
        setHeight(newHeight);
        break;}
    case 6:{
        string newFitLvl;
        cout << "Enter your new fitness level(Beginner/Intermediate/Advanced): ";
        cin >> newFitLvl;
        while(newFitLvl != "Beginner" && newFitLvl !="Intermediate" && newFitLvl!= "Advanced"){
            cout << "Invalid input! Try again..." << endl;
            cin >> newFitLvl;
        }
        setFitnessLevel(newFitLvl);
        break;}
    default:
        cout << "Invalid choice! No changes were made to your profile." << endl;
        return;

    }
    UserRecord updated(getUserId(),getUserType(),getUsername(),getPassword(),getEmail(),getAge(),getWeight(),getHeight(),getGender(),getFitnessLevel(),getMembershipId(),getExperience());
    userFile.clear();
    userFile.seekg((userId - 1) * sizeof(UserRecord), ios::beg);
    userFile.write(reinterpret_cast<char*>(&updated), sizeof(UserRecord));
    cout<< "Profile updated successfully!" << endl;
}
void User::deleteProfile(fstream& userFile){
    cout << "Deleting profile..." << endl;
        UserRecord emptyUser;

    userFile.clear();

    userFile.seekp(
        (getUserId() - 1) * sizeof(UserRecord),
        ios::beg
    );

    userFile.write(
        reinterpret_cast<char*>(&emptyUser),
        sizeof(UserRecord)
    );
  

    cout << "Profile deleted.\n";
}


void Admin::displayProfile() const {
    cout << "Admin Profile:" << endl;
    cout << "User ID: " << getUserId() << endl;
    cout << "Username: " << getUsername() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Age: " << getAge() << endl;
    cout << "Gender: " << getGender() << endl;
    cout << "User Type: " << getUserType() << endl; }

void Admin::addUser(fstream& userFile) {
    Register(userFile);
}
void Admin::removeUser(fstream& userFile) {
    cout << "\nRemoving a user..." << endl;
    int id;
    cout << "Enter the User ID of the user you want to remove: ";
    cin >> id;
    UserRecord emptyUser;
    userFile.clear();
    userFile.seekp((id - 1) * sizeof(UserRecord), ios::beg);
    userFile.write(reinterpret_cast<char*>(&emptyUser), sizeof(UserRecord));
    cout << "User with ID #" << id << " has been removed." << endl;

    // Implementation for removing a user
}
void Admin::updateUser(fstream& userFile) {
    cout << "Updating a user..." << endl;
    int id;
    cout<< "Enter the User ID of the user you want to update: ";
    cin >> id;
        UserRecord user;
    if (user.userId == 0) {
        cout << "No account found with the ID " << id << "." << endl;
        return;
    }
       int userId = getUserId();
   cout<<"\nUpdating the proifle..." << endl;
   cout<<"What would you like to update?" << endl;
    cout << "1. Username"<< endl;
    cout << "2. Password"<< endl;
    cout << "3. Email"<< endl;
    cout << "4. Weight"<< endl;
    cout << "5. Height"<< endl;
    cout << "6. Fitness Level"<< endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
   
    userFile.clear();
    userFile.seekg((userId - 1) * sizeof(UserRecord), ios::beg);    
    userFile.read(reinterpret_cast<char*>(&user), sizeof(UserRecord));
    switch(choice){
    case 1:{
        string newUsername;
        cout << "Enter your new username: ";
        cin >> newUsername;
        setUsername(newUsername);
        
        break;}
    case 2:{
        string newPassword;
        cout << "Enter your new password: ";
        cin >> newPassword;
        while(newPassword.size() < 8){
            cout<< "Password should contain at least 8 characters! Try again..." << endl;
            cin >> newPassword;
        }
        setPassword(newPassword);
        break;}
    case 3:{
        string newEmail;
        cout << "Enter your new email: ";
        cin >> newEmail;
        setEmail(newEmail);
        break;}
    case 4:
    {
        double newWeight;
        cout << "Enter your new weight(kg): ";
        cin >> newWeight;
        while(newWeight<0){
            cout<< "Invalid input! Your weight must be a positive number. Try again..." << endl;
            cin >> newWeight;
        }
        setWeight(newWeight);
        break;
    }
    case 5:
    {
        double newHeight;
        cout << "Enter your new height(cm): ";
        cin >> newHeight;
        while(newHeight<0){
            cout<< "Invalid input! Your height must be a positive number. Try again..." << endl;
            cin >> newHeight;
        }
        setHeight(newHeight);
        break;}
    case 6:{
        string newFitLvl;
        cout << "Enter your new fitness level(Beginner/Intermediate/Advanced): ";
        cin >> newFitLvl;
        while(newFitLvl != "Beginner" && newFitLvl !="Intermediate" && newFitLvl!= "Advanced"){
            cout << "Invalid input! Try again..." << endl;
            cin >> newFitLvl;
        }
        setFitnessLevel(newFitLvl);
        break;}
    default:
        cout << "Invalid choice! No changes were made to your profile." << endl;
        return;

    }
    UserRecord updated(getUserId(),getUserType(),getUsername(),getPassword(),getEmail(),getAge(),getWeight(),getHeight(),getGender(),getFitnessLevel(),getMembershipId(),getExperience());

    userFile.clear();

    userFile.seekg((userId - 1) * sizeof(UserRecord), ios::beg);

    userFile.write(reinterpret_cast<char*>(&updated), sizeof(UserRecord));
    cout<< "Profile updated successfully!" << endl;
    

    // Implementation for updating a user
}
void Admin::reviewUserInfo(fstream& file) {
    file.clear();
    file.seekg(0);
    UserRecord user;
    cout << "\n";
    cout << left;
    cout << setw(10) << "User ID"
         << setw(20) << "Username"
         << setw(15) << "Type"
         << setw(25) << "Email"
         << setw(10) << "Age"
     << endl;
    cout << string(80, '-') << endl;
    while (file.read(reinterpret_cast<char*>(&user),sizeof(UserRecord))) {
        if(user.userId != 0) {
            cout << setw(10) << user.userId
                 << setw(20) << user.username
                 << setw(15) << user.userType
                 << setw(25) << user.email
                 << setw(10) << user.age
                 << endl;
        }
    }
} 

void Trainer::displayProfile() const {
    cout << "Trainer Profile:" << endl;
    cout << "User ID: " << getUserId() << endl;
    cout << "Username: " << getUsername() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Age: " << getAge() << endl;
    cout << "Gender: " << getGender() << endl;
    cout << "User Type: " << getUserType() << endl;             
    cout << "Specialization: " << specialization << endl;
    cout << "Years of Experience: " << yearsOfExperience << endl;
    cout << "Rating: " << rating << endl;
    cout << "Salary: $" << salary << endl;
}

int main(){
fstream outUserInfo("userInfo.dat", ios::in | ios::out | ios::binary);

if (!outUserInfo) {
    ofstream createFile("userInfo.dat", ios::binary);
    UserRecord emptyUser;
    for (int i = 0; i < 100; i++) {
        createFile.write(reinterpret_cast<char*>(&emptyUser), sizeof(UserRecord));
    }
    createFile.close();
    outUserInfo.open("userInfo.dat", ios::in | ios::out | ios::binary);
}
if (!outUserInfo) {
    cerr << "File could not be opened.\n";
    return 1;
}
   
int choice;
while ((choice = enterChoiceMenu()) != 3) {
    switch(choice){
    case 1:
        Register(outUserInfo);
        break;
    case 2:
        Login(outUserInfo);
        break;
    default:
        cout << "Invalid choice! Please try again." << endl;
    break;
    }
}
}
int enterChoiceMenu(){
    int choice;
    cout<< setw (30)<<"WELCOME TO THE FITNEO!  "<<endl;
    cout << setw(36)<< "1.Register" << endl;
    cout << setw(36) << "2.Login" << endl;
    cout << setw(36) << "3.Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}
void Register(fstream& outUserInfo){
    string userType, username, password, email, fitLvl, memId;
    int age, expYears, userId;
    char gender;
    double weight,height;
    cout << "Registering a new user..." << endl;
    cout << "\nEnter your User ID: ";
    cin >> userId;
    while (userId < 1 || userId > maxRecords) {
        cout << "ID must be between 1 and " << maxRecords << ". Try again... ";
        cin  >> userId;
    }

    outUserInfo.clear();
    outUserInfo.seekg((userId - 1) * sizeof(UserRecord), ios::beg);
    UserRecord user;
    
    outUserInfo.read(reinterpret_cast<char*>(&user), sizeof(UserRecord));

    while(user.userId != 0) {
        cout << "Account with the ID #" << userId << " already exists." << endl;
        cout << "Please enter a different User ID: ";
        cin >> userId;
        while (userId < 1 || userId > maxRecords) {
        cout << "ID must be between 1 and " << maxRecords << ". Try again... ";
        cin  >> userId;
        }
        outUserInfo.clear();
        outUserInfo.seekg((userId - 1) * sizeof(UserRecord), ios::beg);
        outUserInfo.read(reinterpret_cast<char*>(&user), sizeof(UserRecord));

    }
    
    

   
    cout << "\nEnter your Username: ";
    cin >> username;
    cout << "\nEnter your Password: ";
    cin >> password;
    while(password.size() < 8){
        cout<< "Password should contain at least 8 characters! Try again..." << endl;
        cin >> password;
    }
    cout << "\nEnter your Email: ";
    cin >> email;
// #include <regex>
// bool isValidEmail(const string& email) {
//     const regex pattern(R"(^[\w\.-]+@[\w\.-]+\.[a-zA-Z]{2,}$)");
//     return regex_match(email, pattern);
// }
//     while(!isValidEmail(email)){
//         cout << "Invalid email format! Try again." << endl;
//         cin >> email;
//     }

    cout << "\nEnter your Age: ";
    cin >> age;
    while(age<0 || age>100){
        cout<< "Invalid input! Your age must be between 0 and 100. Try again..." << endl;
        cin >> age;
    }
    
    cout << "\nEnter your Gender( F(Female)/ M(Male)/ O(Other) ): ";
    cin >> gender;
    while(gender != 'M' &&gender != 'F' && gender!= 'O'){
        cout<< "Invalid input! Try again..." << endl;
        cin >> gender;
    }

    cout << "\nEnter your User Type(Member/Admin/Trainer): ";
    cin >> userType;
    while(userType != "Member" && userType != "Admin" && userType != "Trainer"){
        cout << "Invalid input!  Try again... (Recommened checking for typo)." << endl;
        cin >> userType;
    }
    if(userType == "Admin"){
        fitLvl = "N/A";
        memId = "N/A";
        expYears = 0;
        weight = 0;
        height = 0;
    }
    else{

    cout << "\nEnter your Weight(kg): ";
    cin >> weight;
    while(weight<0){
        cout<< "Invalid input! Your weight must be a positive number. Try again..." << endl;
        cin >> weight;
    }
    cout << "\nEnter your Height(cm): ";
    cin >> height;
    while(height<0){
        cout<< "Invalid input! Your height must be a positive number. Try again..." << endl;
        cin >> height;
    }
    
    cout << "\nEnter your Fitness Level(Beginner/Intermediate/Advanced): ";
    cin >> fitLvl;
    while(fitLvl != "Beginner" && fitLvl !="Intermediate" && fitLvl!= "Advanced"){
        cout << "Invalid input! Try again..." << endl;
        cin >> fitLvl;
    }
    cout << "\nEnter your Membership ID: ";
    cin >> memId;
    cout << "\nEnter your Years of Experience at a gym (0 if less than 12 months): ";
    cin >> expYears;
    while(expYears > age || expYears < 0){
        cout<< "Invalid input! Try again..." << endl;
        cin >> expYears;
    }
    }
UserRecord newUser(userId, userType, username, password, email, age, weight, height, gender, fitLvl, memId, expYears);
outUserInfo.clear();
outUserInfo.seekp((userId - 1) * sizeof(UserRecord), ios::beg);
outUserInfo.write(reinterpret_cast< char*>(&newUser), sizeof(UserRecord));
cout << "Registration successful! You can now log in with your credentials!"<< endl;
}

void initializeFile(fstream& file) {
    file.clear();
    file.seekp(0);

    UserRecord emptyUser; // default user = empty record

    for (int i = 0; i < maxRecords; i++) {
        file.write(reinterpret_cast<char*>(&emptyUser), sizeof(UserRecord));
    }
}

void Login(fstream& userInfo) {
    int userId;
    string password;

    cout << "Logging in..." << endl;
    cout << "Enter your User ID: ";
    cin >> userId;
    while (userId < 1 || userId > maxRecords) {
        cout << "ID must be between 1 and " << maxRecords << ". Try again... ";
        cin  >> userId;
    }
    cout << "Enter your Password:";
    cin >> password;

    userInfo.clear();
    userInfo.seekg((userId - 1) * sizeof(UserRecord), ios::beg);
    UserRecord user;
    userInfo.read(reinterpret_cast<char*>(&user), sizeof(UserRecord));
    

    if (user.userId == 0) {
        cout << "No account found with the ID " << userId << "." << endl;
        return;
    }
    while (password != user.password) {
            cout << "Incorrect password. Please try again." << endl;
            cout << "Enter your Password: ";
            cin >> password;
    }
    if (password == user.password) {
        cout << "Login successful! Welcome, " << user.username << "!" << endl;
        if (string(user.userType) == "Admin") {
            Admin a;
            // copy fields into a
            a.setUserId(user.userId);
            a.setUsername(user.username);
            a.setEmail(user.email);
            // a.displayProfile();  // calls Admin::displayProfile()
            adminMenu(a, userInfo);
        }
        else if (string(user.userType) == "Trainer") {
            Trainer t;
            t.setUserId(user.userId);
            t.setUsername(user.username);
            t.setEmail(user.email);
            // t.displayProfile();   // calls Trainer::displayProfile()
            trainerMenu(t, userInfo);
        }else {
            User u;
            u.setUserId(user.userId);
            u.setUsername(user.username);
            u.setEmail(user.email);
            u.setAge(user.age);
            u.setGender(user.gender);
            u.setUserType(user.userType);
            u.setWeight(user.weight);
            u.setHeight(user.height);
            u.setFitnessLevel(user.fitnessLevel);
            u.setMembershipId(user.membershipId);
            u.setExperience(user.experience);
            userMenu(u, userInfo);
            // u.displayProfile();   // calls User::displayProfile()

        
    }
}
}
void userMenu(User& user, fstream& userInfo) {
    cout<<"\n1.View Profile"<<endl;
    cout<<"2.Update Profile"<<endl;
    cout<<"3.Delete Profile"<<endl;
    cout<<"4.Logout"<<endl;
    int choice;
    cout<<"Enter your choice: ";
    cin >> choice;
    switch(choice){
    case 1:
    cout << "User Profile:" << endl;
    cout << "User ID: " << user.getUserId() << endl;
    cout << "Username: " << user.getUsername() << endl;
    cout << "User Type: " << user.getUserType() << endl;
    cout << "Email: " << user.getEmail() << endl;
    cout << "Age: " << user.getAge() << endl;
    cout<< "Gender: " << user.getGender() << endl;
    cout << "Weight: " << user.getWeight() << " kg" << endl;
    cout << "Height: " << user.getHeight() << " cm" << endl;

        break;
    case 2:
    user.updateProfile(userInfo);
        break;
    
    case 3:
    user.deleteProfile(userInfo);
        break;
    case 4:
     cout << "Logging out..." << endl;
        break;
    default:
        cout << "Invalid choice! Please try again." << endl;
        break;
    }
}

void adminMenu(Admin& admin, fstream& userInfo){
    cout<<"\n1.View Profile"<<endl;
    cout<<"2.Add a new user"<<endl;
    cout<<"3.Remove a user"<<endl;
    cout<<"4.Update a user"<<endl;
    cout<<"5.Review user information"<<endl;
    cout<<"6.Logout"<<endl;
    int choice;
    cout<<"Enter your choice: ";
    cin >> choice;
    switch(choice){
    case 1:
    admin.displayProfile();
        break;
    case 2:
    admin.addUser(userInfo);
        break;
    
    case 3:
     admin.removeUser(userInfo);
        break;
    case 4:
     admin.updateUser(userInfo);
        break;
    case 5:
     admin.reviewUserInfo(userInfo);
        break;
    case 6:
     cout << "Logging out..." << endl;
        break;
    default:
        cout << "Invalid choice! Please try again." << endl;
        break;
    }
}

void trainerMenu(Trainer& trainer, fstream& userInfo) {
    cout<<"\n1.View Profile"<<endl;
    cout<<"2.Logout"<<endl;
    int choice;
    cout<<"Enter your choice: ";
    cin >> choice;
    switch(choice){
    case 1:
    trainer.displayProfile();
        break;
    
    case 2:
     cout << "Logging out..." << endl;
        break;
    default:
        cout << "Invalid choice! Please try again." << endl;
        break;
    }
}