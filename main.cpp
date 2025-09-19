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

// reference variables for displaying results of truth table and propositions
bool p = true;
string pHumanText = "";

bool q = true;
string qHumanText = "";

// user is not allowed to enter these words to ensure proper formatting
vector<string> negations = { 
    "don't", "do not", "isn't", "is not", "aren't", "are not",
    "haven't", "have not", "hasn't", "has not", "wasn't", "was not",
    "weren't", "were not", "hadn't", "had not", "wouldn't", "would not",
    "won't", "will not", "doesn't", "does not"
};

vector<string> prepositions = {
    "if", "then"
};

string input = "";
string inputLower = "";

bool isUserStillEntering = true; // flag to whether or not keep user prompting statement because he or she has or has not used negations or prepositions

string toLowercase(const std::string& s) {
    std::string result = s; // copy original
    for (std::size_t i = 0; i < result.size(); ++i) { // iterates over all chars in string array to make each lowercase
        result[i] = std::tolower(static_cast<unsigned char>(result[i]));
    }
    return result;
}

bool promptStatement(string& input, string& inputLower, const vector<string>& negationsList) { 
    getline(cin, input);
    
    inputLower = toLowercase(input); // normalize input to make checking for negations and preposition words easier

    for (const auto& negationWord : negations) {
        if (inputLower.find(negationWord) != string::npos) { // a word from negation words list has been detected
            cout << "Warning: Statement cannot contain negation!" << endl;
            return false;
        }
    }

    for (const auto& prepositionWord : prepositions) {
        if (inputLower.find(prepositionWord) != string::npos) { // "if" or "then" word has been detected
            cout << "Warning: Statement cannot contain preposition \"if\" or \"then\"!" << endl;
            return false;
        }
    }
    
    inputLower = "";
    return true;
}

void askStatementUntilSuccess(string& input, string& inputLower, const vector<string>& negationsList, string& humanText) {
    while (!promptStatement(input, inputLower, negationsList)) { // user has entered a negation or preposition word
        cout << "Enter input again:" << endl;
        cout << "If/then ";
    }

    humanText = input; // transfer checked statement onto the variable for currently asked statement
    input = "";
}

bool evaluateConditionalStatement(bool p, bool q) { // used for checking conditional statement p -> q
    if (p == true && q == false) { // premise has been broken
        return false;
    }
    else {
        return true;
    }
}

