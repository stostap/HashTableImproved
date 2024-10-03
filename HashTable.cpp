#include "HashTable.h"

// Constructor to initialize the hash table
HashTable::HashTable(int size) : size(size) {
    table = new HashEntry[size];  // Allocate a fixed-size array
    firstInsertedIndex = -1;
    lastInsertedIndex = -1;

    // Initialize the table with unoccupied entries
    for (int i = 0; i < size; ++i) {
        table[i].prev = -1;
        table[i].next = -1;
        table[i].isOccupied = false;
        table[i].isDeleted = false;
    }
}

// Destructor to clean up the allocated memory
HashTable::~HashTable() {
    delete[] table;  // Deallocate the fixed-size array
}

// Hash function to map a string key to an index
int HashTable::hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch + size) % size;  // Simple polynomial hash
    }
    return hash;
}

// Insert or update a key-value pair
void HashTable::insert(const string& key, int value) {
    int index = hashFunction(key);
    int originalIndex = index;

    // Linear probing to handle collisions
    while (table[index].isOccupied && table[index].key != key) {
        index = (index + 1) % size;
        if (index == originalIndex) {
            cout << "Hash table is full!" << endl;
            return;
        }
    }

    bool isNewInsertion = !table[index].isOccupied || table[index].isDeleted;

    // Insert the new key-value pair
    table[index].key = key;
    table[index].value = value;
    table[index].isOccupied = true;
    table[index].isDeleted = false;

    if (isNewInsertion) {
        // Add to the doubly linked list
        if (firstInsertedIndex == -1) {  // First ever element
            firstInsertedIndex = index;
            lastInsertedIndex = index;
        }
        else {
            table[lastInsertedIndex].next = index;
            table[index].prev = lastInsertedIndex;
            lastInsertedIndex = index;
        }
    }
    else {
        // If updated, move to the end if it's not already the last inserted
        if (lastInsertedIndex != index) {
            removeFromList(index);
            table[lastInsertedIndex].next = index;
            table[index].prev = lastInsertedIndex;
            lastInsertedIndex = index;
        }
    }
}

// Remove a key from the hash table
void HashTable::remove(const string& key) {
    int index = hashFunction(key);
    int originalIndex = index;
    bool found = false;

    // Linear probing to find the key
    while (table[index].isOccupied) {
        if (table[index].key == key && !table[index].isDeleted) {
            found = true;
            break;
        }
        index = (index + 1) % size;
        if (index == originalIndex) {
            break;
        }
    }

    if (found) {
        table[index].isDeleted = true;
        table[index].isOccupied = false;
        removeFromList(index);
    }
    else {
        cout << "Key not found!" << endl;
    }
}

// Helper function to remove an entry from the doubly linked list
void HashTable::removeFromList(int index) {
    int prevIndex = table[index].prev;
    int nextIndex = table[index].next;

    if (prevIndex != -1) {
        table[prevIndex].next = nextIndex;
    }
    if (nextIndex != -1) {
        table[nextIndex].prev = prevIndex;
    }

    if (index == firstInsertedIndex) {
        firstInsertedIndex = nextIndex;
    }
    if (index == lastInsertedIndex) {
        lastInsertedIndex = prevIndex;
    }

    table[index].prev = -1;
    table[index].next = -1;
}

// Get a value associated with a key
int HashTable::get(const string& key) {
    int index = hashFunction(key);
    int originalIndex = index;

    // Linear probing to find the key
    while (table[index].isOccupied) {
        if (table[index].key == key && !table[index].isDeleted) {
            return table[index].value;  // Return the associated value
        }
        index = (index + 1) % size;
        if (index == originalIndex) {
            break;
        }
    }

    return -1;  // Key not found
}

// Get the most recently inserted or updated key-value pair
pair<string, int> HashTable::get_last() {
    if (lastInsertedIndex != -1 && table[lastInsertedIndex].isOccupied && !table[lastInsertedIndex].isDeleted) {
        return { table[lastInsertedIndex].key, table[lastInsertedIndex].value };
    }
    else {
        return { "", -1 };  // No valid entry found
    }
}

// Get the least recently inserted or updated key-value pair
pair<string, int> HashTable::get_first() {
    if (firstInsertedIndex != -1 && table[firstInsertedIndex].isOccupied && !table[firstInsertedIndex].isDeleted) {
        return { table[firstInsertedIndex].key, table[firstInsertedIndex].value };
    }
    else {
        return { "", -1 };  // No valid entry found
    }
}
