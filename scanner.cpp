#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: 12
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA
// Done by: Eduardo Rocha
// RE: (vowel | vowel n | consonant vowel | consonant vowel n | consonant consonant vowel | consonant consonant vowel n)+
bool word(string s)
{
  int state = 0;   // Initial state (q0)
  int charpos = 0; // Position in the input string

  /*
     DFA States:
     state 0 = q0: Initial state
     state 1 = q0q1: After recognizing a vowel (a, i, u, e, o, E, I)
     state 2 = qt: After recognizing 't'
     state 3 = qc: After recognizing 'c'
     state 4 = qs: After recognizing 's'
     state 5 = qsa: After recognizing characters like d, w, z, y, j, or handling transitions from other states
     state 6 = qy: After recognizing consonants b, g, h, k, m, n, p, r, or h
     state 7 = qyq0: After recognizing 'n'
  */

  // Loop through the string until the end
  while (s[charpos] != '\0')
  {
    char c = s[charpos]; // Get the current character

    // State transitions based on the DFA logic
    if (state == 0) // q0: Initial state
    {
      // If a vowel is encountered, move to q0q1 state
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' || c == 'E' || c == 'I')
        state = 1;       // Move to q0q1 state
      else if (c == 't') // If 't' is encountered, move to qt state
        state = 2;
      else if (c == 'c') // If 'c' is encountered, move to qc state
        state = 3;
      else if (c == 's') // If 's' is encountered, move to qs state
        state = 4;
      // If any of these characters are encountered, move to qsa state
      else if (c == 'd' || c == 'w' || c == 'z' || c == 'y' || c == 'j')
        state = 5;
      // If any of these consonants are encountered, move to qy state
      else if (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'n' || c == 'p' || c == 'r')
        state = 6;
      else
        return false; // If the character doesn't match any known transition, return false (invalid word)
    }

    // State q0q1 (state 1): After recognizing a vowel
    else if (state == 1)
    {
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' || c == 'E' || c == 'I') // Vowel case
        state = 1;                                                                          // Stay in q0q1 state if another vowel is encountered
      else if (c == 't')                                                                    // If 't' is encountered, move to qt state
        state = 2;
      else if (c == 'c') // If 'c' is encountered, move to qc state
        state = 3;
      else if (c == 's') // If 's' is encountered, move to qs state
        state = 4;
      else if (c == 'd' || c == 'w' || c == 'z' || c == 'y' || c == 'j') // Move to qsa state
        state = 5;
      else if (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'p' || c == 'r') // Consonants lead to qy state
        state = 6;
      else if (c == 'n') // If 'n' is encountered, move to qyq0 state
        state = 7;
      else
        return false; // Invalid character, return false
    }

    // State qt (state 2): After recognizing 't'
    else if (state == 2)
    {
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' || c == 'E' || c == 'I') // Vowel case
        state = 1;                                                                          // Return to q0q1 state after vowel
      else if (c == 's')                                                                    // If 's' is encountered, move to qsa state
        state = 5;
      else
        return false; // Invalid character, return false
    }

    // State qc (state 3): After recognizing 'c'
    else if (state == 3)
    {
      if (c == 'h') // 'ch' leads to qsa state
        state = 5;
      else
        return false; // Invalid character, return false
    }

    // State qs (state 4): After recognizing 's'
    else if (state == 4)
    {
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' || c == 'E' || c == 'I') // Vowel case
        state = 1;                                                                          // Return to q0q1 state after vowel
      else if (c == 'h')                                                                    // 'sh' leads to qsa state
        state = 5;
      else
        return false; // Invalid character, return false
    }

    // State qsa (state 5): After recognizing characters that transition to qsa
    else if (state == 5)
    {
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' || c == 'E' || c == 'I') // Vowel case
        state = 1;                                                                          // Return to q0q1 state after vowel
      else
        return false; // Invalid character, return false
    }

    // State qy (state 6): After recognizing consonants that transition to qy
    else if (state == 6)
    {
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' || c == 'E' || c == 'I') // Vowel case
        state = 1;                                                                          // Return to q0q1 state after vowel
      else if (c == 'y')                                                                    // 'y' leads to qsa state
        state = 5;
      else
        return false; // Invalid character, return false
    }

    // State qyq0 (state 7): After recognizing 'n'
    else if (state == 7)
    {
      // Valid transitions from qyq0 based on different characters
      if (c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o' || c == 'E' || c == 'I') // Vowel case
        state = 1;                                                                          // Return to q0q1 state after vowel
      else if (c == 't')
        state = 2; // 't' transitions to qt state
      else if (c == 'c')
        state = 3; // 'c' transitions to qc state
      else if (c == 's')
        state = 4;                                                       // 's' transitions to qs state
      else if (c == 'd' || c == 'w' || c == 'z' || c == 'y' || c == 'j') // Characters transition to qsa
        state = 5;
      else if (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'n' || c == 'p' || c == 'r') // Consonants transition to qy state
        state = 6;
      else
        return false; // Invalid character, return false
    }

    charpos++; // Move to the next character in the input string
  }

  // Final state validation: return true if we end in a valid state (q0, q0q1, or qyq0)
  if (state == 0 || state == 1 || state == 7)
    return true;
  else
    return false; // Return false if in any other state
}

// DFA for recognizing a period (".")
// Done 6by: Eduardo Rocha
// RE: "\."
bool period(string s)
{
  // If the input string is a period, return true
  if (s == ".")
    return true;
  else
    return false; // Otherwise, return false
}

// ------ Three Tables -------------------------------------

// TABLES Done by: Eduardo Rocha

// Enumeration for token types
// Each token type represents a specific category of words or symbols in the language being parsed
enum tokentype
{
  ERROR,       // Represents an unrecognized or invalid token
  WORD1,       // Token type for a regular word (pattern 1)
  WORD2,       // Token type for a regular word (pattern 2)
  PERIOD,      // Token type for a period
  EOFM,        // End-of-file marker token type
  PRONOUN,     // Token type for pronouns
  VERB,        // Token type for verbs in the present tense
  IS,          // Token type for "desu" (is)
  OBJECT,      // Token type for the object of a sentence
  SUBJECT,     // Token type for the subject of a sentence
  DESTINATION, // Token type for destination
  VERBNEG,     // Token type for verbs in the negative form
  VERBPAST,    // Token type for verbs in the past tense
  VERBPASTNEG, // Token type for verbs in the past negative form
  WAS,         // Token type for the past tense of "desu"
  CONNECTOR    // Token type for connecting words
};

// Array of token names for printing
// This array holds string representations of the token types for debugging or output purposes
string tokenName[30] = {
    "ERROR", "WORD1", "WORD2", "PERIOD", "EOFM",
    "PRONOUN", "VERB", "IS", "OBJECT", "SUBJECT",
    "DESTINATION", "VERBNEG", "VERBPAST", "VERBPASTNEG", "WAS",
    "CONNECTOR"};

// Reserved words and their corresponding token types
// These arrays hold the reserved words in the language and the corresponding token types
string reservedWords[18] = {
    "watashi", "anata", "kare", "kanojo", "spre", "masu",
    "desu", "o", "wa", "ni", "masen", "mashita",
    "masendeshita", "deshita", "mata", "soshite",
    "shikashi", "dakara"};

// This array maps the reserved words to their respective token types
tokentype reservedType[18] = {
    PRONOUN, PRONOUN, PRONOUN, PRONOUN, PRONOUN,
    VERB, IS, OBJECT, SUBJECT, DESTINATION,
    VERBNEG, VERBPAST, VERBPASTNEG, WAS,
    CONNECTOR, CONNECTOR, CONNECTOR, CONNECTOR};

// ------------ Scanner and Driver -----------------------

// Global stream for reading from the input file
ifstream fin;

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// Done by: Minh Tran and Alexander Nicholas
int scanner(tokentype &tt, string &w)
{
  // Grab the next word from the file via fin (input file stream)
  fin >> w;

  cout << "Scanner called using word: " << w << endl;

  // 1. If the word is "eofm", return immediately with the token type EOFM
  if (w == "eofm")
  {
    tt = EOFM; // Set token type to EOFM (End of File Marker)
    return 0;  // Return as the file has reached the end
  }

  // 2. Check if the word matches any reserved word
  for (int i = 0; i < 18; ++i)
  {
    // If the word is in the reserved words list, set the token type accordingly
    if (w == reservedWords[i])
    {
      tt = reservedType[i]; // Set the token type to the corresponding reserved word type
      return 0;             // Return immediately as a reserved word was found
    }
  }

  // 3. Check if the word matches the PERIOD DFA or the WORD DFA
  // Call the 'period' function to check if the word is a period (".")
  if (period(w))
  {
    tt = PERIOD; // Set the token type to PERIOD if it matches
  }
  // Call the 'word' function to check if it's a valid word
  else if (word(w))
  {
    // If the word matches the word DFA but is not a reserved word,
    // determine the token type (WORD1 or WORD2) based on the last character

    // Get the last character of the word
    char lastChar = w[w.length() - 1];

    // If the last character is a vowel (including 'n'), classify as WORD1
    if (lastChar == 'a' || lastChar == 'i' || lastChar == 'u' || lastChar == 'e' || lastChar == 'o' || lastChar == 'n')
    {
      tt = WORD1; // Set token type to WORD1
    }
    // If the last character is 'E' or 'I', classify as WORD2
    else if (lastChar == 'E' || lastChar == 'I') // Capital 'E' or 'I' specifically
    {
      tt = WORD2; // Set token type to WORD2
    }
  }
  else
  {
    // If neither the period DFA nor the word DFA match, it's a lexical error
    // Set the token type to ERROR
    tt = ERROR;

    // Print an error message to the console
    cout << "Lexical error: " << w << " is not a valid token" << endl;
  }

  // 4. Return the token type and the word (both passed by reference)
  return 0;
} // the end of scanner

// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by: Louis
/*
int main()
{
  tokentype thetype;
  string theword;
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());
  // the loop continues until eofm is returned.
  while (true)
  {
    scanner(thetype, theword); // call the scanner which sets
    // the arguments
    if (theword == "eofm")
      break; // stop now
    cout << "Type is:" << tokenName[thetype] << endl;
    cout << "Word is:" << theword << endl;
  }
  cout << "End of file is encountered." << endl;
  fin.close();
} // end*/
