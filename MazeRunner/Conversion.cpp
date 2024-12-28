#include "Conversion.h"
#include <locale>
#include <codecvt>
#include <sstream>

wstring stringToWString(const string& str)
{
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.from_bytes(str);
}

string wstringToString(const wstring& wstr)
{
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(wstr);
}

vector<int> stringToVector(const string& str)
{
    vector<int> result;
    stringstream ss(str);
    string temp;
    while (getline(ss, temp, ','))
    {
        result.push_back(stoi(temp));
    }
    return result;
}

string vectorToString(const vector<int>& vec)
{
    string result;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        result += to_string(vec[i]);
        if (i != vec.size() - 1)
        {
            result += ",";
        }
    }
    return result;
}
