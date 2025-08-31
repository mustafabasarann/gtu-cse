#include <vector>
#include <string>
#include "Sparse1D.h"

using namespace std;
// declaring the Sparse2D class 
class Sparse2D {
public:
// adds two sparse vectors and returns a new Sparse1D object
    Sparse2D operator+(const Sparse2D& other) const;
    Sparse2D operator-(const Sparse2D& other) const;
// unary minus: negates all values in the sparse vector
    Sparse2D operator-() const;
private:
    vector<int> row_indices;
    vector<Sparse1D> rows;

public:
    Sparse2D();
    Sparse2D(const string& filename);
        const Sparse1D& row(int i) const;
// returns the transposed version of Sparse2D
Sparse2D transpose() const;
    Sparse1D column(int col) const;
    Sparse2D operator*(const Sparse2D& other) const;
// allows printing Sparse1D using cout or other ostream objects
    friend ostream& operator<<(ostream& os, const Sparse2D& mat);
};

