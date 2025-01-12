#include "include/parseSelectQuery.h"
#include "../sql/include/SQLQuery.h"
#include <string>
#include <cctype>

SQLQuery parseSelectQuery(const std::string &query) {
    SQLQuery result;
    result.setQueryType("SELECT");

    // Extract columns after "SELECT" and before "FROM"
    size_t selectPos = query.find("SELECT");
    size_t fromPos = query.find("FROM");
    if (selectPos != std::string::npos && fromPos != std::string::npos) {
        std::string columnsPart = query.substr(selectPos + 6, fromPos - (selectPos + 6));
        // Trim and split by comma
        size_t start = 0, commaPos;
        while ((commaPos = columnsPart.find(',', start)) != std::string::npos) {
            std::string col = columnsPart.substr(start, commaPos - start);
            // Trim spaces
            size_t first = col.find_first_not_of(" \t");
            size_t last = col.find_last_not_of(" \t");
            if (first != std::string::npos && last != std::string::npos) {
                col = col.substr(first, last - first + 1);
                result.addSelectValue(col);
            }
            start = commaPos + 1;
        }
        // Last column
        std::string col = columnsPart.substr(start);
        size_t first = col.find_first_not_of(" \t");
        size_t last = col.find_last_not_of(" \t");
        if (first != std::string::npos && last != std::string::npos) {
            col = col.substr(first, last - first + 1);
            result.addSelectValue(col);
        }
    }

    // Extract table name after "FROM" and before "WHERE" or end
    size_t wherePos = query.find("WHERE");
    std::string tablePart;
    if (fromPos != std::string::npos) {
        if (wherePos != std::string::npos) {
            tablePart = query.substr(fromPos + 4, wherePos - (fromPos + 4));
        } else {
            tablePart = query.substr(fromPos + 4);
        }
        // Trim spaces
        size_t first = tablePart.find_first_not_of(" \t");
        size_t last = tablePart.find_last_not_of(" \t");
        if (first != std::string::npos && last != std::string::npos) {
            tablePart = tablePart.substr(first, last - first + 1);
            // Remove trailing semicolon if present
            if (!tablePart.empty() && tablePart.back() == ';') {
                tablePart.pop_back();
            }
            result.setTableName(tablePart);
        }
    }

    // Optional WHERE clause
    if (wherePos != std::string::npos) {
        std::string wherePart = query.substr(wherePos + 5);
        // Trim spaces
        size_t first = wherePart.find_first_not_of(" \t");
        size_t last = wherePart.find_last_not_of(" \t");
        if (first != std::string::npos && last != std::string::npos) {
            wherePart = wherePart.substr(first, last - first + 1);
        }
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
            size_t valFirst = value.find_first_not_of(" \t");
            size_t valLast = value.find_last_not_of(" \t");
            if (valFirst != std::string::npos && valLast != std::string::npos) {
                value = value.substr(valFirst, valLast - valFirst + 1);
            }
            Condition cond(colName, "=", value);
            result.setWhereCondition(cond);
        }
    }

    return result;
}