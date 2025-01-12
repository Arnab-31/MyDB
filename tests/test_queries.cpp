#include <gtest/gtest.h>
#include "../sql/include/SQLQuery.h"
#include "../parser/include/parseCreateTableQuery.h"
#include "../parser/include/parseInsertValueQuery.h"
#include <gtest/gtest.h>
#include "../sql/include/SQLQuery.h"
#include "../parser/include/parseCreateTableQuery.h"
#include "../parser/include/parseInsertValueQuery.h"

TEST(ParseCreateTableQueryTest, ValidQueries) {
    std::vector<std::string> queries{
        "CREATE TABLE example (id INT, name VARCHAR);",
        "CREATE TABLE employees (empId INT, firstName VARCHAR, lastName VARCHAR);",
        "CREATE TABLE orders (orderId INT, product VARCHAR, quantity INT);",
        "CREATE TABLE inventory (sku VARCHAR, qty INT, location VARCHAR);",
        "CREATE TABLE customers (custId INT, fullName VARCHAR, email VARCHAR, phone VARCHAR);"
    };

    for (const auto& q : queries) {
        SQLQuery sqlQ = parseCreateTableQuery(q);
        EXPECT_EQ(sqlQ.getQueryType(), "CREATE") << "Failed query: " << q;
        EXPECT_FALSE(sqlQ.getTableName().empty()) << "Failed query: " << q;
        EXPECT_FALSE(sqlQ.getColumnDefinitions().empty()) << "Failed query: " << q;
    }
}

TEST(ParseInsertValueQueryTest, ValidQueries) {
    std::vector<std::string> queries{
        "INSERT INTO users VALUES (1, 'Alice', 'alice@example.com');",
        "INSERT INTO employees VALUES (2, 'Bob', 'bob@example.com');",
        "INSERT INTO orders VALUES (3, 'Product1', 10);",
        "INSERT INTO inventory VALUES ('SKU123', 50, 'Warehouse1');",
        "INSERT INTO customers VALUES (4, 'Charlie', 'charlie@example.com', '123-456-7890');"
    };

    for (const auto& q : queries) {
        SQLQuery sqlQ = parseInsertValueQuery(q);
        EXPECT_EQ(sqlQ.getQueryType(), "INSERT") << "Failed query: " << q;
        EXPECT_FALSE(sqlQ.getTableName().empty()) << "Failed query: " << q;
        EXPECT_FALSE(sqlQ.getInsertValues().empty()) << "Failed query: " << q;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
