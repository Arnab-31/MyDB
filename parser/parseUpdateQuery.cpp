#include "include/parseUpdateQuery.h"
#include "../sql/include/Condition.h"
#include <string>
#include <cctype>

// ...existing code...

SQLQuery parseUpdateQuery(const std::string &query) {
    SQLQuery result;
    result.setQueryType("UPDATE");

    // Extract table name after "UPDATE" and before "SET"
    size_t updatePos = query.find("UPDATE");
    size_t setPos = query.find("SET");
    if (updatePos != std::string::npos && setPos != std::string::npos) {
        std::string tablePart = query.substr(updatePos + 6, setPos - (updatePos + 6));
        // Trim spaces
        size_t first = tablePart.find_first_not_of(" \t");
        size_t last = tablePart.find_last_not_of(" \t");
        if (first != std::string::npos && last != std::string::npos) {
            tablePart = tablePart.substr(first, last - first + 1);
            result.setTableName(tablePart);
        }
    }

    // Extract SET clause
    size_t wherePos = query.find("WHERE");
    std::string setPart;
    if (setPos != std::string::npos) {
        if (wherePos != std::string::npos) {
            setPart = query.substr(setPos + 3, wherePos - (setPos + 3));
        } else {
            setPart = query.substr(setPos + 3);
        }
        // Trim spaces
        size_t first = setPart.find_first_not_of(" \t");
        size_t last = setPart.find_last_not_of(" \t;");
        if (first != std::string::npos && last != std::string::npos) {
            setPart = setPart.substr(first, last - first + 1);
            // Split by comma and parse column-value pairs
            size_t start = 0, commaPos;
            while ((commaPos = setPart.find(',', start)) != std::string::npos) {
                std::string pair = setPart.substr(start, commaPos - start);
                size_t eqPos = pair.find('=');
                if (eqPos != std::string::npos) {
                    std::string col = pair.substr(0, eqPos);
                    std::string val = pair.substr(eqPos + 1);
                    // Trim spaces and quotes
                    size_t colFirst = col.find_first_not_of(" \t");
                    size_t colLast = col.find_last_not_of(" \t");
                    if (colFirst != std::string::npos && colLast != std::string::npos) {
                        col = col.substr(colFirst, colLast - colFirst + 1);
                    }
                    size_t valFirst = val.find_first_not_of(" \t'");
                    size_t valLast = val.find_last_not_of(" \t';");
                    if (valFirst != std::string::npos && valLast != std::string::npos) {
                        val = val.substr(valFirst, valLast - valFirst + 1);
                    }
                    result.addUpdateValue(col, val);
                }
                start = commaPos + 1;
            }
            // Handle last pair
            std::string pair = setPart.substr(start);
            size_t eqPos = pair.find('=');
            if (eqPos != std::string::npos) {
                std::string col = pair.substr(0, eqPos);
                std::string val = pair.substr(eqPos + 1);
                // Trim spaces and quotes
                size_t colFirst = col.find_first_not_of(" \t");
                size_t colLast = col.find_last_not_of(" \t");
                if (colFirst != std::string::npos && colLast != std::string::npos) {
                    col = col.substr(colFirst, colLast - colFirst + 1);
                }
                size_t valFirst = val.find_first_not_of(" \t'");
                size_t valLast = val.find_last_not_of(" \t';");
                if (valFirst != std::string::npos && valLast != std::string::npos) {
                    val = val.substr(valFirst, valLast - valFirst + 1);
                }
                result.addUpdateValue(col, val);
            }
        }
    }

    // Optional WHERE clause
    if (wherePos != std::string::npos) {
        std::string wherePart = query.substr(wherePos + 5);
        // Trim spaces and semicolon
        size_t first = wherePart.find_first_not_of(" \t");
        size_t last = wherePart.find_last_not_of(" \t;");
        if (first != std::string::npos && last != std::string::npos) {
            wherePart = wherePart.substr(first, last - first + 1);
        }
        // Simple condition parsing (e.g., "id = 1")
        size_t opPos = wherePart.find('=');
        if (opPos != std::string::npos) {
            std::string colName = wherePart.substr(0, opPos);
            std::string value = wherePart.substr(opPos + 1);
            // Trim spaces and quotes
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

    return result;
}