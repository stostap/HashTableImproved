#include "HashTableTests.h"
#include "HashTable.h"
#include <iostream>

void runTests() {
    HashTable ht(10);

    // Test 1: Insert and get
    ht.insert("apple", 1);
    ht.insert("banana", 2);
    ht.insert("cherry", 3);
    cout << "Test 1: Insert and Get -> "
        << (ht.get("apple") == 1 && ht.get("banana") == 2 && ht.get("cherry") == 3 ? "Passed" : "Failed")
        << endl;

    // Test 2: Get non-existing key
    cout << "Test 2: Get non-existing key -> "
        << (ht.get("grape") == -1 ? "Passed" : "Failed")
        << endl;

    // Test 3: Remove a key
    ht.remove("banana");
    cout << "Test 3: Remove -> "
        << (ht.get("banana") == -1 ? "Passed" : "Failed")
        << endl;

    // Test 4: Get last inserted/updated key
    auto last = ht.get_last();
    cout << "Test 4: Get last -> "
        << (last.first == "cherry" && last.second == 3 ? "Passed" : "Failed")
        << endl;

    // Test 5: Update existing key
    ht.insert("apple", 10);
    cout << "Test 5: Update key -> "
        << (ht.get("apple") == 10 ? "Passed" : "Failed")
        << endl;

    // Test 6: Get first inserted key
    auto first = ht.get_first();
    cout << "Test 6: Get first -> "
        << (first.first == "cherry" && first.second == 3 ? "Passed" : "Failed")
        << endl;

    // Test 7: Remove first inserted key
    ht.remove("cherry");
    first = ht.get_first();
    cout << "Test 7: Remove first -> "
        << (first.first == "apple" && first.second == 10 ? "Passed" : "Failed")
        << endl;
}
