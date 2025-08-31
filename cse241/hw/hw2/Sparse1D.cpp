#include "Sparse1D.h"
#include <fstream>
#include <sstream>

using namespace std;
Sparse1D::Sparse1D() {}

// constructor that reads data from a file to build the sparse vector
Sparse1D::Sparse1D(const string& filename) {
    ifstream infile(filename);
    string index_data;
    while (infile >> index_data) {
        size_t sep = index_data.find('|');
        int index = stoi(index_data.substr(0, sep));
        double value = stod(index_data.substr(sep + 1));
        indices.push_back(index);
        data.push_back(value);
    }
}

// adds two sparse vectors and returns a new Sparse1D object
Sparse1D Sparse1D::operator+(const Sparse1D& other) const {
    Sparse1D result;
    size_t i = 0, j = 0;
    while (i < indices.size() && j < other.indices.size()) {
        if (indices[i] == other.indices[j]) {
            result.indices.push_back(indices[i]);
            result.data.push_back(data[i] + other.data[j]);
            i++; j++;
        } else if (indices[i] < other.indices[j]) {
            result.indices.push_back(indices[i]);
            result.data.push_back(data[i]);
            i++;
        } else {
            result.indices.push_back(other.indices[j]);
            result.data.push_back(other.data[j]);
            j++;
        }
    }
    while (i < indices.size()) {
        result.indices.push_back(indices[i]);
        result.data.push_back(data[i]);
        i++;
    }
    while (j < other.indices.size()) {
        result.indices.push_back(other.indices[j]);
        result.data.push_back(other.data[j]);
        j++;
    }
    return result;
}

// dot product: multiplies corresponding elements and sums them
double Sparse1D::dot(const Sparse1D& other) const {
    double result = 0;
    size_t i = 0, j = 0;
    while (i < indices.size() && j < other.indices.size()) {
        if (indices[i] == other.indices[j]) {
            result += data[i] * other.data[j];
            i++; j++;
        } else if (indices[i] < other.indices[j]) {
            i++;
        } else {
            j++;
        }
    }
    return result;
}

// allows printing Sparse1D using cout or other ostream objects
ostream& operator<<(ostream& os, const Sparse1D& obj) {
    for (size_t i = 0; i < obj.indices.size(); ++i) {
        os << obj.indices[i] << "|" << obj.data[i];
        if (i != obj.indices.size() - 1) os << " ";
    }
    return os;
}
// subtracts one Sparse1D object from another
Sparse1D Sparse1D::operator-(const Sparse1D& other) const {
    Sparse1D result = *this;
    for (size_t i = 0; i < other.indices.size(); ++i) {
        int idx = other.indices[i];
        double val = -other.data[i];
        bool found = false;
        for (size_t j = 0; j < result.indices.size(); ++j) {
            if (result.indices[j] == idx) {
                result.data[j] += val;
                found = true;
                break;
            }
        }
        if (!found && val != 0.0) {
            result.indices.push_back(idx);
            result.data.push_back(val);
        }
    }
    return result;
}

// subtracts one Sparse1D object from another
Sparse1D Sparse1D::operator-() const {
    Sparse1D result = *this;
    for (double& val : result.data) {
        val = -val;
    }
    return result;
}
