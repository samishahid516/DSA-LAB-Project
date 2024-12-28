#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "DatabaseConnection.h"
#include "Conversion.h"

using namespace std;

class User
{
private:
    string username;
    string password;
    int accountLevel;
    int score;
    vector<int> completedLevels;
    vector<int> unlockedSkins;

public:
    User();
    void setUsername(const string& username);
    void setPassword(const string& password);
    const string& getUsername() const;
    int getAccountLevel() const;
    int getScore() const;
    const vector<int>& getCompletedLevels() const;
    const vector<int>& getUnlockedSkins() const;
    bool registerUser(DatabaseConnection& db);
    bool loginUser(DatabaseConnection& db);
    void displayAccountDetails();
    bool loadCompletedLevels(DatabaseConnection& db);
    bool saveCompletedLevels(DatabaseConnection& db, const vector<int>& completedLevels);
};

#endif // USER_H
