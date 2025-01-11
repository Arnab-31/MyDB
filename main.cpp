#include <iostream>
#include <vector>
#include "parser/include/parseCreateTableQuery.h"
#include "parser/include/parseInsertValueQuery.h"
#include "sql/include/SQLQuery.h" 

using namespace std;

int main() {
    vector<string> queries{
        "CREATE TABLE example (id INT, name VARCHAR);",
        "INSERT INTO users VALUES (1,'Alice','alice@example.com');",
        "CREATE TABLE employees (empId INT, firstName VARCHAR, lastName VARCHAR);",
        "CREATE TABLE orders (orderId INT, product VARCHAR, quantity INT);",
        "CREATE TABLE inventory (sku VARCHAR, qty INT, location VARCHAR);",
        "CREATE TABLE customers (custId INT, fullName VARCHAR, email VARCHAR, phone VARCHAR);"
    };

    for (auto &q : queries) {
        SQLQuery sqlQ;
        if (q.rfind("CREATE", 0) == 0) {
            sqlQ = parseCreateTableQuery(q);
        } else if (q.rfind("INSERT", 0) == 0) {
            sqlQ = parseInsertValueQuery(q);
        }
        cout << "Query: " << q << endl;
        cout << "Query Type: " << sqlQ.getQueryType() << endl;
        cout << "Table Name: " << sqlQ.getTableName() << endl;

        if (sqlQ.getQueryType() == "CREATE") {
            const auto& cols = sqlQ.getColumnDefinitions();
            for (auto& kv : cols) {
                cout << "Column: " << kv.first << ", Type: " << kv.second << endl;
            }
        } else if (sqlQ.getQueryType() == "INSERT") {
            const auto& values = sqlQ.getInsertValues();
            for (const auto& val : values) {
                cout << "Value: " << val << endl;
            }
        }
        cout << "------------------------" << endl;
    }

    return 0;
}