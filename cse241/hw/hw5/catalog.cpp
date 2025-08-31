// Include the catalog header file
#include "catalog.h"
// Include standard I/O stream library
#include <iostream>
// Include algorithm library for sorting functionality
#include <algorithm>
// Include regex library for command parsing
#include <regex>

// Process the data file and build the catalog
void Catalog::processDataFile(const std::string& filename) {
    // Open the data file for reading
    std::ifstream dataFile(filename);
    // Check if the file was opened successfully
    if (!dataFile.is_open()) {
        // Throw an exception if the file couldn't be opened
        throw std::runtime_error("Cannot open data file: " + filename);
    }
    
    // String to hold each line read from the file
    std::string line;
    
    // Read and parse the first line (field format)
    if (std::getline(dataFile, line)) {
        // Parse the field format line to extract field information
        parseFieldFormat(line);
    }
    
    // Read and parse entries from the data file
    while (std::getline(dataFile, line)) {
        try {
            // Try to parse the entry
            parseEntry(line);
        } catch (const MissingFieldException& e) {
            // Handle missing field exception
            outputFile << e.what() << std::endl;
            // Output the entry with missing fields
            outputFile << line << std::endl;
        } catch (const DuplicateEntryException& e) {
            // Handle duplicate entry exception
            outputFile << e.what() << std::endl;
            // Output the duplicate entry
            outputFile << line << std::endl;
        }
    }
    
    // Close the data file after reading
    dataFile.close();
    
    // Output the number of unique entries to the log file
    outputFile << entries.size() << " unique entries" << std::endl;
}

// Process the commands file and execute the commands
void Catalog::processCommandsFile(const std::string& filename) {
    // Open the commands file for reading
    std::ifstream commandsFile(filename);
    // Check if the file was opened successfully
    if (!commandsFile.is_open()) {
        // Throw an exception if the file couldn't be opened
        throw std::runtime_error("Cannot open commands file: " + filename);
    }
    
    // String to hold each line read from the file
    std::string line;
    // Read each line from the commands file
    while (std::getline(commandsFile, line)) {
        // Output the command to the log file
        outputFile << line << std::endl;
        
        try {
            // Check if the line starts with "search " and contains " in "
            if (line.substr(0, 7) == "search " && line.find(" in ") != std::string::npos) {
                // Find the positions of the quotes in the search command
                size_t firstQuotePos = line.find("\"");
                size_t secondQuotePos = line.find("\"", firstQuotePos + 1);
                size_t thirdQuotePos = line.find("\"", secondQuotePos + 1);
                size_t fourthQuotePos = line.find("\"", thirdQuotePos + 1);
                
                // Ensure all quotes are found
                if (firstQuotePos != std::string::npos && secondQuotePos != std::string::npos &&
                    thirdQuotePos != std::string::npos && fourthQuotePos != std::string::npos) {
                    
                    // Extract the search value and field name from the command
                    std::string value = line.substr(firstQuotePos + 1, secondQuotePos - firstQuotePos - 1);
                    std::string fieldName = line.substr(thirdQuotePos + 1, fourthQuotePos - thirdQuotePos - 1);
                    
                    // Execute the search command
                    executeSearch(value, fieldName);
                } else {
                    // Throw exception if the command format is incorrect
                    throw WrongCommandException();
                }
            }
            // Check if the line starts with "sort "
            else if (line.substr(0, 5) == "sort ") {
                // Find the positions of the quotes in the sort command
                size_t firstQuotePos = line.find("\"");
                size_t secondQuotePos = line.find("\"", firstQuotePos + 1);
                
                // Ensure both quotes are found
                if (firstQuotePos != std::string::npos && secondQuotePos != std::string::npos) {
                    // Extract the field name from the command
                    std::string fieldName = line.substr(firstQuotePos + 1, secondQuotePos - firstQuotePos - 1);
                    // Execute the sort command
                    executeSort(fieldName);
                } else {
                    // Throw exception if the command format is incorrect
                    throw WrongCommandException();
                }
            }
            else {
                // Throw exception for unrecognized commands
                throw WrongCommandException();
            }
        } catch (const WrongCommandException& e) {
            // Log the wrong command exception
            outputFile << e.what() << std::endl;
        }
    }
    
    // Close the commands file after processing
    commandsFile.close();
}

