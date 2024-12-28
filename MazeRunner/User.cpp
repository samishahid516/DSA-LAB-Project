#include "User.h"

User::User() : accountLevel(1), score(0) {}

void User::setUsername(const string& username) 
{
    this->username = username;
}
void User::setPassword(const string& password) 
{
    this->password = password;
}

const string& User::getUsername() const 
{
    return username;
}
int User::getAccountLevel() const 
{
    return accountLevel;
}
int User::getScore() const 
{
    return score;
}
const vector<int>& User::getCompletedLevels() const 
{
    return completedLevels;
}
const vector<int>& User::getUnlockedSkins() const 
{
    return unlockedSkins;
}

bool User::registerUser(DatabaseConnection& db)
{
    string completedLevelsStr = vectorToString(completedLevels);
    string unlockedSkinsStr = vectorToString(unlockedSkins);

    wstring usernameW = stringToWString(username);
    wstring passwordW = stringToWString(password);
    wstring completedLevelsW = stringToWString(completedLevelsStr);
    wstring unlockedSkinsW = stringToWString(unlockedSkinsStr);

    wstring query = L"INSERT INTO Users (Username, Password, AccountLevel, Score, CompletedLevels, UnlockedSkins) "
        L"VALUES ('" + usernameW + L"', '" + passwordW + L"', " + to_wstring(accountLevel) + L", " + to_wstring(score) +
        L", '" + completedLevelsW + L"', '" + unlockedSkinsW + L"');";

    return db.executeQuery(query);
}

bool User::loginUser(DatabaseConnection& db)
{
    wstring usernameW = stringToWString(username);
    wstring passwordW = stringToWString(password);

    wstring query = L"SELECT * FROM Users WHERE Username = '" + usernameW + L"' AND Password = '" + passwordW + L"';";

    vector<wstring> row;
    if (db.executeQuery(query)) 
    {
        if (db.fetchRow(row)) 
        {
            accountLevel = stoi(string(row[3].begin(), row[3].end()));
            score = stoi(string(row[4].begin(), row[4].end()));
            completedLevels = stringToVector(string(row[5].begin(), row[5].end()));
            unlockedSkins = stringToVector(string(row[6].begin(), row[6].end()));
            return true;
        }
    }
    return false;
}

void User::displayAccountDetails()
{
    cout << "Username: " << username << endl;
    cout << "Account Level: " << accountLevel << endl;
    cout << "Score: " << score << endl;

    cout << "Completed Levels: ";
    for (int level : completedLevels)
    {
        cout << level << " ";
    }
    cout << endl;

    cout << "Unlocked Skins: ";
    for (int skin : unlockedSkins)
    {
        cout << skin << " ";
    }
    cout << endl;
}

bool User::loadCompletedLevels(DatabaseConnection& db)
{
    string query = "SELECT CompletedLevels FROM Users WHERE Username = '" + username + "'";
    vector<wstring> row;

    if (db.fetchRow(row))
    {
        stringstream ss(wstringToString(row[0]));
        string level;
        while (getline(ss, level, ',')) {
            completedLevels.push_back(stoi(level));
        }
        return true;
    }
    return false;
}

bool User::saveCompletedLevels(DatabaseConnection& db, const vector<int>& completedLevels)
{
    stringstream ss;
    for (int level : completedLevels)
    {
        ss << level << ",";
    }
    string completedLevelsStr = ss.str();
    completedLevelsStr.pop_back();

    string query = "UPDATE Users SET CompletedLevels = '" + completedLevelsStr + "' WHERE Username = '" + username + "'";

    return db.executeQuery(stringToWString(query));
}
