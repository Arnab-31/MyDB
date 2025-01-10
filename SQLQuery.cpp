#include <string>
#include <map>
#include <vector>
#include "./Condition.cpp"

using namespace std;

class SQLQuery {
private:
    // Query type (e.g. "CREATE", "INSERT", "SELECT", ...)
    string queryType;
    
    // Map to hold column definitions:
    //   - key: column name
    //   - value: data type (e.g. "INT", "VARCHAR", ...)
    map<string, string> columnDefinitions;
    
    // List of values for INSERT queries
    vector<string> insertValues;
    
    // List of column names for SELECT queries
    vector<string> selectColumns;

    // One Condition object to store a condition (optional usage)
    Condition condition;

    // Table name
    string tableName;

public:
    // Constructors
    SQLQuery() = default;
    explicit SQLQuery(const string& qType) : queryType(qType) {}

    // Setters
    void setQueryType(const string& qType) {
        queryType = qType;
    }
    
    void addColumnDefinition(const string& columnName, const string& dataType) {
        columnDefinitions[columnName] = dataType;
    }
    
    void addInsertValue(const string& value) {
        insertValues.push_back(value);
    }
    
    void addSelectColumn(const string& columnName) {
        selectColumns.push_back(columnName);
    }

    // Condition setter
    void setCondition(const Condition& cond) {
        condition = cond;
    }

    void setTableName(const string& tName) {
        tableName = tName;
    }

    // Getters
    const string& getQueryType() const {
        return queryType;
    }
    
    const map<string, string>& getColumnDefinitions() const {
        return columnDefinitions;
    }
    
    const vector<string>& getInsertValues() const {
        return insertValues;
    }
    
    const vector<string>& getSelectColumns() const {
        return selectColumns;
    }

    // Condition getter
    const Condition& getCondition() const {
        return condition;
    }

    const string& getTableName() const {
        return tableName;
    }
};