// Parse the field format line from the data file
void Catalog::parseFieldFormat(const std::string& line) {
    // Create a string stream from the line
    std::stringstream ss(line);
    // String to hold each field descriptor
    std::string fieldDesc;
    
    // Parse each field format descriptor separated by '|'
    while (std::getline(ss, fieldDesc, '|')) {
        // Create a string stream for the field descriptor
        std::stringstream fieldSs(fieldDesc);
        // Strings to hold the field name, type, and array type
        std::string name, type, arrayType;
        
        // Parse field_name:field_type:is_array_or_not
        std::getline(fieldSs, name, ':');
        std::getline(fieldSs, type, ':');
        std::getline(fieldSs, arrayType);
        
        // Create a field format structure
        FieldFormat format;
        // Set the field name
        format.name = name;
        
        // Set the field type based on the string
        if (type == "string") format.type = DataT::S;
        else if (type == "integer") format.type = DataT::I;
        else if (type == "double") format.type = DataT::D;
        else if (type == "bool") format.type = DataT::B;
        
        // Set whether the field is single or multi based on the string
        if (arrayType == "single") format.sm = FieldT::single;
        else if (arrayType == "multi") format.sm = FieldT::multi;
        
        // Add the field format to the vector
        fieldFormats.push_back(format);
        
        // Output field names to the log file
        if (fieldFormats.size() > 1) {
            outputFile << "|";
        }
        outputFile << name;
    }
    // End the line in the log file
    outputFile << std::endl;
}

// Parse an entry line from the data file
void Catalog::parseEntry(const std::string& line) {
    // Create a string stream from the line
    std::stringstream ss(line);
    // String to hold each field value
    std::string fieldValue;
    // Vector to hold all field values
    std::vector<std::string> values;
    
    // Split the entry line by '|'
    while (std::getline(ss, fieldValue, '|')) {
        // Add each field value to the vector
        values.push_back(fieldValue);
    }
    
    // Check for missing fields
    if (hasMissingField(values)) {
        // Throw exception if any required fields are missing
        throw MissingFieldException();
    }
    
    // Check for duplicates (first field match)
    if (!values.empty() && isDuplicate(values[0])) {
        // Throw exception if this entry is a duplicate
        throw DuplicateEntryException();
    }
    
    // Create a new entry
    Entry entry;
    
    // Process each field in the entry
    for (size_t i = 0; i < values.size() && i < fieldFormats.size(); ++i) {
        // Pointer to the field base class
        FieldBase* field = nullptr;
        
        // Create the appropriate field based on its type
        switch (fieldFormats[i].type) {
            case DataT::S:
                // Create a string field
                field = createStringField(values[i], fieldFormats[i].sm);
                break;
            case DataT::I:
                // Create an integer field
                field = createIntField(values[i], fieldFormats[i].sm);
                break;
            case DataT::D:
                // Create a double field
                field = createDoubleField(values[i], fieldFormats[i].sm);
                break;
            case DataT::B:
                // Create a boolean field
                field = createBoolField(values[i], fieldFormats[i].sm);
                break;
        }
        
        // Add the field to the entry if it was created successfully
        if (field) {
            entry.fields.push_back(field);
        }
    }
    
    // Add the entry to the collection
    entries.push_back(entry);
}

// Create a string field (single or multi)
FieldBase* Catalog::createStringField(const std::string& value, FieldT fieldType) {
    // Check if the field is single or multi
    if (fieldType == FieldT::single) {
        // Create a single string field
        return new FieldSingle<std::string>(value);
    } else {
        // Create a vector to hold multiple string values
        std::vector<std::string> values;
        // Create a string stream from the value
        std::stringstream ss(value);
        // String to hold each item
        std::string item;
        
        // Split the value by ':'
        while (std::getline(ss, item, ':')) {
            // Add each item to the vector
            values.push_back(item);
        }
        
        // Create a multi string field
        return new FieldMulti<std::string>(values);
    }
}

