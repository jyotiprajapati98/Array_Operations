#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

using Array3D = vector<vector<vector<float>>>;

bool parseFile(const string& filename, Array3D& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return false;
    }
    
    string line;
    int lineNumber = 0;
    vector<vector<float>> currentMatrix;
    vector<float> currentRow;
    
    while (getline(file, line)) {
        lineNumber++;
        stringstream ss;
        
        for (char c : line) {
            if (isdigit(c) || c == '.' || c == '-' || c == ' ' || c == ',' || c == ']') {
                ss << c;
            } else if (c == '[') {
                if (!currentMatrix.empty()) {
                    data.push_back(currentMatrix);
                    currentMatrix.clear();
                }
            }
        }
        
        float value;
        while (ss >> value) {
            currentRow.push_back(value);
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
        
        if (!currentRow.empty()) {
            currentMatrix.push_back(currentRow);
            currentRow.clear();
        }
    }
    
    if (!currentMatrix.empty()) {
        data.push_back(currentMatrix);
    }
    
    file.close();
    return true;
}

void printAndSaveArray3D(const Array3D& data, const string& outputFilename) {
    ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open output file " << outputFilename << endl;
        return;
    }

    cout << fixed << setprecision(6);
    outFile << fixed << setprecision(6);

    for (size_t i = 0; i < data.size(); ++i) {
        cout << "Data Sample " << i + 1 << ":\n";
        outFile << "Data Sample " << i + 1 << ":\n";
        
        for (const auto& row : data[i]) {
            for (float value : row) {
                cout << value << " ";
                outFile << value << " ";
            }
            cout << "\n";
            outFile << "\n";
        }
        cout << "------------------\n";
        outFile << "------------------\n";

    }
    
    outFile.close();
}

int main() {
    string filename = "Input_Data_Sample.txt";
    string outputFilename = "Parsed_Data_Sample_Output.txt";
    Array3D data;
    
    if (parseFile(filename, data)) {
        cout << "File parsed successfully.\n";
        printAndSaveArray3D(data, outputFilename);
        cout << "Data has been written to " << outputFilename << endl;
    } else {
        cout << "File parsing failed." << endl;
    }
    
    return 0;
}
