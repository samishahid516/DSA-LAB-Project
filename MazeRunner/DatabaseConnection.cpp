#include "DatabaseConnection.h"

DatabaseConnection::DatabaseConnection()
    : sqlEnvHandle(nullptr), sqlConnHandle(nullptr), sqlStmtHandle(nullptr)
{
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle) != SQL_SUCCESS)
    {
        cerr << "Unable to allocate environment handle." << endl;
        exit(EXIT_FAILURE);
    }

    if (SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0) != SQL_SUCCESS)
    {
        cerr << "Unable to set ODBC version." << endl;
        exit(EXIT_FAILURE);
    }

    if (SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle) != SQL_SUCCESS)
    {
        cerr << "Unable to allocate connection handle." << endl;
        exit(EXIT_FAILURE);
    }
}

DatabaseConnection::~DatabaseConnection()
{
    disconnect();
}

bool DatabaseConnection::connect()
{
    SQLWCHAR connectionString[] = L"Driver={SQL Server};Server=DESKTOP-U5CTDF0;Database=UserDatabase;Trusted_Connection=yes;";
    SQLWCHAR retConString[1024];

    switch (SQLDriverConnectW(sqlConnHandle, nullptr, connectionString, SQL_NTS, retConString, 1024, nullptr, SQL_DRIVER_NOPROMPT))
    {
    case SQL_SUCCESS:
    case SQL_SUCCESS_WITH_INFO:
        wcout << L"Successfully connected to the database!" << endl;
        return true;
    case SQL_INVALID_HANDLE:
    case SQL_ERROR:
        showSQLError(SQL_HANDLE_DBC, sqlConnHandle);
        return false;
    default:
        wcerr << L"Unexpected connection return." << endl;
        return false;
    }
}

bool DatabaseConnection::executeQuery(const wstring& query)
{
    if (sqlStmtHandle)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        sqlStmtHandle = nullptr;
    }

    if (SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle) != SQL_SUCCESS)
    {
        cerr << "Unable to allocate statement handle." << endl;
        return false;
    }

    if (SQLExecDirectW(sqlStmtHandle, (SQLWCHAR*)query.c_str(), SQL_NTS) != SQL_SUCCESS)
    {
        showSQLError(SQL_HANDLE_STMT, sqlStmtHandle);
        return false;
    }

    return true;
}

bool DatabaseConnection::fetchRow(vector<wstring>& row)
{
    SQLRETURN retCode;
    SQLWCHAR buffer[256];

    while ((retCode = SQLFetch(sqlStmtHandle)) == SQL_SUCCESS)
    {
        for (int i = 1;; i++) {
            if (SQLGetData(sqlStmtHandle, i, SQL_C_WCHAR, buffer, sizeof(buffer), nullptr) == SQL_SUCCESS) {
                row.push_back(wstring(buffer));
            }
            else {
                break;
            }
        }
    }

    return !row.empty();
}

void DatabaseConnection::disconnect()
{
    if (sqlStmtHandle) SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    if (sqlConnHandle)
    {
        SQLDisconnect(sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    }
    if (sqlEnvHandle) SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);

    cout << "Disconnected from the database." << endl;
}

void DatabaseConnection::bindInt(int paramIndex, int value) 
{
    SQLBindParameter(sqlStmtHandle, paramIndex, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &value, 0, nullptr);
}

void DatabaseConnection::bindText(int paramIndex, const char* value) 
{
    SQLBindParameter(sqlStmtHandle, paramIndex, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_LONGVARCHAR, 0, 0, (SQLCHAR*)value, 0, nullptr);
}

void DatabaseConnection::showSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
    SQLWCHAR sqlState[1024];
    SQLWCHAR message[1024];

    if (SQLGetDiagRecW(handleType, handle, 1, sqlState, nullptr, message, 1024, nullptr) == SQL_SUCCESS)
    {
        wcerr << L"SQL Error: " << message << L" (SQL State: " << sqlState << L")" << endl;
    }
}