// Create an integer field (single or multi)
FieldBase* Catalog::createIntField(const std::string& value, FieldT fieldType) {
    // Check if the field is single or multi
    if (fieldType == FieldT::single) {
        // Handle empty values
        if (value.empty()) return new FieldSingle<int>(0);
        // Create a single integer field
        return new FieldSingle<int>(std::stoi(value));
    } else {
        // Create a vector to hold multiple integer values
        std::vector<int> values;
        // Create a string stream from the value
        std::stringstream ss(value);
        // String to hold each item
        std::string item;
        
        // Split the value by ':'
        while (std::getline(ss, item, ':')) {
            // Skip empty items
            if (!item.empty()) {
                // Convert to integer and add to the vector
                values.push_back(std::stoi(item));
            }
        }
        
        // Create a multi integer field
        return new FieldMulti<int>(values);
    }
}

// Create a double field (single or multi)
FieldBase* Catalog::createDoubleField(const std::string& value, FieldT fieldType) {
    // Check if the field is single or multi
    if (fieldType == FieldT::single) {
        // Handle empty values
        if (value.empty()) return new FieldSingle<double>(0.0);
        // Create a single double field
        return new FieldSingle<double>(std::stod(value));
    } else {
        // Create a vector to hold multiple double values
        std::vector<double> values;
        // Create a string stream from the value
        std::stringstream ss(value);
        // String to hold each item
        std::string item;
        
        // Split the value by ':'
        while (std::getline(ss, item, ':')) {
            // Skip empty items
            if (!item.empty()) {
                // Convert to double and add to the vector
                values.push_back(std::stod(item));
            }
        }
        
        // Create a multi double field
        return new FieldMulti<double>(values);
    }
}

// Create a boolean field (single or multi)
FieldBase* Catalog::createBoolField(const std::string& value, FieldT fieldType) {
    // Check if the field is single or multi
    if (fieldType == FieldT::single) {
        // Handle empty values
        if (value.empty()) return new FieldSingle<bool>(false);
        // Create a single boolean field (true if value is "true" or "1")
        return new FieldSingle<bool>(value == "true" || value == "1");
    } else {
        // Create a vector to hold multiple boolean values
        std::vector<bool> values;
        // Create a string stream from the value
        std::stringstream ss(value);
        // String to hold each item
        std::string item;
        
        // Split the value by ':'
        while (std::getline(ss, item, ':')) {
            // Skip empty items
            if (!item.empty()) {
                // Convert to boolean and add to the vector (true if item is "true" or "1")
                values.push_back(item == "true" || item == "1");
            }
        }
        
        // Create a multi boolean field
        return new FieldMulti<bool>(values);
    }
}

// Check if an entry has missing fields
bool Catalog::hasMissingField(const std::vector<std::string>& values) {
    // If number of values is less than number of formats, some fields are missing
    if (values.size() < fieldFormats.size()) {
        return true;
    }
    
    // Check if any required single field is empty
    for (size_t i = 0; i < values.size() && i < fieldFormats.size(); ++i) {
        // Consider all single fields as required
        if (values[i].empty() && fieldFormats[i].sm == FieldT::single) {
            return true;
        }
    }
    
    // No missing fields found
    return false;
}

// Check if an entry is a duplicate based on the first field
bool Catalog::isDuplicate(const std::string& firstField) {
    // Check if any existing entry has the same first field
    for (const auto& entry : entries) {
        // Skip entries with no fields
        if (entry.fields.empty()) continue;
        
        // Check if the first field type is string and single
        if (fieldFormats[0].type == DataT::S && fieldFormats[0].sm == FieldT::single) {
            // Cast to the appropriate field type
            auto field = static_cast<FieldSingle<std::string>*>(entry.fields[0]);
            // Compare the field value with the first field of the new entry
            if (field->getdata() == firstField) {
                return true;
            }
        }
    }
    
    // No duplicate found
    return false;
}

