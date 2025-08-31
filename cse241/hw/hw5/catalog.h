// Include guards to prevent multiple inclusions of this header file
#ifndef CATALOG_H
#define CATALOG_H

// Standard library includes for various functionality
#include <vector>          // For storing collections of data
#include <string>          // For string handling
#include <fstream>         // For file I/O operations
#include <map>             // For key-value pair storage
#include <set>             // For storing unique elements
#include <algorithm>       // For algorithms like sorting
#include <sstream>         // For string stream operations
#include "entry.h"         // Include custom Entry class definition
#include "exceptions.h"    // Include custom exception classes

// The main Catalog class for managing catalog data and operations
class Catalog {
public:
    // Constructor that opens the output file
    // Takes the output filename as a parameter
    Catalog(const std::string& outputFilename) {
        // Open the output file for writing
        outputFile.open(outputFilename);
        // Check if the file was opened successfully
        if (!outputFile.is_open()) {
            // Throw an exception if the file couldn't be opened
            throw std::runtime_error("Cannot open output file: " + outputFilename);
        }
    }
    
    // Destructor to clean up resources
    ~Catalog() {
        // Close the output file if it's still open
        if (outputFile.is_open()) {
            outputFile.close();
        }
    }
    
    // Process data.txt file to read catalog data
    // Takes the data filename as a parameter
    void processDataFile(const std::string& filename);
    
    // Process commands.txt file to execute commands on the catalog
    // Takes the commands filename as a parameter
    void processCommandsFile(const std::string& filename);
    
private:
    // Store the format of each field in the catalog
    std::vector<FieldFormat> fieldFormats;
    
    // Store all the entries in the catalog
    std::vector<Entry> entries;
    
    // File stream for writing output to the log file
    std::ofstream outputFile;
    
    // Parse the field format line from data.txt
    // Takes a line from the file as a parameter
    void parseFieldFormat(const std::string& line);
    
    // Parse an entry line from data.txt
    // Takes a line from the file as a parameter
    void parseEntry(const std::string& line);
    
    // Execute a search command
    // Takes the search value and field name as parameters
    void executeSearch(const std::string& value, const std::string& fieldName);
    
    // Execute a sort command
    // Takes the field name to sort by as a parameter
    void executeSort(const std::string& fieldName);
    
    // Check if an entry has a missing field
    // Takes a vector of field values as a parameter
    bool hasMissingField(const std::vector<std::string>& values);
    
    // Check if an entry is a duplicate based on the first field
    // Takes the first field value as a parameter
    bool isDuplicate(const std::string& firstField);
    
    // Format an entry as a string for output
    // Takes an Entry object as a parameter
    std::string formatEntry(const Entry& entry);
    
    // Create a string field based on the value and field type
    // Takes the field value and field type as parameters
    FieldBase* createStringField(const std::string& value, FieldT fieldType);
    
    // Create an integer field based on the value and field type
    // Takes the field value and field type as parameters
    FieldBase* createIntField(const std::string& value, FieldT fieldType);
    
    // Create a double field based on the value and field type
    // Takes the field value and field type as parameters
    FieldBase* createDoubleField(const std::string& value, FieldT fieldType);
    
    // Create a boolean field based on the value and field type
    // Takes the field value and field type as parameters
    FieldBase* createBoolField(const std::string& value, FieldT fieldType);
    
    // Find the index of a field by name
    // Takes the field name as a parameter
    int findFieldIndex(const std::string& fieldName);
    
    // Comparator struct for sorting entries
    struct EntryComparator {
        // Reference to the format of the field to compare
        const FieldFormat& format;
        
        // Index of the field to compare
        int fieldIndex;
        
        // Constructor that initializes the format and field index
        EntryComparator(const FieldFormat& format, int fieldIndex)
            : format(format), fieldIndex(fieldIndex) {}
        
        // Comparison operator for sorting entries
        // Takes two Entry objects as parameters
        bool operator()(const Entry& e1, const Entry& e2) const;
    };
};

// End of include guard
#endif // CATALOG_H