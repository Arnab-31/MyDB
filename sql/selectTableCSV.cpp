#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "./include/SQLQuery.h"
#include "./include/selectTableCSV.h"
#include "./include/Condition.h"

static std::vector<std::string> splitRow(const std::string &row) {
    std::vector<std::string> result;
    std::stringstream ss(row);
    std::string cell;
    while (std::getline(ss, cell, ',')) {
        result.push_back(cell);
    }
    return result;
}

void selectFromTableCSV(const SQLQuery &query) {
    std::string tableName = query.getTableName();
    std::string filePath = "data/" + tableName + ".csv";
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cout << "Table '" << tableName << "' not found." << std::endl;
        return;
    }

    // Read header
    std::string headerLine;
    if (!std::getline(fileStream, headerLine)) {
        std::cout << "No data found in table '" << tableName << "'." << std::endl;
        return;
    }
    std::vector<std::string> headers = splitRow(headerLine);

    // Identify the columns to select
    std::vector<std::string> selectCols = query.getSelectValues();
    if (selectCols.empty()) {
        std::cout << "No columns specified for select. Showing all columns." << std::endl;
        selectCols = headers;
    }
    // Map column names to indices
    std::vector<int> colIndices;
    for (auto &col : selectCols) {
        auto it = std::find(headers.begin(), headers.end(), col);
        if (it == headers.end()) {
            std::cout << "Column '" << col << "' not found in table '" << tableName << "'." << std::endl;
            return;
        }
        colIndices.push_back(std::distance(headers.begin(), it));
    }

    // Optional: handle WHERE
    Condition cond = query.getWhereCondition();
    int whereColIndex = -1;
    bool hasWhere = !cond.getColumnName().empty();
    std::string conditionValue = cond.getValue();
    if (hasWhere) {
        auto it = std::find(headers.begin(), headers.end(), cond.getColumnName());
        if (it == headers.end()) {
            std::cout << "WHERE column '" << cond.getColumnName() << "' not found." << std::endl;
            return;
        }
        whereColIndex = static_cast<int>(std::distance(headers.begin(), it));
    }

    // Read all rows into a collection to compute column widths
    std::vector<std::vector<std::string>> allRows;
    std::string row;
    while (std::getline(fileStream, row)) {
        std::vector<std::string> rowData = splitRow(row);
        if (rowData.size() < headers.size()) continue; // skip malformed lines
        allRows.push_back(rowData);
    }

    // Compute maximum column widths
    std::vector<size_t> colWidths(colIndices.size(), 0);
    for (size_t i = 0; i < selectCols.size(); ++i) {
        colWidths[i] = std::max(colWidths[i], selectCols[i].size());
    }
    for (auto &r : allRows) {
        for (size_t i = 0; i < colIndices.size(); ++i) {
            colWidths[i] = std::max(colWidths[i], r[colIndices[i]].size());
        }
    }

    // Print table header with widths
    std::cout << "=========================================" << std::endl;
    for (size_t i = 0; i < selectCols.size(); i++) {
        std::cout << std::setw(colWidths[i]) << selectCols[i]
                  << (i < selectCols.size() - 1 ? " | " : "");
    }
    std::cout << std::endl << "=========================================" << std::endl;

    int displayedCount = 0;
    // Print rows with widths
    bool anyRowDisplayed = false;
    for (auto &r : allRows) {
        // Check WHERE condition if present
        if (hasWhere) {
            // Basic check for "="
            if (cond.getConditionOperator() == "=") {
                if (r[whereColIndex] != conditionValue) {
                    continue;
                }
            }
            // Extend for other operators if needed
        }

        // Print selected columns
        for (size_t i = 0; i < colIndices.size(); i++) {
            std::cout << std::setw(colWidths[i]) << r[colIndices[i]]
                      << (i < colIndices.size() - 1 ? " | " : "");
        }
        std::cout << std::endl;
        anyRowDisplayed = true;
        displayedCount++;
    }

    if (!anyRowDisplayed) {
        std::cout << "No matching rows to display." << std::endl;
    } else {
        std::cout << displayedCount << " rows displayed." << std::endl;
    }
}