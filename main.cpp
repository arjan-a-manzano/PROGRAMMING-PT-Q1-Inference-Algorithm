#include <iostream> // import libraries
#include <string>
#include <conio.h>
#include <iomanip>
#include <locale>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using std::cin; // namespace aliases
using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::boolalpha;
using std::tolower;
using std::vector;

bool p = true;
string pHumanText = "";

bool q = true;
string qHumanText = "";

vector<string> negations = {
    "don't", "do not", "isn't", "is not", "aren't", "are not",
    "haven't", "have not", "hasn't", "has not", "wasn't", "was not",
    "weren't", "were not", "hadn't", "had not", "wouldn't", "would not",
    "won't", "will not"
};

vector<string> prepositions = {
    "If", "if", "Then", "then"
};

string input = "";
string inputLower = "";

bool isUserStillEntering = true;

string toLowercase(const std::string& s) {
    std::string result = s; // copy original
    for (std::size_t i = 0; i < result.size(); ++i) {
        result[i] = std::tolower(static_cast<unsigned char>(result[i]));
    }
    return result;
}

bool promptStatement(string& input, string& inputLower, const vector<string>& negationsList) { 
    getline(cin, input);
    
    inputLower = toLowercase(input);

    for (const auto& negationWord : negations) {
        if (inputLower.find(negationWord) != string::npos) {
            return false;
        }
    }

    for (const auto& prepositionWord : prepositions) {
        if (inputLower.find(prepositionWord) != string::npos) {
            return false;
        }
    }
    
    inputLower = "";
    return true;
}

void askStatementUntilSuccess(string& input, string& inputLower, const vector<string>& negationsList, string& humanText) {
    while (!promptStatement(input, inputLower, negationsList)) { cout << "Warning: Statement cannot contain negation!" << endl; }

    humanText = input;
    input = "";
}

bool evaluateConditionalStatement(bool p, bool q) {
    if (p == true && q == false) {
        return false;
    }
    else {
        return true;
    }
}

void displayTruthTableHeader(bool p, bool q) {
    cout << setw(3) << "P"
         << setw(7) << "Q"
         << setw(8) << u8"\u00acP" // NOT P
         << setw(8) << u8"\u00acQ" // NOT Q
         << setw(12) << u8"P \u2227 Q" // P AND Q
         << setw(10) << u8"P \u2228 Q" // P OR Q
         << setw(10) << u8"P \u2192 Q" // Conditional statement
         << setw(10) << u8"P \u2295 Q" // P XOR Q
         << setw(10) << u8"P \u2194 Q" // P IFF QA
         << setw(14) << u8"\u00ac(P \u2227 Q)" // P NAND Q
         << setw(13) << u8"\u00ac(P \u2228 Q)" // P NOR Q
         << setw(13) << u8"\u00acP \u2192 \u00acQ" // Contrapositive of Conditional Statement
         << endl; 
}

void displayTruthTableValues(bool p, bool q) {
    cout << boolalpha
         << setw(5) << p
         << setw(7) << q
         << setw(7) << !p // NOT P
         << setw(7) << !q // NOT Q
         << setw(7) << (p && q) // P AND Q
         << setw(8) << (p || q) // P OR Q
         << setw(8) << evaluateConditionalStatement(p, q) // Conditional Statement
         << setw(9) << (p != q) // P XOR Q
         << setw(7) << (p == q) // P XOR Q
         << setw(11) << !(p && q) // P NAND Q
         << setw(10) << !(p || q) // P NOR Q
         << setw(9) << evaluateConditionalStatement(!p, !q) // Contrapositive of Conditional Statement
         << endl;
}

int main()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); // switch console to UTF-8
    #endif


    cout << "Enter your hypothesis: " << endl;
    cout << "If ";
    askStatementUntilSuccess(input, inputLower, negations, pHumanText);
    cout << endl;
    cout << "Hypothesis input: " << pHumanText << endl;
    cout << endl;

    cout << "Enter your conclusion: " << endl;
    cout << "then ";
    askStatementUntilSuccess(input, inputLower, negations, qHumanText);
    cout << endl;
    cout << "Conclusion input: " << qHumanText << endl;
    cout << endl;

    cout << "Proposition input: " << "If " << pHumanText << ", then " << qHumanText << endl;
    cout << endl;
    

    displayTruthTableHeader(p, q);

    displayTruthTableValues(p, q);

    p = true;
    q = false;
    displayTruthTableValues(p, q);

    p = false;
    q = true;
    displayTruthTableValues(p, q);

    p = false;
    q = false;
    displayTruthTableValues(p, q);

    _getch();

    return 0;
}