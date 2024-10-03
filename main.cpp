#include "HashTableTests.h"
#include "TextParser.h"
#include <iostream>
#include "HashTable.h"

int main() {
    runTests();  // Run all the tests. Only for HashTable atm.

    TextParser parser("98-0.txt");  // Provide the path to your text file
    vector<string> words = parser.parseWords(); // ~140k different words
    cout << "Dict size: " << words.size() << endl;

    HashTable ht(int(words.size() * 1.2));
    // Insert all words into the hash table with auto-incrementing values
    for (size_t i = 0; i < words.size(); ++i) {
        ht.insert(words[i], i + 1); 
    }
    return 0;
}