void displayTruthTableHeader() { // unicode escape sequences used to ensure special symbol is interpreted correctly
    cout << setw(3) << "P" // setw spaces out characters along the line to form an invisible table
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

void displayTruthTableValues(bool p, bool q) { // parameters declared to compute the current set of p and q statements
    cout << boolalpha
         << setw(5) << p
         << setw(7) << q
         << setw(7) << !p // NOT P
         << setw(7) << !q // NOT Q
         << setw(7) << (p && q) // P AND Q
         << setw(8) << (p || q) // P OR Q
         << setw(8) << evaluateConditionalStatement(p, q) // Conditional Statement
         << setw(9) << (p != q) // P XOR Q
         << setw(7) << (p == q) // P IFF Q
         << setw(11) << !(p && q) // P NAND Q
         << setw(10) << !(p || q) // P NOR Q
         << setw(9) << evaluateConditionalStatement(!p, !q) // Contrapositive of Conditional Statement
         << endl;
}

string negateHumanText(const string& humanText) { // add "not" prefix to signify negation
    return "not " + humanText; // it would be too complex to insert this in between the user's statement as it would require distinguishing the subject and predicate
}

void displayHumanText(const string& pHumanText, const string& qHumanText, bool p, bool q) {

    // NEGATE
    if (p) {
        cout << "P: " << pHumanText << '\n' 
             << u8"\u00acP: " << negateHumanText(pHumanText) << '\n'; // NOT P
    }
    else {
        cout << "P: " << negateHumanText(pHumanText) << '\n' 
             << u8"\u00acP: " << pHumanText << '\n'; // NEGATE NOT P
    }

    if (q) {
        cout << "Q: " << qHumanText << '\n'
             << u8"\u00acQ: " << negateHumanText(qHumanText) << '\n'; // NOT Q
    }
    else {
        cout << "Q: " << negateHumanText(qHumanText) << '\n' 
             << u8"\u00acQ: " << qHumanText << '\n'; // NEGATE NOT Q
    }


    // AND, OR, Conditional statement, XOR, IFF
    if (p == true && q == true) { // P, Q
        cout << boolalpha
             << u8"P \u2227 Q: " << pHumanText << " and " << qHumanText << " (Result: " << (p && q) << ")\n" // P AND Q

             << u8"P \u2228 Q: " << pHumanText << " or " << qHumanText << " (Result: " << (p || q) << ")\n" // P OR Q

             << u8"P \u2192 Q: " << "If " << pHumanText << ", then " << qHumanText <<
             " (Result: " << evaluateConditionalStatement(p, q) << ")\n" // Conditional statement

             << u8"P \u2295 Q: " << "Either " << pHumanText << " or " << qHumanText << ", but not both" << 
             " (Result: " << (p != q) << ")\n" // P XOR Q

             << u8"P \u2194 Q: " << pHumanText << " if and only if " << qHumanText << " (Result: " << (p == q) << ")\n" // P IFF Q

             << u8"\u00ac(P \u2227 Q): " << negateHumanText(pHumanText) << " and " << negateHumanText(qHumanText) <<
             " (Result: " << !(p && q) << ")\n" // P NAND Q

             << u8"\u00ac(P \u2228 Q): " << negateHumanText(pHumanText) << " or " << negateHumanText(qHumanText) <<
             " (Result: " << !(p || q) << ")\n" // P NOR Q

             << u8"\u00acP \u2192 \u00acQ: " << "If " << negateHumanText(pHumanText) << ", then " << negateHumanText(qHumanText) <<
             " (Result: " << evaluateConditionalStatement(!p, !q) << ")\n" // Contrapositive of Conditional statement
             << endl; 
    }
    else if (p == true && q == false) { // P, NOT Q
        cout << boolalpha
             << u8"P \u2227 Q: " << pHumanText << " and " << negateHumanText(qHumanText) << 
             " (Result: " << (p && q) << ")\n" // P AND NOT Q

             << u8"P \u2228 Q: " << pHumanText << " or " << negateHumanText(qHumanText) << 
             " (Result: " << (p || q) << ")\n" // P OR NOT Q

             << u8"P \u2192 Q: " << "If " << pHumanText << ", then " << negateHumanText(qHumanText) <<
             " (Result: " << evaluateConditionalStatement(p, q) << ")\n" // Conditional statement

             << u8"P \u2295 Q: " << "Either " << pHumanText << " or " << negateHumanText(qHumanText) << ", but not both" << 
             " (Result: " << (p != q) << ")\n" // P XOR NOT Q

             << u8"P \u2194 Q: " << pHumanText << " if and only if " << negateHumanText(qHumanText) << 
             " (Result: " << (p == q) << ")\n" // P IFF NOT Q

             << u8"\u00ac(P \u2227 Q): " << negateHumanText(pHumanText) << " and " << qHumanText <<
             " (Result: " << !(p && q) << ")\n" // P NAND NOT Q

             << u8"\u00ac(P \u2228 Q): " << negateHumanText(pHumanText) << " or " << qHumanText <<
             " (Result: " << !(p || q) << ")\n" // P NOR NOT Q

             << u8"\u00acP \u2192 \u00acQ: " << "If " << negateHumanText(pHumanText) << ", then " << qHumanText <<
             " (Result: " << evaluateConditionalStatement(!p, !q) << ")\n" // Contrapositive of Conditional statement
             << endl; 
    }
    else if (p == false && q == true) { // NOT P, Q
        cout << boolalpha
             << u8"P \u2227 Q: " << negateHumanText(pHumanText) << " and " << qHumanText << 
             " (Result: " << (p && q) << ")\n" // NOT P AND Q

             << u8"P \u2228 Q: " << negateHumanText(pHumanText) << " or " << qHumanText << 
             " (Result: " << (p || q) << ")\n" // NOT P OR Q

             << u8"P \u2192 Q: " << "If " << negateHumanText(pHumanText) << ", then " << qHumanText <<
             " (Result: " << evaluateConditionalStatement(p, q) << ")\n" // Conditional statement

             << u8"P \u2295 Q: " << "Either " << negateHumanText(pHumanText) << " or " << qHumanText << ", but not both" << 
             " (Result: " << (p != q) << ")\n" // NOT P XOR Q

             << u8"P \u2194 Q: " << negateHumanText(pHumanText) << " if and only if " << qHumanText << 
             " (Result: " << (p == q) << ")\n" // NOT P IFF Q

             << u8"\u00ac(P \u2227 Q): " << pHumanText << " and " << negateHumanText(qHumanText) <<
             " (Result: " << !(p && q) << ")\n" // NOT P NAND Q

             << u8"\u00ac(P \u2228 Q): " << pHumanText << " or " << negateHumanText(qHumanText) <<
             " (Result: " << !(p || q) << ")\n" // NOT P NOR Q

             << u8"\u00acP \u2192 \u00acQ: " << "If " << pHumanText << ", then " << negateHumanText(qHumanText) <<
             " (Result: " << evaluateConditionalStatement(!p, !q) << ")\n" // Contrapositive of Conditional statement
             << endl; 
    }
    else if (p == false && q == false) { // NOT P, NOT Q
        cout << boolalpha
             << u8"P \u2227 Q: " << negateHumanText(pHumanText) << " and " << negateHumanText(qHumanText) << 
             " (Result: " << (p && q) << ")\n" // NOT P AND NOT Q

             << u8"P \u2228 Q: " << negateHumanText(pHumanText) << " or " << negateHumanText(qHumanText) << 
             " (Result: " << (p || q) << ")\n" // NOT P OR NOT Q

             << u8"P \u2192 Q: " << "If " << negateHumanText(pHumanText) << ", then " << negateHumanText(qHumanText) <<
             " (Result: " << evaluateConditionalStatement(p, q) << ")\n" // Conditional statement

             << u8"P \u2295 Q: " << "Either " << negateHumanText(pHumanText) << " or " << negateHumanText(qHumanText) << ", but not both" << 
             " (Result: " << (p != q) << ")\n" // NOT P XOR NOT Q

             << u8"P \u2194 Q: " << negateHumanText(pHumanText) << " if and only if " << negateHumanText(qHumanText) << 
             " (Result: " << (p == q) << ")\n" // NOT P IFF NOT Q

             << u8"\u00ac(P \u2227 Q): " << pHumanText << " and " << qHumanText <<
             " (Result: " << !(p && q) << ")\n" // NOT P NAND NOT Q

             << u8"\u00ac(P \u2228 Q): " << pHumanText << " or " << qHumanText <<
             " (Result: " << !(p || q) << ")\n" // NOT P NOR NOT Q

             << u8"\u00acP \u2192 \u00acQ: " << "If " << pHumanText << ", then " << qHumanText <<
             " (Result: " << evaluateConditionalStatement(!p, !q) << ")\n" // Contrapositive of Conditional statement
             << endl; 
    }
}

int main()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); // switch console to UTF-8 for Windows users
    #endif

    // ask user of p and q statements for later in truth table and propositions
    cout << "Enter your hypothesis:" << endl;
    cout << "If ";
    askStatementUntilSuccess(input, inputLower, negations, pHumanText);
    cout << endl;
    cout << "Hypothesis input: " << pHumanText << endl; // display received statement
    cout << endl;

    cout << "Enter your conclusion:" << endl;
    cout << "then ";
    askStatementUntilSuccess(input, inputLower, negations, qHumanText);
    cout << endl;
    cout << "Conclusion input: " << qHumanText << endl;
    cout << endl;

    cout << endl;
    cout << "TRUTH TABLE" << endl;
    cout << endl;

    displayTruthTableHeader(); // construct truth table

    displayTruthTableValues(p, q); // first call uses default values

    p = true;
    q = false;
    displayTruthTableValues(p, q);

    p = false;
    q = true;
    displayTruthTableValues(p, q);

    p = false;
    q = false;
    displayTruthTableValues(p, q);
    cout << endl;

    cout << endl;
    cout << "PROPOSITIONS" << endl; // display human text format of the logical computations
    cout << endl;
    
    p = true;
    q = true;
    cout << "P = " << p << ", Q = " << q << endl;
    displayHumanText(pHumanText, qHumanText, p, q);
    cout << endl;

    p = true;
    q = false;
    cout << "P = " << p << ", Q = " << q << endl;
    displayHumanText(pHumanText, qHumanText, p, q);
    cout << endl;

    p = false;
    q = true;
    cout << "P = " << p << ", Q = " << q << endl;
    displayHumanText(pHumanText, qHumanText, p, q);
    cout << endl;

    p = false;
    q = false;
    cout << "P = " << p << ", Q = " << q << endl;
    displayHumanText(pHumanText, qHumanText, p, q);
    cout << endl;

    _getch();

    return 0;
}