#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

// function declarations
double dotProduct(const std::vector<double>& v1, const std::vector<double>& v2);
std::vector<double> crossProduct(const std::vector<double>& v1, const std::vector<double>& v2);
double normL1(const std::vector<double>& v);
double normL2(const std::vector<double>& v);
double normInfinity(const std::vector<double>& v);
double normP(const std::vector<double>& v, int p);
std::vector<double> vectorAddition(const std::vector<double>& v1, const std::vector<double>& v2);
std::vector<double> vectorMultiply(const std::vector<double>& v1, const std::vector<double>& v2);
bool isLinearlyIndependent(const std::vector<std::vector<double>>& vectors);
std::vector<double> vectorSubtraction(const std::vector<double>& v1, const std::vector<double>& v2);
std::vector<double> scalarMultiply(const std::vector<double>& v, double scalar);
double angleBetweenVectors(const std::vector<double>& v1, const std::vector<double>& v2);
std::vector<double> normalize(const std::vector<double>& v);
void drawVector(const std::vector<double>& v);

#endif // VECTOR_H

