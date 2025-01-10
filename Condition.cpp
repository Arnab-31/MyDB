#include <string>
#include <map>
#include <vector>

using namespace std;

// --------------------------------------
// 1) Condition Class
//    - Stores one condition of the form: columnName op value
//      Example: "id > 10" 
// --------------------------------------
class Condition {
private:
    string columnName;       // e.g. "id"
    string conditionOperator; // e.g. "<", ">", "=="
    string value;             // e.g. "10"

public:
    // Constructors
    Condition() = default;
    Condition(const string& col, const string& op, const string& val)
        : columnName(col), conditionOperator(op), value(val) {}

    // Setters
    void setColumnName(const string& col) {
        columnName = col;
    }
    void setConditionOperator(const string& op) {
        conditionOperator = op;
    }
    void setValue(const string& val) {
        value = val;
    }

    // Getters
    const string& getColumnName() const {
        return columnName;
    }
    const string& getConditionOperator() const {
        return conditionOperator;
    }
    const string& getValue() const {
        return value;
    }
};