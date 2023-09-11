#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

// Function Declarations
double dotProduct(const vector<double>& v1, const vector<double>& v2);
vector<double> crossProduct(const vector<double>& v1, const vector<double>& v2);
double normL1(const vector<double>& v);
double normL2(const vector<double>& v);
double normInfinity(const vector<double>& v);
double normP(const vector<double>& v, int p);
vector<double> vectorAddition(const vector<double>& v1, const vector<double>& v2);
vector<double> vectorMultiply(const vector<double>& v1, const vector<double>& v2);
bool isLinearlyIndependent(const vector<vector<double>>& vectors);
vector<double> vectorSubtraction(const vector<double>& v1, const vector<double>& v2);
vector<double> scalarMultiply(const vector<double>& v, double scalar);
double angleBetweenVectors(const vector<double>& v1, const vector<double>& v2);
void drawVector(const vector<double>& v);

double dotProduct(const vector<double>& v1, const vector<double>& v2) {
    if (v1.size() != v2.size()) {
        throw invalid_argument("Vectors must be the same size for dot product.");
    }

    double result = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

// Cross Product
vector<double> crossProduct(const vector<double>& v1, const vector<double>& v2) {
    if (v1.size() != 3 || v2.size() != 3) {
        throw invalid_argument("Vectors must be 3D for cross product.");
    }

    vector<double> result(3);
    result[0] = v1[1] * v2[2] - v2[1] * v1[2];
    result[1] = v2[0] * v1[2] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v2[0] * v1[1];

    return result;
}

// L1 Norm (Manhattan Norm)
double normL1(const vector<double>& v) {
    double result = 0.0;
    for (size_t i = 0; i < v.size(); ++i) {
        result += abs(v[i]);
    }
    return result;
}

// L2 Norm (Euclidean Norm)
double normL2(const vector<double>& v) {
    double result = 0.0;
    for (size_t i = 0; i < v.size(); ++i) {
        result += pow(v[i], 2);
    }
    return sqrt(result);
}

// Infinity Norm
double normInfinity(const vector<double>& v) {
    double maxElement = abs(v[0]);
    for (size_t i = 1; i < v.size(); ++i) {
        maxElement = max(maxElement, abs(v[i]));
    }
    return maxElement;
}

// P Norm
double normP(const vector<double>& v, int p) {
    double result = 0.0;
    for (size_t i = 0; i < v.size(); ++i) {
        double abs_val = abs(v[i]);
        result += pow(abs_val, p);
    }
    return pow(result, 1.0 / p);
}


// Vector Addition
vector<double> vectorAddition(const vector<double>& v1, const vector<double>& v2) {
    if (v1.size() != v2.size()) {
        throw invalid_argument("Vectors must be the same size for vector addition.");
    }

    vector<double> result(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

// Vector Multiplication
vector<double> vectorMultiply(const vector<double>& v1, const vector<double>& v2) {
    if (v1.size() != v2.size()) {
        throw invalid_argument("Vectors must be the same size for vector multiplication.");
    }

    vector<double> result(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] * v2[i];
    }
    return result;
}

bool isLinearlyIndependent(const vector<vector<double>>& vectors) {
    if (vectors.size() == 3 && vectors[0].size() == 3) {
        double det = vectors[0][0] * (vectors[1][1] * vectors[2][2] - vectors[2][1] * vectors[1][2]) -
                     vectors[0][1] * (vectors[1][0] * vectors[2][2] - vectors[2][0] * vectors[1][2]) +
                     vectors[0][2] * (vectors[1][0] * vectors[2][1] - vectors[2][0] * vectors[1][1]);

        return (det != 0);
    } else {
        throw invalid_argument("This check for linear independence only works for 3 sets of 3D vectors.");
    }
}

vector<double> vectorSubtraction(const vector<double>& v1, const vector<double>& v2) {
    if (v1.size() != v2.size()) {
        throw invalid_argument("Vectors must be the same size for vector subtraction.");
    }

    vector<double> result(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

vector<double> scalarMultiply(const vector<double>& v, double scalar) {
    vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] * scalar;
    }
    return result;
}

double angleBetweenVectors(const vector<double>& v1, const vector<double>& v2) {
    if (v1.size() != v2.size()) {
        throw invalid_argument("Vectors must be the same size for angle calculation.");
    }

    double product = dotProduct(v1, v2);
    double norms = normL2(v1) * normL2(v2);

    if (norms == 0) {
        throw invalid_argument("One of vectors is a zero vector. Cannot calculate angle.");
    }

    return acos(product / norms);
}

vector<double> normalize(const vector<double>& v) {
    double magnitude = normL2(v);
    if (magnitude == 0) {
        throw invalid_argument("Cannot normalize a zero vector.");
    }

    vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] / magnitude;
    }
    return result;
}

void drawVector(const vector<double>& v) {
    if (v.size() != 2) throw invalid_argument("drawVector can only draw 2D vectors");

    int x = round(v[0]);
    int y = round(v[1]);
    int width = max(20, 2 + max(x, y));  // minimum width is 20

    for (int i = width; i >= 0; --i) {
        for (int j = 0; j <= width; ++j) {
            if (j == 0 && i == 0) {
                cout << "+";  // origin
            } else if (j == 0) {
                cout << "|";  // y-axis
            } else if (i == 0) {
                cout << "-";  // x-axis
            } else if (j == x && i == y) {
                cout << "*";  // vector end point
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

// Dot, Cross Product function and linear independence check are omitted in the main function because they are applicable only on 3D

int main() {
    vector<double> sv1 = {3, 2, 5};
    vector<double> sv2 = {4, 5, 6};
    vector<double> v2D = {4, 5};

    cout << "sv1: ";
    for (auto i : sv1)
        cout << i << " ";
    cout << "\n";
    
    cout << "sv2: ";
    for (auto i : sv2)
        cout << i << " ";
    cout << "\n";

    cout << "Dot Product of sv1 and sv2: " << dotProduct(sv1, sv2) << "\n";

    cout << "L1 Norm of sv1: " << normL1(sv1) << "\n";

    cout << "L2 Norm of sv1: " << normL2(sv1) << "\n";

    cout << "Infinity Norm of sv1: " << normInfinity(sv1) << "\n";

    cout << "P Norm of sv1 with p=3: " << normP(sv1, 3) << "\n";

    cout << "Vector Addition of sv1 and sv2: ";
    vector<double> sum = vectorAddition(sv1, sv2);
    for (double val : sum)
        cout << val << " ";
    cout << "\n";

    cout << "Vector Multiplication sv1 and sv2: ";
    vector<double> product = vectorMultiply(sv1, sv2);
    for (double val : product)
        cout << val << " ";
    cout << "\n";

    cout << "Vector Subtraction sv1 - sv2: ";
    vector<double> subtract = vectorSubtraction(sv1, sv2);
    for (double val : subtract) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Scalar Multiplication of sv1 with scalar 3: ";
    vector<double> multiplied = scalarMultiply(sv1, 3);
    for (double val : multiplied) {
        cout << val << " ";
    }
    cout << endl;

    cout << "The angle between vectors sv1 and sv2 in radians: " << angleBetweenVectors(sv1, sv2) << endl;

    cout << "\n2D vector v2D: " << std::endl; 
    drawVector(v2D);

    return 0;
}


