// Include guards to prevent multiple inclusions of this header file
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

// Include standard exception library for exception base class
#include <exception>
// Include string library for string operations
#include <string>

// MissingFieldException class
// Thrown when a required field is missing in an entry
class MissingFieldException : public std::exception {
public:
    // Override the what() method to provide a custom error message
    // noexcept specifier indicates this function doesn't throw exceptions
    const char* what() const noexcept override {
        // Return a descriptive error message for missing field
        return "Exception: missing field";
    }
};

// DuplicateEntryException class
// Thrown when an entry with the same first field already exists
class DuplicateEntryException : public std::exception {
public:
    // Override the what() method to provide a custom error message
    // noexcept specifier indicates this function doesn't throw exceptions
    const char* what() const noexcept override {
        // Return a descriptive error message for duplicate entry
        return "Exception: duplicate entry";
    }
};

// WrongCommandException class
// Thrown when a command is not recognized or has incorrect format
class WrongCommandException : public std::exception {
public:
    // Override the what() method to provide a custom error message
    // noexcept specifier indicates this function doesn't throw exceptions
    const char* what() const noexcept override {
        // Return a descriptive error message for wrong command
        return "Exception: command is wrong";
    }
};

// End of include guard
#endif // EXCEPTIONS_H