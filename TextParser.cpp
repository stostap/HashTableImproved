#include "TextParser.h"
#include <fstream>
#include <cctype>
#include <iostream>

TextParser::TextParser(const string& filePath) : filePath(filePath) {}

// Helper function to determine if a character is a punctuation mark
bool TextParser::isPunctuation(char c) {
    // TODO(ostap): fix UTF-8 coding properly
    if (c == '’') {
        return false;
    }
    if (c == '“') {
        return true;
    }
    if (c == '”') {
        return true;
    }
    if (c == '‘') {
        return true;
    }
    if (c == 'é') {
        return false;
    }
    if (c == 'è') {
        return false;
    }
    return ispunct(c) && c != '\''; // Allow apostrophes inside words
}

// Function to parse and extract words
vector<string> TextParser::parseWords() {
    ifstream file(filePath);
    vector<string> words;
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << endl;
        return words;
    }

    string word;
    while (file >> word) {
        string cleanWord;
        for (char c : word) {
            if (!isPunctuation(c)) {
                cleanWord += c;
            }
        }
        if (!cleanWord.empty()) {
            words.push_back(cleanWord);  // Store the cleaned word
        }
    }

    file.close();
    return words;
}
