#include "include/parseCreateTableQuery.h"
#include "../sql/include/SQLQuery.h"
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

static void trimSpaces(std::string &s) {
    while (!s.empty() && std::isspace((unsigned char)s.front())) s.erase(s.begin());
    while (!s.empty() && std::isspace((unsigned char)s.back())) s.pop_back();
}

SQLQuery parseCreateTableQuery(const string& query) {
    SQLQuery result;
    result.setQueryType("CREATE");

    // Find table name
    size_t pos = query.find("TABLE");
    if (pos != string::npos) {
        pos += 5; 
        while (pos < query.size() && isspace(query[pos])) {
            pos++;
        }
        string tableName;
        while (pos < query.size() && !isspace(query[pos]) && query[pos] != '(') {
            tableName.push_back(query[pos++]);
        }
        // Assume tableName is valid
        result.setTableName(tableName);
    }

    // Find columns substring
    size_t start = query.find('(');
    size_t end = query.find(')');
    if (start != string::npos && end != string::npos && end > start) {
        string columnsPart = query.substr(start + 1, end - start - 1);
        size_t prev = 0, next;
        while ((next = columnsPart.find(',', prev)) != string::npos) {
            string colDef = columnsPart.substr(prev, next - prev);
            // Trim leading/trailing spaces
            trimSpaces(colDef);

            size_t spacePos = colDef.find(' ');
            if (spacePos != string::npos) {
                string colName = colDef.substr(0, spacePos);
                string colType = colDef.substr(spacePos + 1);
                trimSpaces(colName);
                trimSpaces(colType);
                result.addColumnDefinition(colName, colType);
            }
            prev = next + 1;
        }

        // Handle the last column
        string colDef = columnsPart.substr(prev);
        trimSpaces(colDef);

        size_t spacePos = colDef.find(' ');
        if (spacePos != string::npos) {
            string colName = colDef.substr(0, spacePos);
            string colType = colDef.substr(spacePos + 1);
            trimSpaces(colName);
            trimSpaces(colType);
            result.addColumnDefinition(colName, colType);
        }
    }

    return result;
}