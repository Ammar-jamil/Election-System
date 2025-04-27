#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
class User
{
private:
    char username[50];
    char password[50];

public:  void registerUser() {
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ofstream outFile("users.txt", ios::app);
    if (outFile.is_open()) {
        outFile << username << " " << password << endl;
        cout << "Registration successful!" << endl;
        outFile.close();
    }
    else {
        cout << "Error opening file for registration!" << endl;
    }
}


      bool loginUser() {
          string enteredUsername, enteredPassword;
          cout << "Enter your username: ";
          cin >> enteredUsername;
          cout << "Enter your password: ";
          cin >> enteredPassword;
          ifstream inFile("users.txt");
          if (inFile.is_open()) {
              string username, password;
              while (inFile >> username >> password) {
                  if (username == enteredUsername && password == enteredPassword) {
                      cout << "Login successful. Welcome " << enteredUsername << "!" << endl;
                      cout << "Select election type:" << endl << "1.Local" << endl << "2.National"123;
                      inFile.close();
                      return true;
                  }
              }

              cout << "Invalid username or password." << endl;
              inFile.close();
              return false;
          }
          else {
              cout << "Error opening file for login!" << endl;
              return false;
          }
      }
};

int main() {
    User user;
    int choice;

    while (true) {
        cout << "1. Register\n2. Login\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            user.registerUser();
        }
        else if (choice == 2) {
            user.loginUser();
        }
        else if (choice == 3) {
            break;

        }
        else {
            cout << "Invalid choice. Please try again.\n";
            cout << "HEllo";
        }
    }
    return 0;
}
