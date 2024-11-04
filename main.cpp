#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
// Structure to hold the details of a line in the code
struct LineInfo {
int lineNumber;
string content;
vector<string> affectedVariables;
};
// Function to parse the code and find the variable usage
void analyzeCode(const string& code, const string& variableName, vector<LineInfo>& linesInfo) {
istringstream iss(code);
string line;
int lineNumber = 0;
while (getline(iss, line)) {
lineNumber++;
LineInfo lineInfo = {lineNumber, line, {}};
// Check if the variable is assigned or used in this line
if (line.find(variableName) != string::npos) {
// Find all affected variables
size_t pos = 0;
while ((pos = line.find("int ", pos)) != string::npos) {
size_t endPos = line.find(";", pos);
string varDeclaration = line.substr(pos, endPos - pos);
// Extract the variable name
size_t spacePos = varDeclaration.find(" ");
if (spacePos != string::npos) {
string affectedVar = varDeclaration.substr(spacePos + 1);
size_t commaPos = affectedVar.find(",");
if (commaPos != string::npos) {
affectedVar = affectedVar.substr(0, commaPos);
}
lineInfo.affectedVariables.push_back(affectedVar);
}
pos = endPos;
}
}
linesInfo.push_back(lineInfo);
}
}
int main() {
string codeSnippet = R"(
#include <iostream>
#include <stdio.h>
int main() {
int x = 10;
int y = x + 5;
int z = y * 2;
cout << z << endl;
return 0;
})";
string variableName = "z"; // Variable to analyze
vector<LineInfo> linesInfo;
analyzeCode(codeSnippet, variableName, linesInfo);
cout << "Variable '" << variableName << "' is used in the following lines:\n";
for (const auto& lineInfo : linesInfo) {
if (lineInfo.content.find(variableName) != string::npos) {
cout << "Line " << lineInfo.lineNumber << ": " << lineInfo.content << endl;
cout << "Affected variables: ";
for (const auto& affectedVar : lineInfo.affectedVariables) {
cout << affectedVar << " ";
}
cout << endl;
}
}
return 0;
}