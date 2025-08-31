#ifndef WORDSTRING_H
#define WORDSTRING_H

#include <string>
#include <iostream>

// The WordString class is a custom string class that stores words and the spaces after them.
class WordString {
private:
	std::string* words;		// Dynamically allocated array of words
	int* spacesAfter;		// Dynamically allocated array of space counts after each word
	int wordCount;		// Number of words stored
	int capacity;		// Current capacity of the arrays

	// Resizes the arrays to the new capacity
	void resizeArrays(int newCapacity);

	// Parses the input string and fills the words and spacesAfter arrays
	void parseInput(const std::string& input);

	// Copies data from another WordString object
	void copyFrom(const WordString& other);

	// Frees dynamically allocated memory
	void freeMemory();

public:
	// Constructors & Destructor
	WordString();					// Default constructor
	WordString(const char* str);			// Constructor from C-string
	WordString(const std::string& str);		// Constructor from std::string
	WordString(const WordString& other);		// Copy constructor
	~WordString();					// Destructor
	
	// Assignment operator
	WordString& operator=(const WordString& other);	// Copy assignment operator

	// Core functionality
	std::string toString() const;			// Returns the combined string with spaces
	int numberOfWords() const;			// Returns the number of words
	std::string get(int index) const;		// Returns the word at the given index
	void replace(int index, const std::string& new_word);	// Replaces a word at the given index
	void insertAfter(int index, const std::string& insertion);	// Inserts new words after the given index
	void remove(int index);			// Removes the word at the given index
	void strip();				// Removes extra spaces (sets all to single space)

	// Operators
	friend std::ostream& operator<<(std::ostream& os, const WordString& ws);	// Stream output operator
	friend std::istream& operator>>(std::istream& is, WordString& ws);	// Stream input operator
	WordString operator+(const WordString& other) const;	// Concatenation with another WordString
	WordString operator+(const std::string& str) const;	// Concatenation with std::string
	bool operator==(const WordString& other) const;	// Equality comparison
};

#endif

