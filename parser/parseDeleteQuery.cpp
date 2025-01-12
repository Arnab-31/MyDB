
#include "include/parseDeleteQuery.h"
#include "../sql/include/Condition.h"
#include <string>
#include <cctype>

SQLQuery parseDeleteQuery(const std::string &query) {
    SQLQuery result;
    result.setQueryType("DELETE");

    // Extract table name after "DELETE FROM"
    size_t deletePos = query.find("DELETE FROM");
    if (deletePos != std::string::npos) {
        deletePos += 11; // Length of "DELETE FROM"
        // Trim spaces
        size_t first = query.find_first_not_of(" \t", deletePos);
        size_t nextSpace = query.find_first_of(" \t;", first);
        if (first != std::string::npos) {
            std::string tableName = query.substr(first, nextSpace - first);
            result.setTableName(tableName);
        }
    }

    // Extract WHERE clause if present
    size_t wherePos = query.find("WHERE");
    if (wherePos != std::string::npos) {
        std::string wherePart = query.substr(wherePos + 5);
        // Trim spaces and semicolon
        size_t first = wherePart.find_first_not_of(" \t");
        size_t last = wherePart.find_last_not_of(" \t;");
        if (first != std::string::npos && last != std::string::npos) {
            wherePart = wherePart.substr(first, last - first + 1);
            // Simple condition parsing (e.g., "id = 1")
            size_t opPos = wherePart.find('=');
            if (opPos != std::string::npos) {
                std::string colName = wherePart.substr(0, opPos);
                std::string value = wherePart.substr(opPos + 1);
                // Trim spaces
                size_t colFirst = colName.find_first_not_of(" \t");
                size_t colLast = colName.find_last_not_of(" \t");
                if (colFirst != std::string::npos && colLast != std::string::npos) {
                    colName = colName.substr(colFirst, colLast - colFirst + 1);
                }
                size_t valFirst = value.find_first_not_of(" \t'");
                size_t valLast = value.find_last_not_of(" \t';");
                if (valFirst != std::string::npos && valLast != std::string::npos) {
                    value = value.substr(valFirst, valLast - valFirst + 1);
                }
                Condition cond(colName, "=", value);
                result.setWhereCondition(cond);
            }
        }
    }

    return result;
}