#include <iostream>
#include <vector>
#include "parser/include/parseCreateTableQuery.h"
#include "parser/include/parseInsertValueQuery.h"
#include "parser/include/parseSelectQuery.h"
#include "parser/include/parseUpdateQuery.h"
#include "sql/include/SQLQuery.h" 
#include "./sql/include/Condition.h" 
#include "parser/include/parseDeleteQuery.h"
#include "parser/include/parseDropTableQuery.h"
#include "sql/include/createTableCSV.h"
#include "sql/include/insertTableCSV.h"
#include "sql/include/selectTableCSV.h"
#include "sql/include/updateTableCSV.h"

using namespace std;

int main() {
    vector<string> queries{
        // "CREATE TABLE employees (empId INT, firstName VARCHAR, lastName VARCHAR);",
        // "INSERT INTO employees VALUES (1,'Alice','alice@example.com');",
        // "INSERT INTO employees VALUES (2,'Alice','alice@example.com');",
        // "INSERT INTO employees VALUES (3,'Alice','alice@example.com');",
        // "SELECT name FROM employees;",
        //"CREATE TABLE employees (empId INT, firstName VARCHAR, lastName VARCHAR);",
        //"CREATE TABLE orders (orderId INT, product VARCHAR, quantity INT);",
        // "CREATE TABLE inventory (sku VARCHAR, qty INT, location VARCHAR);",
        // "CREATE TABLE customers (custId INT, fullName VARCHAR, email VARCHAR, phone VARCHAR);",
        // "SELECT firstName, lastName FROM employees WHERE firstName = 'Alice';",
        // "SELECT name FROM employees;",
         "UPDATE employees SET firstName = 'Raj2';",
        // "DELETE FROM users WHERE id = 1;", // Existing DELETE query
        // "DROP TABLE example;" // New DROP TABLE query for testing
        //"CREATE TABLE example (id INT, name VARCHAR);",
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
        } else if (q.rfind("DROP", 0) == 0) { // Handling DROP TABLE queries
            sqlQ = parseDropTableQuery(q);
        }
        cout << "Query: " << q << endl;
        cout << "Query Type: " << sqlQ.getQueryType() << endl;
        cout << "Table Name: " << sqlQ.getTableName() << endl;

        if (sqlQ.getQueryType() == "CREATE") {
            createTableCSV(sqlQ);
        } else if (sqlQ.getQueryType() == "INSERT") {
            insertIntoTableCSV(sqlQ);
        } else if (sqlQ.getQueryType() == "SELECT") {
            selectFromTableCSV(sqlQ);
        } else if (sqlQ.getQueryType() == "UPDATE") {
            updateTableCSV(sqlQ);
        } else if (sqlQ.getQueryType() == "DELETE") { // Handling DELETE query output
            if (!sqlQ.getWhereCondition().getColumnName().empty()) {
                const Condition &cond = sqlQ.getWhereCondition();
                cout << "WHERE Clause: " << cond.getColumnName() << " " << cond.getConditionOperator() << " " << cond.getValue() << endl;
            }
        } else if (sqlQ.getQueryType() == "DROP") { // Handling DROP TABLE query output
            // No additional information to display for DROP
        }
    }

    return 0;
}