// Format an entry as a string for output
std::string Catalog::formatEntry(const Entry& entry) {
    // String stream to build the formatted entry
    std::stringstream ss;
    
    // Process each field in the entry
    for (size_t i = 0; i < entry.fields.size(); ++i) {
        // Add separator between fields
        if (i > 0) {
            ss << "|";
        }
        
        // Get the field
        const FieldBase* field = entry.fields[i];
        
        // Handle single and multi fields differently
        if (field->gettype() == FieldT::single) {
            // Handle different data types
            switch (fieldFormats[i].type) {
                case DataT::S: {
                    // Cast to single string field
                    auto f = static_cast<const FieldSingle<std::string>*>(field);
                    // Add the string value
                    ss << f->getdata();
                    break;
                }
                case DataT::I: {
                    // Cast to single integer field
                    auto f = static_cast<const FieldSingle<int>*>(field);
                    // Add the integer value
                    ss << f->getdata();
                    break;
                }
                case DataT::D: {
                    // Cast to single double field
                    auto f = static_cast<const FieldSingle<double>*>(field);
                    // Add the double value
                    ss << f->getdata();
                    break;
                }
                case DataT::B: {
                    // Cast to single boolean field
                    auto f = static_cast<const FieldSingle<bool>*>(field);
                    // Add the boolean value as "true" or "false"
                    ss << (f->getdata() ? "true" : "false");
                    break;
                }
            }
        } else { // MULTI
            // Handle different data types for multi fields
            switch (fieldFormats[i].type) {
                case DataT::S: {
                    // Cast to multi string field
                    auto f = static_cast<const FieldMulti<std::string>*>(field);
                    // Add each string value separated by ':'
                    for (int j = 0; j < f->getsize(); ++j) {
                        if (j > 0) ss << ":";
                        ss << f->getdata(j);
                    }
                    break;
                }
                case DataT::I: {
                    // Cast to multi integer field
                    auto f = static_cast<const FieldMulti<int>*>(field);
                    // Add each integer value separated by ':'
                    for (int j = 0; j < f->getsize(); ++j) {
                        if (j > 0) ss << ":";
                        ss << f->getdata(j);
                    }
                    break;
                }
                case DataT::D: {
                    // Cast to multi double field
                    auto f = static_cast<const FieldMulti<double>*>(field);
                    // Add each double value separated by ':'
                    for (int j = 0; j < f->getsize(); ++j) {
                        if (j > 0) ss << ":";
                        ss << f->getdata(j);
                    }
                    break;
                }
                case DataT::B: {
                    // Cast to multi boolean field
                    auto f = static_cast<const FieldMulti<bool>*>(field);
                    // Add each boolean value as "true" or "false" separated by ':'
                    for (int j = 0; j < f->getsize(); ++j) {
                        if (j > 0) ss << ":";
                        ss << (f->getdata(j) ? "true" : "false");
                    }
                    break;
                }
            }
        }
    }
    
    // Return the formatted entry string
    return ss.str();
}

