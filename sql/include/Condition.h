
#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

class Condition {
private:
    std::string columnName;        // e.g. "id"
    std::string conditionOperator; // e.g. "<", ">", "=="
    std::string value;             // e.g. "10"

public:
    Condition();
    Condition(const std::string& col, const std::string& op, const std::string& val);

    void setColumnName(const std::string& col);
    void setConditionOperator(const std::string& op);
    void setValue(const std::string& val);

    const std::string& getColumnName() const;
    const std::string& getConditionOperator() const;
    const std::string& getValue() const;
};