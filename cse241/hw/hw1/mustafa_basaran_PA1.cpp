#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int MAX_ATTEMPTS = 100;	// Maximum number of attempts allowed
const int MAX_ALPHABET = 256;	// Maximum number of alphabet characters

// Function to read the alphabet from "alphabet.txt" and return it as a string
string readAlphabet(const string &filename) {
	ifstream file(filename);	// Open the file
	if (!file) {
		return "";	// Return an empty string if the file cannot be opened
	}

	string alphabet = "";	// To store unique characters from the file
	char ch;
	
	while (file.get(ch)) {	// Read character by character
		if (ch != ' ' && ch != ',' && ch != '\n' && alphabet.find(ch) == string::npos) {
			alphabet += ch;	// Add the character if it's not a space/comma/newline and not already in the alphabet
		}
	}
	
	return alphabet;	// Return the final processed alphabet
}

// Function to generate a random word of given length from the alphabet
string generateRandomWord(string alphabet, int length) {
	string word = "";	// The resulting random word
	srand(time(0));	// Seed the random number generator with the current time

	for (int i = 0; i < length; i++) {
		int index = rand() % alphabet.length();	// Pick a random index
		word += alphabet[index];	// Append the selected character to the word
		alphabet.erase(index, 1);	// Remove the selected character to ensure uniqueness
	}

	return word;
}

// Function to validate if a given word is valid according to the rules
bool isValidWord(const string &word, const string &alphabet) {
	if (word.empty()) return false;	// If the word is empty, it's invalid

	for (int i = 0; i < word.length(); i++) {
		if (alphabet.find(word[i]) == string::npos) {
			return false;	// The word contains a character not present in the alphabet
		}
		for (int j = i + 1; j < word.length(); j++) {
			if (word[i] == word[j]) {
				return false;	// The word contains duplicate characters (not allowed)
			}
		}
	}

	return true;	// The word passes all checks and is valid
}

// Function to calculate Cexact (correct position matches) and Cmisplaced (wrong position matches)
void calculateHints(const string &secret, const string &guess, int &Cexact, int &Cmisplaced) {
	Cexact = 0;
	Cmisplaced = 0;

	for (int i = 0; i < secret.length(); i++) {
		if (guess[i] == secret[i]) {
			Cexact++;	// Correct character in the correct position
		} else if (secret.find(guess[i]) != string::npos) {
			Cmisplaced++;	// Correct character but in the wrong position
		}
	}
}

int main(int argc, char *argv[]) {
	// Check if the correct number of arguments is provided
	if (argc != 3) {
		cout << "INPUT ERROR" << endl;
		return 0;
	}

	string mode = argv[1];	// Read the first argument (-r or -u)
	
	// Validate mode
	if (mode != "-r" && mode != "-u") {
		cout << "INPUT ERROR" << endl;
		return 0;
	}

	// Read the alphabet from "alphabet.txt"
	string alphabet = readAlphabet("alphabet.txt");
	if (alphabet.empty()) {
		cout << "INPUT ERROR" << endl;
		return 0;
	}

	string secret;	// The secret word to be guessed
	int wordLength;

	// If mode is "-r", generate a random word
	if (mode == "-r") {
		wordLength = atoi(argv[2]);	// Convert string argument to integer

		if (wordLength <= 0 || wordLength > (int)alphabet.length()) { // length() returns size_t(unsigned) thats why casting. cant compare size_t with int
			cout << "INPUT ERROR" << endl;
			return 0;
		}

		secret = generateRandomWord(alphabet, wordLength);	// Generate a random secret word
	}
	// If mode is "-u", use the provided word as the secret word
	else {
		secret = argv[2];
		wordLength = secret.length();

		if (!isValidWord(secret, alphabet)) {
			cout << "INPUT ERROR" << endl;
			return 0;
		}
	}

	// Print the alphabet in the required format
	cout << "[";
	for (int i = 0; i < alphabet.length(); i++) {
		cout << alphabet[i];
		if (i != alphabet.length() - 1) {
			cout << ",";
		}
	}
	cout << "]" << endl;

	int attempts = 0;	// Counter for the number of attempts
	string guess;	// Variable to store the user's guess
	
	// Game loop: The user has up to MAX_ATTEMPTS (100) tries
	while (attempts < MAX_ATTEMPTS) {
		attempts++;	// Increment attempt count
		cin >> guess;	// Read user input

		// Validate the guessed word
		if (!isValidWord(guess, alphabet) || (int)guess.length() != wordLength) {
			cout << "INPUT ERROR" << endl;
			return 0;
		}

		// Calculate hints (Cexact and Cmisplaced)
		int Cexact, Cmisplaced;
		calculateHints(secret, guess, Cexact, Cmisplaced);
		cout << Cexact << " " << Cmisplaced << endl;

		// If the guessed word matches the secret word, print FOUND and exit
		if (Cexact == wordLength) {
			cout << "FOUND " << attempts << endl;
			return 0;
		}
	}

	// If the user fails to guess the word within 100 attempts, print "FAILED"
	cout << "FAILED" << endl;
	return 0;
}

