#include "./include/updateTableCSV.h"
#include "./include/SQLQuery.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

void updateTableCSV(const SQLQuery& sqlQuery) {
    // Retrieve condition, update fields, and table name
    const Condition& condition = sqlQuery.getWhereCondition();
    const auto& updateValues = sqlQuery.getUpdateValues();
    const string& tableName = sqlQuery.getTableName();

    // Open the CSV file
    ifstream inFile("data/" + tableName + ".csv");
    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << tableName << ".csv" << endl;
        return;
    }

    // Read the header line
    string headerLine;
    getline(inFile, headerLine);
    vector<string> headers;
    stringstream headerStream(headerLine);
    string header;
    while (getline(headerStream, header, ',')) {
        headers.push_back(header);
    }

    // Read the rest of the file
    vector<vector<string>> rows;
    string line;
    while (getline(inFile, line)) {
        stringstream lineStream(line);
        string cell;
        vector<string> row;
        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        rows.push_back(row);
    }
    inFile.close();

    // Find the index of the condition column
    auto it = find(headers.begin(), headers.end(), condition.getColumnName());
    int conditionIndex = (it != headers.end()) ? distance(headers.begin(), it) : -1;

    // Check if all columns to be updated are present
    for (const auto& update : updateValues) {
        auto updateIt = find(headers.begin(), headers.end(), update.first);
        if (updateIt == headers.end()) {
            cerr << "Error: Column " << update.first << " not found in table " << tableName << endl;
            return;
        }
    }

    // Introduce a variable to track how many rows are updated
    int updatedCount = 0;

    // Update matching rows or all rows if no condition is provided
    for (auto& row : rows) {
        if (conditionIndex == -1 || row[conditionIndex] == condition.getValue()) {
            for (const auto& update : updateValues) {
                auto updateIt = find(headers.begin(), headers.end(), update.first);
                if (updateIt != headers.end()) {
                    int updateIndex = distance(headers.begin(), updateIt);
                    row[updateIndex] = update.second;
                }
            }
            // Increment the counter whenever a row matches the condition or if no condition is provided
            updatedCount++;
        }
    }

    // Write the updated rows back to the file
    ofstream outFile("data/" + tableName + ".csv", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file data/" << tableName << ".csv" << endl;
        return;
    }

    // Write the header
    outFile << headerLine << endl;

    // Write the rows
    for (const auto& row : rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << row[i];
            if (i < row.size() - 1) {
                outFile << ",";
            }
        }
        outFile << endl;
    }
    outFile.close();

    // Print the number of updated rows
    cout << updatedCount << " rows updated" << endl;
}