#include "WordString.h"
#include <sstream>
#include <cctype>

using namespace std;

// Resizes the words and spacesAfter arrays to a new capacity
void WordString::resizeArrays(int newCapacity) {
	string* newWords = new string[newCapacity];
	int* newSpaces = new int[newCapacity];

	// Copy existing data into new arrays
	int copyCount = (wordCount < newCapacity) ? wordCount : newCapacity;
	for (int i = 0; i < copyCount; i++) {
		newWords[i] = words[i];
		newSpaces[i] = spacesAfter[i];
	}

	// Free old memory
	delete[] words;
	delete[] spacesAfter;

	// Update pointers
	words = newWords;
	spacesAfter = newSpaces;
	capacity = newCapacity;
}

// Parses the input string into words and counts spaces after each word
void WordString::parseInput(const string& input) {
	freeMemory(); // Clear any existing data
	if (input.empty()) return;

	// First pass: count number of words
	istringstream iss(input);
	string temp;
	int count = 0;
	while (iss >> temp) count++;

	if (count == 0) return;

	// Initialize arrays with double capacity
	wordCount = count;
	capacity = count * 2;
	words = new string[capacity];
	spacesAfter = new int[capacity]();

	int currentWord = 0;
	size_t pos = 0;

	// Second pass: extract words and count spaces after them
	while (pos < input.size()) {
		// Skip over leading spaces
		while (pos < input.size() && isspace(input[pos])) pos++;
		if (pos >= input.size()) break;

		// Find word boundaries
		size_t wordStart = pos;
		while (pos < input.size() && !isspace(input[pos])) pos++;
		words[currentWord] = input.substr(wordStart, pos - wordStart);

		// Count spaces after the word
		int spaceCount = 0;
		while (pos < input.size() && isspace(input[pos])) {
			spaceCount++;
			pos++;
		}
		spacesAfter[currentWord] = spaceCount;
		currentWord++;
	}
}

// Copies all data from another WordString object
void WordString::copyFrom(const WordString& other) {
	wordCount = other.wordCount;
	capacity = other.capacity;
	words = new string[capacity];
	spacesAfter = new int[capacity];
	for (int i = 0; i < wordCount; i++) {
		words[i] = other.words[i];
		spacesAfter[i] = other.spacesAfter[i];
	}
}

// Frees all dynamically allocated memory
void WordString::freeMemory() {
	delete[] words;
	delete[] spacesAfter;
	words = nullptr;
	spacesAfter = nullptr;
	wordCount = 0;
	capacity = 0;
}

// Default constructor
WordString::WordString() : words(nullptr), spacesAfter(nullptr), wordCount(0), capacity(0) {}

// Constructor from C-string
WordString::WordString(const char* str) : WordString(string(str)) {}

// Constructor from string
WordString::WordString(const string& str) : words(nullptr), spacesAfter(nullptr), wordCount(0), capacity(0) {
	parseInput(str);
}

// Copy constructor
WordString::WordString(const WordString& other) : words(nullptr), spacesAfter(nullptr), wordCount(0), capacity(0) {
	copyFrom(other);
}

// Destructor
WordString::~WordString() {
	freeMemory();
}

// Copy assignment operator
WordString& WordString::operator=(const WordString& other) {
	if (this != &other) {
		freeMemory();
		copyFrom(other);
	}
	return *this;
}

// Returns the full string with spaces reconstructed
string WordString::toString() const {
	string result;
	for (int i = 0; i < wordCount; i++) {
		result += words[i];
		// Add spaces after the word
		if (i < wordCount - 1) {
			result.append(spacesAfter[i], ' ');
		}
	}
	return result;
}

// Returns the number of words
int WordString::numberOfWords() const {
	return wordCount;
}

// Gets the word at a given index, returns empty string if out of bounds
string WordString::get(int index) const {
	if (index < 0 || index >= wordCount) return "";
	return words[index];
}

// Replaces a word at the specified index
void WordString::replace(int index, const string& new_word) {
	if (index < 0 || index >= wordCount) return;
	words[index] = new_word;
}

// Inserts new words after the specified index
void WordString::insertAfter(int index, const string& insertion) {
	if (index < -1 || index >= wordCount) return;

	// Count how many new words we need to insert
	istringstream iss(insertion);
	string temp;
	int newWords = 0;
	while (iss >> temp) newWords++;

	if (newWords == 0) return;

	// Resize arrays if needed
	if (wordCount + newWords >= capacity) {
		resizeArrays((wordCount + newWords) * 2);
	}

	// Shift existing words to the right to make space
	for (int i = wordCount - 1; i > index; i--) {
		words[i + newWords] = words[i];
		spacesAfter[i + newWords] = spacesAfter[i];
	}

	// Insert new words one by one
	iss.clear();
	iss.str(insertion);
	int insertPos = index + 1;
	while (iss >> temp) {
		words[insertPos] = temp;
		// Add space after inserted word, except for the last one
		spacesAfter[insertPos] = (insertPos == wordCount + newWords - 1) ? 0 : 1;
		insertPos++;
	}

	// Make sure the word before the insertion has at least one space
	if (index >= 0) {
		spacesAfter[index] = 1;
	}

	wordCount += newWords;
}

// Removes the word at the specified index
void WordString::remove(int index) {
	if (index < 0 || index >= wordCount) return;

	if (wordCount == 1) {
		freeMemory();
		return;
	}

	// Adjust spaces when removing a word
	if (index == 0) {
		spacesAfter[index] = spacesAfter[index + 1];
	} else if (index == wordCount - 1) {
		// Last word, no adjustment needed
	} else {
		// Combine spaces before and after the removed word
		spacesAfter[index - 1] += spacesAfter[index];
	}

	// Shift remaining words left
	for (int i = index; i < wordCount - 1; i++) {
		words[i] = words[i + 1];
		spacesAfter[i] = spacesAfter[i + 1];
	}

	wordCount--;
}

// Strips extra spaces, sets all spaces to single space
void WordString::strip() {
	for (int i = 0; i < wordCount; i++) {
		spacesAfter[i] = (i < wordCount - 1) ? 1 : 0;
	}
}

// Stream output operator: prints WordString
ostream& operator<<(ostream& os, const WordString& ws) {
	os << ws.toString();
	return os;
}

// Stream input operator: reads WordString
istream& operator>>(istream& is, WordString& ws) {
	string input;
	getline(is, input);
	ws.parseInput(input);
	return is;
}

// Concatenation operator with another WordString
WordString WordString::operator+(const WordString& other) const {
	WordString result(*this);
	result.insertAfter(result.wordCount - 1, other.toString());
	return result;
}

// Concatenation operator with string
WordString WordString::operator+(const string& str) const {
	WordString result(*this);
	result.insertAfter(result.wordCount - 1, str);
	return result;
}

// Equality operator: compares words and spaces
bool WordString::operator==(const WordString& other) const {
	if (wordCount != other.wordCount) return false;
	for (int i = 0; i < wordCount; i++) {
		if (words[i] != other.words[i] || spacesAfter[i] != other.spacesAfter[i]) {
			return false;
		}
	}
	return true;
}

