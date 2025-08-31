#include <iostream>
using namespace std;

class Polynomial {
public:
    Polynomial(); // Default constructor
    Polynomial(const Polynomial& other); // Copy constructor
    Polynomial(double coefficient[], int size); // Parameterized constructor
    ~Polynomial(); // Destructor

    double& operator[](int degree);
    const double& operator[](int degree) const;
    const Polynomial& operator=(const Polynomial& rhs);
    double eval(double arg) const;
    int mySize() const;

    friend double evaluate(const Polynomial& poly, double arg);
    friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
    friend Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs);
    friend Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs);

private:
    double* coeff;
    int size;
};

// Default constructor
Polynomial::Polynomial() {
    size = 1;
    coeff = new double[size];
    coeff[0] = 0;
}

// Copy constructor
Polynomial::Polynomial(const Polynomial& other) {
    size = other.size;
    coeff = new double[size];
    for (int i = 0; i < size; i++) {
        coeff[i] = other.coeff[i];
    }
}

// Parameterized constructor
Polynomial::Polynomial(double coefficient[], int size) {
    this->size = size;
    coeff = new double[size];
    for (int i = 0; i < size; i++) {
        coeff[i] = coefficient[i];
    }
}

// Destructor
Polynomial::~Polynomial() {
    delete[] coeff;
}

// [] operator (non-const version)
double& Polynomial::operator[](int degree) {
    return coeff[degree];
}

// [] operator (const version)
const double& Polynomial::operator[](int degree) const {
    return coeff[degree];
}

// = operator
const Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    if (this != &rhs) {
        delete[] coeff;
        size = rhs.size;
        coeff = new double[size];
        for (int i = 0; i < size; i++) {
            coeff[i] = rhs.coeff[i];
        }
    }
    return *this;
}

// Eval function
double Polynomial::eval(double arg) const {
    double result = 0;
    double xPower = 1;
    for (int i = 0; i < size; i++) {
        result += coeff[i] * xPower;
        xPower *= arg;
    }
    return result;
}

// Return size
int Polynomial::mySize() const {
    return size;
}

// Friend function to evaluate
double evaluate(const Polynomial& poly, double arg) {
    return poly.eval(arg);
}

// + operator
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    int maxSize = max(lhs.size, rhs.size);
    double* resultCoeff = new double[maxSize];

    for (int i = 0; i < maxSize; i++) {
        double left = (i < lhs.size) ? lhs.coeff[i] : 0;
        double right = (i < rhs.size) ? rhs.coeff[i] : 0;
        resultCoeff[i] = left + right;
    }

    Polynomial result(resultCoeff, maxSize);
    delete[] resultCoeff;
    return result;
}

// - operator
Polynomial operator-(const Polynomial& lhs, const Polynomial& rhs) {
    int maxSize = max(lhs.size, rhs.size);
    double* resultCoeff = new double[maxSize];

    for (int i = 0; i < maxSize; i++) {
        double left = (i < lhs.size) ? lhs.coeff[i] : 0;
        double right = (i < rhs.size) ? rhs.coeff[i] : 0;
        resultCoeff[i] = left - right;
    }

    Polynomial result(resultCoeff, maxSize);
    delete[] resultCoeff;
    return result;
}

// * operator
Polynomial operator*(const Polynomial& lhs, const Polynomial& rhs) {
    int resultSize = lhs.size + rhs.size - 1;
    double* resultCoeff = new double[resultSize];
    
    for (int i = 0; i < resultSize; i++) {
        resultCoeff[i] = 0;
    }

    for (int i = 0; i < lhs.size; i++) {
        for (int j = 0; j < rhs.size; j++) {
            resultCoeff[i + j] += lhs.coeff[i] * rhs.coeff[j];
        }
    }

    Polynomial result(resultCoeff, resultSize);
    delete[] resultCoeff;
    return result;
}

int main() {
    // Define coefficients for two polynomials
Polynomial empty;
double one[] = { 1 };
Polynomial One(one, 1);
double quad[] = {3, 2, 1 };
double cubic[] = {1, 2 ,0, 3};
Polynomial q(quad, 3);
Polynomial c(cubic, 4);
Polynomial p = q;
Polynomial r;
r=q;
r=c;
 
cout << "Polynomial q" << endl;
for(int i=0;i<3;i++)
    cout << "term with degree " << i<< "has coefficient "<<q[i] << endl;
 
cout << "Polynomial c" << endl;
for(int i=0;i<4;i++)
    cout << "term with degree " << i<< "has coefficient "<<c[i] << endl;
 
cout << "value of q(2) is "<<evaluate(q,2)<<endl;
cout << "value of c(2) is "<<evaluate(c,2)<<endl;   
cout << "value of p(2) is "<<evaluate(p,2)<<endl;   
cout << "value of r(2) is "<<evaluate(r,2)<<endl;
 
r=q+c;
cout << "value of (q+c)(2) is "<<evaluate(r,2)<<endl;
 
r=q-c;
cout << "value of (q-c)(2) is "<<evaluate(r,2)<<endl;
 
r=q*c;
cout << "size of (q*c)(2) is "<<r.mySize()<<endl;
cout << "Polynomial r (=q*c) "<<endl;
 
for(int i=0;i<r.mySize();i++)
    cout << "term with degree " << i << " has coefficient "<<r[i] << endl;
cout << "value of (q*c)(2) is "<<evaluate(r,2)<<endl;
 
return 0;
}
