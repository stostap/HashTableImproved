#pragma once
#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#include <string>
#include <vector>

using namespace std;

class TextParser {
public:
    TextParser(const string& filePath);
    vector<string> parseWords(); // Extracts all words without punctuation, keeping capitalization

private:
    string filePath;
    bool isPunctuation(char c);
};

#endif
