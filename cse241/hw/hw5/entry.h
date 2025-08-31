// Include guards to prevent multiple inclusions of this header file
#ifndef ENTRY_H
#define ENTRY_H

// Standard library includes for various functionality
#include <vector>     // For storing collections of fields
#include <string>     // For string handling
#include <memory>     // For smart pointer functionality
#include "field.h"    // Include custom Field class definitions

// Entry class representing a catalog entry
class Entry {
public:
    // Vector to store pointers to fields
    // Each field represents a column in the catalog entry
    std::vector<FieldBase*> fields;
    
    // Destructor to clean up field pointers
    // Deletes all dynamically allocated field objects
    ~Entry() {
        // Loop through all fields and delete them
        for (auto field : fields) {
            delete field;
        }
    }
    
    // Copy constructor
    // Creates a deep copy of another Entry object
    Entry(const Entry& other) {
        // Deep copy fields from other entry
        for (const auto* field : other.fields) {
            // Fields will be properly copied based on their type
            if (field->gettype() == FieldT::single) {
                // Handle single-value fields based on their data type
                if (dynamic_cast<const FieldSingle<std::string>*>(field)) {
                    // Copy string field
                    auto f = static_cast<const FieldSingle<std::string>*>(field);
                    fields.push_back(new FieldSingle<std::string>(f->getdata()));
                } else if (dynamic_cast<const FieldSingle<int>*>(field)) {
                    // Copy integer field
                    auto f = static_cast<const FieldSingle<int>*>(field);
                    fields.push_back(new FieldSingle<int>(f->getdata()));
                } else if (dynamic_cast<const FieldSingle<double>*>(field)) {
                    // Copy double field
                    auto f = static_cast<const FieldSingle<double>*>(field);
                    fields.push_back(new FieldSingle<double>(f->getdata()));
                } else if (dynamic_cast<const FieldSingle<bool>*>(field)) {
                    // Copy boolean field
                    auto f = static_cast<const FieldSingle<bool>*>(field);
                    fields.push_back(new FieldSingle<bool>(f->getdata()));
                }
            } else { // Handle multi-value fields
                if (dynamic_cast<const FieldMulti<std::string>*>(field)) {
                    // Copy multi-string field
                    auto f = static_cast<const FieldMulti<std::string>*>(field);
                    std::vector<std::string> values;
                    // Copy all values in the multi-string field
                    for (int i = 0; i < f->getsize(); ++i) {
                        values.push_back(f->getdata(i));
                    }
                    fields.push_back(new FieldMulti<std::string>(values));
                } else if (dynamic_cast<const FieldMulti<int>*>(field)) {
                    // Copy multi-integer field
                    auto f = static_cast<const FieldMulti<int>*>(field);
                    std::vector<int> values;
                    // Copy all values in the multi-integer field
                    for (int i = 0; i < f->getsize(); ++i) {
                        values.push_back(f->getdata(i));
                    }
                    fields.push_back(new FieldMulti<int>(values));
                } else if (dynamic_cast<const FieldMulti<double>*>(field)) {
                    // Copy multi-double field
                    auto f = static_cast<const FieldMulti<double>*>(field);
                    std::vector<double> values;
                    // Copy all values in the multi-double field
                    for (int i = 0; i < f->getsize(); ++i) {
                        values.push_back(f->getdata(i));
                    }
                    fields.push_back(new FieldMulti<double>(values));
                } else if (dynamic_cast<const FieldMulti<bool>*>(field)) {
                    // Copy multi-boolean field
                    auto f = static_cast<const FieldMulti<bool>*>(field);
                    std::vector<bool> values;
                    // Copy all values in the multi-boolean field
                    for (int i = 0; i < f->getsize(); ++i) {
                        values.push_back(f->getdata(i));
                    }
                    fields.push_back(new FieldMulti<bool>(values));
                }
            }
        }
    }
    
    // Copy assignment operator
    // Assigns the content of another Entry object to this one
    Entry& operator=(const Entry& other) {
        // Check for self-assignment
        if (this != &other) {
            // Clean up existing fields
            for (auto field : fields) {
                delete field;
            }
            fields.clear();
            
            // Use copy constructor's logic to create a temporary copy
            Entry temp(other);
            // Swap the fields vector with the temporary copy
            fields.swap(temp.fields);
            // The temporary object will delete the old fields when it goes out of scope
        }
        return *this;
    }
    
    // Default constructor
    // Creates an empty entry with no fields
    Entry() = default;
    
    // Move constructor
    // Efficiently transfers ownership of resources from another Entry
    Entry(Entry&& other) noexcept : fields(std::move(other.fields)) {
        // Clear the source object's fields to prevent double deletion
        other.fields.clear();
    }
    
    // Move assignment operator
    // Efficiently assigns the content of another Entry by transferring ownership
    Entry& operator=(Entry&& other) noexcept {
        // Check for self-assignment
        if (this != &other) {
            // Clean up existing fields
            for (auto field : fields) {
                delete field;
            }
            
            // Move fields from the other entry
            fields = std::move(other.fields);
            // Clear the source object's fields to prevent double deletion
            other.fields.clear();
        }
        return *this;
    }
};

// End of include guard
#endif // ENTRY_H