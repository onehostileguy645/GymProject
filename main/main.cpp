#include <fstream>
#include "membership.cpp"
#include "progress.cpp"
#include "user.cpp"
#include "diet.cpp"
#include "recommendation.cpp"
#include "workout.cpp"

using namespace std;


int main(){
    fstream userFile("users.dat", ios::in | ios::out | ios::binary);
    if (!userFile) {
        cout << "Could not open user file. Creating new one.\n";
        userFile.open("users.dat", ios::out | ios::binary);
        userFile.close();
        userFile.open("users.dat", ios::in | ios::out | ios::binary);
    }

    fstream memberFile("memberships.dat", ios::in | ios::out | ios::binary);
    if (!memberFile) {
        cout << "Could not open membership file. Creating new one.\n";
        memberFile.open("memberships.dat", ios::out | ios::binary);
        memberFile.close();
        memberFile.open("memberships.dat", ios::in | ios::out | ios::binary);
    }

    fstream progressFile("progress.dat", ios::in | ios::out | ios::binary);
    if (!progressFile) {
        cout << "Could not open progress file. Creating new one.\n";
        progressFile.open("progress.dat", ios::out | ios::binary);
        progressFile.close();
        progressFile.open("progress.dat", ios::in | ios::out | ios::binary);
    }

    cout << "Welcome to the Fitnio Management System!\n";
    cout<< "Please log in to continue.\n";
    //user login and registration logic here


    int choice;
    do{
        cout << "--------- Main Menu ---------\n";
        cout << "1. Membership\n";
        cout << "2. Your progress\n";
        cout << "3. Workouts\n";
        cout << "4. Diet\n";
        cout << "5. Recommendations\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;


        switch(choice){
            case 1: 
            membershipMenu(memberFile, userFile, userId); 
            break;
            
            case 2: 
            progressMenu(progressFile, userFile, userId); 
            break;
            
            case 3: ; break;
            
            case 4: ; break;
            
            case 5: ; break;
            
            case 6: 
            cout << "Exiting...\n"; break;
            
            default: 
            cout << "Invalid choice. Please try again.\n";
        }
    }while(choice != 6);


    userFile.close();
    memberFile.close();
    progressFile.close();
    return 0;
}