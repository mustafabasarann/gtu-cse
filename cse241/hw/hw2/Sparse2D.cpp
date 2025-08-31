#include "Sparse2D.h"
#include <fstream>
#include <sstream>

using namespace std;
Sparse2D::Sparse2D() {}

Sparse2D::Sparse2D(const string& filename) {
    ifstream infile(filename);
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int row_index;
        iss >> row_index;
        row_indices.push_back(row_index);

// this vector holds the indices of non-zero elements
        vector<int> indices;
// this vector holds the actual non-zero values of the sparse vector
        vector<double> data;

        string index_data;
        while (iss >> index_data) {
            size_t sep = index_data.find('|');
            int col_index = stoi(index_data.substr(0, sep));
            double value = stod(index_data.substr(sep + 1));
            indices.push_back(col_index);
            data.push_back(value);
        }

        Sparse1D row;
        row.indices = indices;
        row.data = data;
        rows.push_back(row);
    }
}

// allows printing Sparse1D using cout or other ostream objects
ostream& operator<<(ostream& os, const Sparse2D& mat) {
    for (size_t i = 0; i < mat.row_indices.size(); ++i) {
        os << mat.row_indices[i] << " " << mat.rows[i] << endl;
    }
    return os;
}

// returns the transposed version of Sparse2D
Sparse2D Sparse2D::transpose() const {
    vector<vector<pair<int, double>>> cols;
    for (size_t i = 0; i < row_indices.size(); ++i) {
        const Sparse1D& row = rows[i];
        for (size_t j = 0; j < row.indices.size(); ++j) {
            int col_index = row.indices[j];
            if (col_index >= (int)cols.size())
                cols.resize(col_index + 1);
            cols[col_index].emplace_back(row_indices[i], row.data[j]);
        }
    }
    Sparse2D result;
    for (size_t i = 0; i < cols.size(); ++i) {
        if (!cols[i].empty()) {
            result.row_indices.push_back(i);
            Sparse1D row;
            for (auto& p : cols[i]) {
                row.indices.push_back(p.first);
                row.data.push_back(p.second);
            }
            result.rows.push_back(row);
        }
    }
    return result;
}

Sparse1D Sparse2D::column(int col) const {
    Sparse1D result;
    for (size_t i = 0; i < rows.size(); ++i) {
        const Sparse1D& row = rows[i];
        for (size_t j = 0; j < row.indices.size(); ++j) {
            if (row.indices[j] == col) {
                result.indices.push_back(row_indices[i]);
                result.data.push_back(row.data[j]);
            }
        }
    }
    return result;
}

Sparse2D Sparse2D::operator*(const Sparse2D& other) const {
// returns the transposed version of Sparse2D
    Sparse2D otherT = other.transpose();
    Sparse2D result;
    for (size_t i = 0; i < row_indices.size(); ++i) {
        vector<double> newData;
        vector<int> newIndices;
        for (size_t j = 0; j < otherT.rows.size(); ++j) {
// dot product: multiplies corresponding elements and sums them
            double val = rows[i].dot(otherT.rows[j]);
            if (val != 0) {
                newIndices.push_back(otherT.row_indices[j]);
                newData.push_back(val);
            }
        }
        Sparse1D row;
        row.indices = newIndices;
        row.data = newData;
        result.row_indices.push_back(row_indices[i]);
        result.rows.push_back(row);
    }
    return result;
}
// adds two sparse vectors and returns a new Sparse1D object
Sparse2D Sparse2D::operator+(const Sparse2D& other) const {
    Sparse2D result = *this;
    for (size_t i = 0; i < other.row_indices.size(); ++i) {
        int idx = other.row_indices[i];
        bool found = false;
        for (size_t j = 0; j < result.row_indices.size(); ++j) {
            if (result.row_indices[j] == idx) {
                result.rows[j] = result.rows[j] + other.rows[i];
                found = true;
                break;
            }
        }
        if (!found) {
            result.row_indices.push_back(idx);
            result.rows.push_back(other.rows[i]);
        }
    }
    return result;
}

Sparse2D Sparse2D::operator-(const Sparse2D& other) const {
    Sparse2D negOther = other;
    for (auto& row : negOther.rows) {
        row = -row;
    }
    return (*this) + negOther;
}

// unary minus: negates all values in the sparse vector
Sparse2D Sparse2D::operator-() const {
    Sparse2D result = *this;
    for (auto& row : result.rows) {
        row = -row;
    }
    return result;
}

const Sparse1D& Sparse2D::row(int i) const {
    return rows.at(i);
}
