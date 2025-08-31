#include <vector>
#include <string>
#include <iostream>

using namespace std;
// declaring the Sparse1D class 
class Sparse1D {
public:
// subtracts one Sparse1D object from another
    Sparse1D operator-(const Sparse1D& other) const;
// subtracts one Sparse1D object from another
    Sparse1D operator-() const;
private:
// this vector holds the indices of non-zero elements
    vector<int> indices;
// this vector holds the actual non-zero values of the sparse vector
    vector<double> data;

public:
// default constructor: creates an empty sparse vector
    Sparse1D();
// constructor that reads data from a file to build the sparse vector
    Sparse1D(const string& filename);
// dot product: multiplies corresponding elements and sums them
    double dot(const Sparse1D& other) const;
// adds two sparse vectors and returns a new Sparse1D object
    Sparse1D operator+(const Sparse1D& other) const;
// allows printing Sparse1D using cout or other ostream objects
    friend ostream& operator<<(ostream& os, const Sparse1D& obj);

    friend class Sparse2D;
};
