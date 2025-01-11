
#include "include/parseInsertValueQuery.h"
#include "../sql/include/SQLQuery.h"
#include <string>
using namespace std;

SQLQuery parseInsertValueQuery(const string& query) {
    SQLQuery result;
    result.setQueryType("INSERT");

    // Find "INTO"
    size_t intoPos = query.find("INTO");
    if (intoPos != string::npos) {
        intoPos += 4;
        while (intoPos < query.size() && isspace(query[intoPos])) {
            intoPos++;
        }
        string tableName;
        while (intoPos < query.size() && !isspace(query[intoPos])) {
            tableName.push_back(query[intoPos++]);
        }
        result.setTableName(tableName);
    }

    // Parse values inside parentheses
    size_t start = query.find('(');
    size_t end = query.find(')');
    if (start != string::npos && end != string::npos && end > start) {
        string valuesPart = query.substr(start + 1, end - start - 1);
        size_t prev = 0, next;
        while ((next = valuesPart.find(',', prev)) != string::npos) {
            string val = valuesPart.substr(prev, next - prev);
            // ...trim spaces...
            result.addInsertValue(val);
            prev = next + 1;
        }
        // Handle last value
        string val = valuesPart.substr(prev);
        // ...trim spaces...
        result.addInsertValue(val);
    }

    return result;
}