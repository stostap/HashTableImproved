#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <utility>

using namespace std;

struct HashEntry {
    string key;
    int value;
    bool isOccupied;
    bool isDeleted;
    int prev;  // Previous element in the insertion order
    int next;  // Next element in the insertion order

    // Constructor
    HashEntry() : isOccupied(false), isDeleted(false), prev(-1), next(-1) {}
};

class HashTable {
private:
    HashEntry* table;  // Fixed-size array for the hash table
    int size;          // Size of the hash table
    int firstInsertedIndex;   // Tracks the first inserted element
    int lastInsertedIndex;    // Tracks the last inserted element

    // Hash function to map keys to table indices
    int hashFunction(const string& key);

    // Removes an entry from the doubly linked list (helper function)
    void removeFromList(int index);

public:
    // Constructor to initialize the hash table
    HashTable(int size);

    // Destructor to clean up the allocated memory
    ~HashTable();

    // Insert or update a key-value pair
    void insert(const string& key, int value);

    // Remove a key from the hash table
    void remove(const string& key);

    // Get a value associated with a key
    int get(const string& key);

    // Get the most recently inserted or updated key-value pair
    pair<string, int> get_last();

    // Get the least recently inserted or updated key-value pair
    pair<string, int> get_first();
};

#endif // HASHTABLE_H
