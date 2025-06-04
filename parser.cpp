#include <iostream>
#include <fstream>
#include <string>
#include "scanner.cpp"
typedef tokentype token_type;
using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .
       and then append the two files into one:
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: 12
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------
// ifstream fin; // Removed duplicate definition
string saved_lexeme;
token_type saved_token;
bool token_available = false;
ofstream errorFile("errors.txt"); // Global file stream for error messages
bool tracing = true;              // Set to true to enable tracing, false to disable

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.
void syntaxerror1(token_type expected, string lexeme);
void syntaxerror2(string function_name, string lexeme);

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme
token_type next_token();

// Type of error: Expected
// Done by: Eduardo Rocha and Alexander Nicholas
void syntaxerror1(token_type expected, string lexeme)
{
    // Construct the error message
    string errorMessage = "SYNTAX ERROR: Expected " + tokenName[expected] + " but found " + lexeme + "\n";

    // Print and log the error
    cout << errorMessage;
    if (errorFile.is_open())
        errorFile << errorMessage;

    exit(1); // Exit on syntax error
}

// Type of error: Unexpected
// Done by: Eduardo Rocha and Alexander Nicholas
void syntaxerror2(string function_name, string lexeme)
{

    // Construct the error message
    string errorMessage = "SYNTAX ERROR: Unexpected " + lexeme + " found in " + function_name + "\n";

    // Print to the console
    cout << errorMessage;

    // Write to the error file
    if (errorFile.is_open())
    {
        errorFile << errorMessage;
    }

    exit(1); // Exit on syntax error
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Will grab and update any new tokens and continue to do so sequentially.
// Done by: Eduardo Rocha
token_type next_token()
{
    if (!token_available)
    {                                       // if there is no saved token yet
        scanner(saved_token, saved_lexeme); // call scanner to grab a new token
        token_available = true;             // mark the fact that you have saved it
    }
    return saved_token; // return the saved token
}

// Purpose: Will track any matched token and save them.
// Done by: Eduardo Rocha
bool match(tokentype expected)
{
    if (next_token() != expected)
    {                                         // mismatch has occurred with the next token
        syntaxerror1(expected, saved_lexeme); // call syntax error function
        return false;
    }
    else
    {                                                      // match has occurred
        cout << "Matched " << tokenName[expected] << endl; // trace the matched token
        token_available = false;                           // eat up the token
        return true;
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

void story();
void s();
void noun();
void verb();
void be();
void tense();

// Grammar: <story> ::= <s> { <s> }
// Done by: Alexander Nicholas
void story()
{
    if (tracing)
        cout << "Processing <story>" << endl;
    s(); // process one <s>
    while (next_token() == CONNECTOR || next_token() == WORD1 || next_token() == PRONOUN)
    {
        s(); // process additional <s> as long as start of <s> is seen
    }
}

// Grammar rule: <s> ::= [CONNECTOR] <noun> SUBJECT <verb> <tense> PERIOD
// Done by: Eduardo Rocha
void s()
{
    if (tracing)
        cout << "Processing <s>" << endl; // Print tracing message if tracing is enabled

    if (next_token() == CONNECTOR)
    {
        match(CONNECTOR); // Match optional CONNECTOR if the next token is CONNECTOR
    }

    noun();         // Process <noun>
    match(SUBJECT); // Match SUBJECT token
    cout << "Processing <afterSubject>" << endl;

    if (next_token() == WORD2)
    {
        verb();        // Process <verb> if the next token is WORD2
        tense();       // Process <tense>
        match(PERIOD); // Match PERIOD token
    }
    else if (next_token() == WORD1 || next_token() == PRONOUN)
    {
        noun(); // Process <noun> if the next token is WORD1 or PRONOUN
        cout << "Processing <afterNoun>" << endl;
        if (next_token() == IS || next_token() == WAS)
        {
            be();          // Process <be> if the next token is IS or WAS
            match(PERIOD); // Match PERIOD token
        }
        else if (next_token() == DESTINATION)
        {
            match(DESTINATION); // Match DESTINATION token
            verb();             // Process <verb>
            tense();            // Process <tense>
            match(PERIOD);      // Match PERIOD token
        }
        else if (next_token() == OBJECT)
        {
            match(OBJECT); // Match OBJECT token

            if (next_token() == WORD2)
            {
                verb();        // Process <verb> if the next token is WORD2
                tense();       // Process <tense>
                match(PERIOD); // Match PERIOD token
            }
            else if (next_token() == WORD1 || next_token() == PRONOUN)
            {
                noun();             // Process <noun> if the next token is WORD1 or PRONOUN
                match(DESTINATION); // Match DESTINATION token
                verb();             // Process <verb>
                tense();            // Process <tense>
                match(PERIOD);      // Match PERIOD token
            }
        }
        else
        {
            syntaxerror2("afterNoun", saved_lexeme); // Catch unexpected tokens
        }
    }
    else
    {
        syntaxerror2("afterSubject", saved_lexeme); // Catch unexpected tokens
    }
}

// Grammar rule: <noun> ::= WORD1 | PRONOUN
// Done by: Minh Tran
void noun()
{
    if (tracing)
        cout << "Processing <noun>" << endl; // Print tracing message if tracing is enabled

    if (next_token() == WORD1)
    {
        match(WORD1); // Match WORD1 if the next token is WORD1
    }
    else if (next_token() == PRONOUN)
    {
        match(PRONOUN); // Match PRONOUN if the next token is PRONOUN
    }
    else
    {
        syntaxerror2("noun", saved_lexeme); // Call syntax error function if no match is found
    }
}

// Grammar rule: <verb> ::= WORD2
// Done by: Eduardo Rocha
void verb()
{
    if (tracing)                             // If tracing is enabled
        cout << "Processing <verb>" << endl; // Print tracing message
    match(WORD2);                            // Match WORD2 token
}

// Grammar rule: <be> ::= IS | WAS
// Done by: Minh Tran
void be()
{
    if (tracing)                           // If tracing is enabled
        cout << "Processing <be>" << endl; // Print tracing message
    if (next_token() == IS)                // Check if the next token is IS
    {
        match(IS); // Match IS token
    }
    else if (next_token() == WAS) // Check if the next token is WAS
    {
        match(WAS); // Match WAS token
    }
    else // If the next token is neither IS nor WAS
    {
        syntaxerror2("be", saved_lexeme); // Call syntax error function
    }
}

// Grammar rule: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Alexander Nicholas
void tense()
{
    if (tracing)                              // If tracing is enabled
        cout << "Processing <tense>" << endl; // Print tracing message

    if (next_token() == VERBPAST) // Check if the next token is VERBPAST
    {
        match(VERBPAST); // Match VERBPAST token
    }
    else if (next_token() == VERBPASTNEG) // Check if the next token is VERBPASTNEG
    {
        match(VERBPASTNEG); // Match VERBPASTNEG token
    }
    else if (next_token() == VERB) // Check if the next token is VERB
    {
        match(VERB); // Match VERB token
    }
    else if (next_token() == VERBNEG) // Check if the next token is VERBNEG
    {
        match(VERBNEG); // Match VERBNEG token
    }
    else // If the next token is none of the above
    {
        syntaxerror2("tense", saved_lexeme); // Call syntax error function
    }
}

string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Alexander Nicholas
int main()
{

    cout << "Group 12 - Eduardo Rocha, Alexander Nicholas, and Minh Tran \n"; // Prompt the user to enter the input file name

    char traceInput; // Variable to store user input for tracing option
    while (true)     // Infinite loop to get valid tracing input from the user
    {
        cout << "Enable tracing? (y/n): "; // Prompt the user to enable tracing
        cin >> traceInput;                 // Read the user input
        if (traceInput == 'y' || traceInput == 'Y' || traceInput == 'n' || traceInput == 'N')
        {
            tracing = (traceInput == 'y' || traceInput == 'Y'); // Enable tracing if user inputs 'y'
            break;                                              // Exit the loop if the input is valid
        }
        else
        {
            cerr << "Invalid input for tracing option. Please enter 'y' or 'n'." << endl; // Error message for invalid input
        }
    }

    cout << "Enter the input file name: "; // Prompt the user to enter the input file name
    cin >> filename;                       // Read the file name from the user
    fin.open(filename.c_str());            // Open the input file

    if (!fin) // Check if the file was opened successfully
    {
        cerr << "Error opening file " << filename << endl; // Error message if the file cannot be opened
        return 1;                                          // Exit if the file cannot be opened
    }

    // Calls the <story> function to start parsing
    story();

    // Closes the input file and the error file
    fin.close();             // Close the input file
    if (errorFile.is_open()) // Check if the error file is open
    {
        errorFile.close(); // Close the error file
    }

    cout << "Parsing completed." << endl; // Message indicating parsing is completed
    return 0;                             // Return 0 to indicate successful execution

} // end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
