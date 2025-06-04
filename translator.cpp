#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: 12
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: Eduardo Rocha 
// Function to load the Lexicon from the provided file
void loadLexicon(const string& filename) {
    ifstream fin(filename);  // Open the file
    if (!fin) {
        cerr << "Error: Cannot open lexicon file." << endl;
        exit(1);
    }

    string line;
    while (getline(fin, line)) {
        // Ignore empty lines or lines that do not have proper formatting
        if (line.empty() || isspace(line[0])) continue;

        istringstream iss(line);
        string jpWord, enWord;

        // Extract the Japanese word and its English translation
        if (iss >> jpWord >> ws && getline(iss, enWord)) {
            Lexicon[jpWord] = enWord;
        }
    }
    fin.close();  // Close the file
}

// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: Eduardo Rocha 
void getEword()
{
  if(Lexicon.find(saved_lexeme) != Lexiocon.end())
  {
    saved_E_word = Lexicon[saved_lexeme];
  }
  else
   {
    saved_E_word = saved_lexeme;
   }
   cout << "getEword: japanese word \"" << saved_lexeme << "\", English word \"" << saved_E_word << "\"" << endl;
}

//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: ** 

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.


// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  **
int main()
{
  //** opens the lexicon.txt file and reads it into Lexicon
  //** closes lexicon.txt 

  //** opens the output file translated.txt

  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing

  //** closes the input file 
  //** closes traslated.txt
 
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

