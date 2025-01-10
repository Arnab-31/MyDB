#include <iostream>
#include "parseCreateTableQuery.cpp"

using namespace std;

int main() {
    vector<string> queries{
        "CREATE TABLE example (id INT, name VARCHAR);",
        "CREATE TABLE employees (empId INT, firstName VARCHAR, lastName VARCHAR);",
        "CREATE TABLE orders (orderId INT, product VARCHAR, quantity INT);",
        "CREATE TABLE inventory (sku VARCHAR, qty INT, location VARCHAR);",
        "CREATE TABLE customers (custId INT, fullName VARCHAR, email VARCHAR, phone VARCHAR);"
    };

    for (auto& q : queries) {
        SQLQuery sqlQ = parseCreateTableQuery(q);
        cout << "Query: " << q << endl;
        cout << "Query Type: " << sqlQ.getQueryType() << endl;
        cout << "Table Name: " << sqlQ.getTableName() << endl;
        const auto& cols = sqlQ.getColumnDefinitions();
        for (auto& kv : cols) {
            cout << "Column: " << kv.first << ", Type: " << kv.second << endl;
        }
        cout << "------------------------" << endl;
    }

    return 0;
}