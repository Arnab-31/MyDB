#include <iostream>
#include <vector>
#include "parser/include/parseCreateTableQuery.h"
#include "parser/include/parseInsertValueQuery.h"
#include "parser/include/parseSelectQuery.h"
#include "parser/include/parseUpdateQuery.h"
#include "sql/include/SQLQuery.h" 
#include "./sql/include/Condition.h" 
#include "parser/include/parseDeleteQuery.h"

using namespace std;

int main() {
    vector<string> queries{
        "CREATE TABLE example (id INT, name VARCHAR);",
        "INSERT INTO users VALUES (1,'Alice','alice@example.com');",
        "CREATE TABLE employees (empId INT, firstName VARCHAR, lastName VARCHAR);",
        "CREATE TABLE orders (orderId INT, product VARCHAR, quantity INT);",
        "CREATE TABLE inventory (sku VARCHAR, qty INT, location VARCHAR);",
        "CREATE TABLE customers (custId INT, fullName VARCHAR, email VARCHAR, phone VARCHAR);",
        "SELECT name, email FROM employees WHERE id = 100;",
        "SELECT name FROM employees;",
        "UPDATE users SET email = 'newalice@example.com', name = 'Raj' WHERE id = 1;",
        "DELETE FROM users WHERE id = 1;" // New DELETE query for testing
    };

    for (auto &q : queries) {
        SQLQuery sqlQ;
        if (q.rfind("CREATE", 0) == 0) {
            sqlQ = parseCreateTableQuery(q);
        } else if (q.rfind("INSERT", 0) == 0) {
            sqlQ = parseInsertValueQuery(q);
        } else if (q.rfind("SELECT", 0) == 0) {
            sqlQ = parseSelectQuery(q);
        } else if (q.rfind("UPDATE", 0) == 0) {
            sqlQ = parseUpdateQuery(q);
        } else if (q.rfind("DELETE", 0) == 0) { // Handling DELETE queries
            sqlQ = parseDeleteQuery(q);
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
        } else if (sqlQ.getQueryType() == "SELECT") {
            const auto &cols = sqlQ.getSelectValues();
            cout << "Selected Columns: ";
            for (const auto &c : cols) {
                cout << c << " ";
            }
            cout << endl;
            if (!sqlQ.getWhereCondition().getColumnName().empty()) {
                const Condition &cond = sqlQ.getWhereCondition();
                cout << "WHERE Clause: " << cond.getColumnName() << " " << cond.getConditionOperator() << " " << cond.getValue() << endl;
            }
        } else if (sqlQ.getQueryType() == "UPDATE") {
            const auto &updates = sqlQ.getUpdateValues();
            cout << "Update Values:" << endl;
            for (const auto &pair : updates) {
                cout << "  " << pair.first << " = " << pair.second << endl;
            }
            if (!sqlQ.getWhereCondition().getColumnName().empty()) {
                const Condition &cond = sqlQ.getWhereCondition();
                cout << "WHERE Clause: " << cond.getColumnName() << " " << cond.getConditionOperator() << " " << cond.getValue() << endl;
            }
        } else if (sqlQ.getQueryType() == "DELETE") { // Handling DELETE query output
            if (!sqlQ.getWhereCondition().getColumnName().empty()) {
                const Condition &cond = sqlQ.getWhereCondition();
                cout << "WHERE Clause: " << cond.getColumnName() << " " << cond.getConditionOperator() << " " << cond.getValue() << endl;
            }
        }
        cout << "------------------------" << endl;
    }

    return 0;
}