// Execute a search command
void Catalog::executeSearch(const std::string& value, const std::string& fieldName) {
    // Find the index of the specified field
    int fieldIndex = findFieldIndex(fieldName);
    
    // If the field is not found, throw an exception
    if (fieldIndex == -1) {
        throw WrongCommandException();
    }
    
    // Flag to track if any matches were found
    bool foundAny = false;
    
    // Find entries that match the search criteria
    for (const auto& entry : entries) {
        // Skip entries that don't have the specified field
        if (fieldIndex >= static_cast<int>(entry.fields.size())) {
            continue;  // Skip entries with missing fields
        }
        
        // Get the field to search in
        const FieldBase* field = entry.fields[fieldIndex];
        // Flag to track if this entry matches
        bool match = false;
        
        // Handle single and multi fields differently
        if (field->gettype() == FieldT::single) {
            // Handle different data types
            switch (fieldFormats[fieldIndex].type) {
                case DataT::S: {
                    // Cast to single string field
                    auto f = static_cast<const FieldSingle<std::string>*>(field);
                    // Check if the value is found in the field data
                    if (f->getdata().find(value) != std::string::npos) {
                        match = true;
                    }
                    break;
                }
                case DataT::I: {
                    // Cast to single integer field
                    auto f = static_cast<const FieldSingle<int>*>(field);
                    // Convert integer to string and check for matches
                    if (std::to_string(f->getdata()).find(value) != std::string::npos) {
                        match = true;
                    }
                    break;
                }
                case DataT::D: {
                    // Cast to single double field
                    auto f = static_cast<const FieldSingle<double>*>(field);
                    // Convert double to string and check for matches
                    if (std::to_string(f->getdata()).find(value) != std::string::npos) {
                        match = true;
                    }
                    break;
                }
                case DataT::B: {
                    // Cast to single boolean field
                    auto f = static_cast<const FieldSingle<bool>*>(field);
                    // Convert boolean to "true"/"false" and check for matches
                    std::string boolStr = f->getdata() ? "true" : "false";
                    if (boolStr.find(value) != std::string::npos) {
                        match = true;
                    }
                    break;
                }
            }
        } else { // MULTI
            // Handle different data types for multi fields
            switch (fieldFormats[fieldIndex].type) {
                case DataT::S: {
                    // Cast to multi string field
                    auto f = static_cast<const FieldMulti<std::string>*>(field);
                    // Check each string value for matches
                    for (int i = 0; i < f->getsize(); ++i) {
                        if (f->getdata(i).find(value) != std::string::npos) {
                            match = true;
                            break;
                        }
                    }
                    break;
                }
                case DataT::I: {
                    // Cast to multi integer field
                    auto f = static_cast<const FieldMulti<int>*>(field);
                    // Check each integer value (converted to string) for matches
                    for (int i = 0; i < f->getsize(); ++i) {
                        if (std::to_string(f->getdata(i)).find(value) != std::string::npos) {
                            match = true;
                            break;
                        }
                    }
                    break;
                }
                case DataT::D: {
                    // Cast to multi double field
                    auto f = static_cast<const FieldMulti<double>*>(field);
                    // Check each double value (converted to string) for matches
                    for (int i = 0; i < f->getsize(); ++i) {
                        if (std::to_string(f->getdata(i)).find(value) != std::string::npos) {
                            match = true;
                            break;
                        }
                    }
                    break;
                }
                case DataT::B: {
                    // Cast to multi boolean field
                    auto f = static_cast<const FieldMulti<bool>*>(field);
                    // Check each boolean value (converted to "true"/"false") for matches
                    for (int i = 0; i < f->getsize(); ++i) {
                        std::string boolStr = f->getdata(i) ? "true" : "false";
                        if (boolStr.find(value) != std::string::npos) {
                            match = true;
                            break;
                        }
                    }
                    break;
                }
            }
        }
        
        // If this entry matches, output it
        if (match) {
            foundAny = true;
            outputFile << formatEntry(entry) << std::endl;
        }
    }
    
    // If no matches were found, output "Not found"
    if (!foundAny) {
        outputFile << "Not found" << std::endl;
    }
}

// Execute a sort command
void Catalog::executeSort(const std::string& fieldName) {
    // Find the index of the specified field
    int fieldIndex = findFieldIndex(fieldName);
    
    // If the field is not found, throw an exception
    if (fieldIndex == -1) {
        throw WrongCommandException();
    }
    
    // Create a copy of entries to sort
    std::vector<Entry> sortedEntries = entries;
    
    // Sort the entries based on the specified field
    std::sort(sortedEntries.begin(), sortedEntries.end(), 
              EntryComparator(fieldFormats[fieldIndex], fieldIndex));
    
    // Output the sorted entries
    for (const auto& entry : sortedEntries) {
        outputFile << formatEntry(entry) << std::endl;
    }
}

