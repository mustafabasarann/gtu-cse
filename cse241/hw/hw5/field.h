// Include guards to prevent multiple inclusions of this header file
#ifndef FIELD_H
#define FIELD_H

// Standard library includes for various functionality
#include <string>      // For string handling
#include <vector>      // For storing collections of data
#include <memory>      // For smart pointer functionality

// Enumeration for field types: single value or multiple values
enum class FieldT { single, multi };

// Enumeration for data types: string, int, double, bool
enum class DataT { S, I, D, B }; // S=string, I=integer, D=double, B=bool

// Field format structure to store metadata about a field
struct FieldFormat {
    std::string name;  // Name of the field
    DataT type;        // Data type of the field
    FieldT sm;         // Whether the field is single or multi-valued
};

// Base class for all field types
class FieldBase {
public:
    // Virtual destructor for proper cleanup in derived classes
    virtual ~FieldBase() = default;
    
    // Pure virtual function to get the type of field (single or multi)
    // Must be implemented by derived classes
    virtual FieldT gettype() const = 0;
};

// Template class for single-value fields
// Can store different data types (T) like string, int, double, bool
template<class T>
class FieldSingle : public FieldBase {
public:
    // Constructor that initializes the field with data
    FieldSingle(T data) : data(data) {}
    
    // Getter method to access the field data
    T getdata() const { return data; }
    
    // Implementation of the gettype method from the base class
    // Returns that this is a single-value field
    FieldT gettype() const override { 
        return FieldT::single; 
    }
    
private:
    // The actual data stored in the field
    T data;
};

// Template class for multi-value fields
// Can store collections of different data types (T)
template<class T>
class FieldMulti : public FieldBase {
public:
    // Constructor that initializes the field with a vector of data
    FieldMulti(std::vector<T> data) : data(data) {}
    
    // Getter method to access a specific element in the data vector
    T getdata(int index) const { 
        return data[index]; 
    }
    
    // Getter method to get the number of elements in the data vector
    int getsize() const { 
        return data.size(); 
    }
    
    // Implementation of the gettype method from the base class
    // Returns that this is a multi-value field
    FieldT gettype() const override { 
        return FieldT::multi; 
    }
    
private:
    // The vector of data stored in the field
    std::vector<T> data;
};

// End of include guard
#endif // FIELD_H