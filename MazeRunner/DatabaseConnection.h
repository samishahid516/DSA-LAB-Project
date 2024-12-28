#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <locale>
#include <codecvt>

using namespace std;

class DatabaseConnection
{
private:
    SQLHANDLE sqlEnvHandle;
    SQLHANDLE sqlConnHandle;
    SQLHANDLE sqlStmtHandle;

public:
    DatabaseConnection();
    ~DatabaseConnection();

    bool connect();
    bool executeQuery(const wstring& query);
    bool fetchRow(vector<wstring>& row);
    void disconnect();
    void bindInt(int paramIndex, int value);
    void bindText(int paramIndex, const char* value);
    void showSQLError(unsigned int handleType, const SQLHANDLE& handle);
};

#endif // DATABASE_CONNECTION_H
