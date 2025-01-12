
#include "include/parseDropTableQuery.h"
#include "../sql/include/Condition.h"
#include <string>
#include <cctype>

SQLQuery parseDropTableQuery(const std::string &query) {
    SQLQuery result;
    result.setQueryType("DROP");

    // Extract table name after "DROP TABLE"
    size_t dropPos = query.find("DROP TABLE");
    if (dropPos != std::string::npos) {
        dropPos += 10; // Length of "DROP TABLE"
        // Trim spaces
        size_t first = query.find_first_not_of(" \t", dropPos);
        size_t nextSpace = query.find_first_of(" \t;", first);
        if (first != std::string::npos) {
            std::string tableName = query.substr(first, nextSpace - first);
            result.setTableName(tableName);
        }
    }

    return result;
}