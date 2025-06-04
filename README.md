# Basic Japanese Translator
This project implements a basic Japanese-to-English translator using a combination of Deterministic Finite Automata (DFA) for lexical analysis and recursive descent parsing for syntax analysis. It processes Japanese-like phonetic input, parses its grammatical structure, and outputs an English translation based on a predefined lexicon.

1. Lexical Analysis (scanner.cpp): Uses custom-built DFAs to identify valid words, reserved keywords, and punctuation.
2. Syntax Parsing (parser.cpp): Employs recursive descent parsing to ensure the sentence follows defined grammar rules.
3. Semantic Translation (translator.cpp): Loads a lexicon from file and translates recognized words into English, generating an intermediate representation of the translation.

Error Handling: Provides clear syntax error messages and logs them to errors.txt.

Tracing Option: Optional debug output to trace parsing steps.

NOTE: This project is for learning purposes only. Do not copy or submit as your own in any academic setting.