// Find the index of a field by name
int Catalog::findFieldIndex(const std::string& fieldName) {
    // Loop through all field formats
    for (size_t i = 0; i < fieldFormats.size(); ++i) {
        // If the field name matches, return the index
        if (fieldFormats[i].name == fieldName) {
            return i;
        }
    }
    // Field not found
    return -1;
}

// Comparator for sorting entries
bool Catalog::EntryComparator::operator()(const Entry& e1, const Entry& e2) const {
    // Skip comparison if either entry doesn't have the field
    if (fieldIndex >= static_cast<int>(e1.fields.size()) || 
        fieldIndex >= static_cast<int>(e2.fields.size())) {
        // Entries with missing fields come last
        return fieldIndex < static_cast<int>(e1.fields.size());
    }
    
    // Get the fields to compare
    const FieldBase* field1 = e1.fields[fieldIndex];
    const FieldBase* field2 = e2.fields[fieldIndex];
    
    // Handle single and multi fields differently
    if (format.sm == FieldT::single) {
        // Handle different data types
        switch (format.type) {
            case DataT::S: {
                // Cast to single string fields
                auto f1 = static_cast<const FieldSingle<std::string>*>(field1);
                auto f2 = static_cast<const FieldSingle<std::string>*>(field2);
                // Compare string values
                return f1->getdata() < f2->getdata();
            }
            case DataT::I: {
                // Cast to single integer fields
                auto f1 = static_cast<const FieldSingle<int>*>(field1);
                auto f2 = static_cast<const FieldSingle<int>*>(field2);
                // Compare integer values
                return f1->getdata() < f2->getdata();
            }
            case DataT::D: {
                // Cast to single double fields
                auto f1 = static_cast<const FieldSingle<double>*>(field1);
                auto f2 = static_cast<const FieldSingle<double>*>(field2);
                // Compare double values
                return f1->getdata() < f2->getdata();
            }
            case DataT::B: {
                // Cast to single boolean fields
                auto f1 = static_cast<const FieldSingle<bool>*>(field1);
                auto f2 = static_cast<const FieldSingle<bool>*>(field2);
                // Compare boolean values
                return f1->getdata() < f2->getdata();
            }
        }
    } else { // MULTI
        // Handle different data types for multi fields
        switch (format.type) {
            case DataT::S: {
                // Cast to multi string fields
                auto f1 = static_cast<const FieldMulti<std::string>*>(field1);
                auto f2 = static_cast<const FieldMulti<std::string>*>(field2);
                
                // Compare first elements if available
                if (f1->getsize() > 0 && f2->getsize() > 0) {
                    return f1->getdata(0) < f2->getdata(0);
                } else if (f1->getsize() == 0) {
                    return true; // Empty comes before non-empty
                } else {
                    return false;
                }
            }
            case DataT::I: {
                // Cast to multi integer fields
                auto f1 = static_cast<const FieldMulti<int>*>(field1);
                auto f2 = static_cast<const FieldMulti<int>*>(field2);
                
                // Compare first elements if available
                if (f1->getsize() > 0 && f2->getsize() > 0) {
                    return f1->getdata(0) < f2->getdata(0);
                } else if (f1->getsize() == 0) {
                    return true;
                } else {
                    return false;
                }
            }
            case DataT::D: {
                // Cast to multi double fields
                auto f1 = static_cast<const FieldMulti<double>*>(field1);
                auto f2 = static_cast<const FieldMulti<double>*>(field2);
                
                // Compare first elements if available
                if (f1->getsize() > 0 && f2->getsize() > 0) {
                    return f1->getdata(0) < f2->getdata(0);
                } else if (f1->getsize() == 0) {
                    return true;
                } else {
                    return false;
                }
            }
            case DataT::B: {
                // Cast to multi boolean fields
                auto f1 = static_cast<const FieldMulti<bool>*>(field1);
                auto f2 = static_cast<const FieldMulti<bool>*>(field2);
                
                // Compare first elements if available
                if (f1->getsize() > 0 && f2->getsize() > 0) {
                    return f1->getdata(0) < f2->getdata(0);
                } else if (f1->getsize() == 0) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    
    // Default case - should not reach here
    return false;
}