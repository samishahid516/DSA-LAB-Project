#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>
#include <vector>

using namespace std;

wstring stringToWString(const string& str);
string wstringToString(const wstring& wstr);
vector<int> stringToVector(const string& str);
string vectorToString(const vector<int>& vec);

#endif // STRING_UTILS_H
