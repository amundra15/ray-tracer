#include <core/matrix.h>
#include <core/assert.h>

#include <core/vector.h>
#include <core/point.h>

namespace rt {

Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4) {
    mat[0][0] = r1[0];
    mat[0][1] = r1[1];
    mat[0][2] = r1[2];
    mat[0][3] = r1[3];  
    mat[1][0] = r2[0];
    mat[1][1] = r2[1];
    mat[1][2] = r2[2];
    mat[1][3] = r2[3];      
    mat[2][0] = r3[0];
    mat[2][1] = r3[1];
    mat[2][2] = r3[2];
    mat[2][3] = r3[3]; 
    mat[3][0] = r4[0];
    mat[3][1] = r4[1];
    mat[3][2] = r4[2];
    mat[3][3] = r4[3];
}

Float4& Matrix::operator[](int idx) {
    Float4 *result = new Float4(mat[idx][0],mat[idx][1],mat[idx][2],mat[idx][3]);
    return *result;
    // /* TODO */ NOT_IMPLEMENTED;
}

Float4 Matrix::operator[](int idx) const {
    return Float4(mat[idx][0],mat[idx][1],mat[idx][2],mat[idx][3]);
}

Matrix Matrix::operator+(const Matrix& b) const {
    Matrix result;

    result[0][0] = mat[0][0] + b[0][0];
    result[0][1] = mat[0][1] + b[0][1];
    result[0][2] = mat[0][2] + b[0][2];
    result[0][3] = mat[0][3] + b[0][3];
    result[1][0] = mat[1][0] + b[1][0];
    result[1][1] = mat[1][1] + b[1][1];
    result[1][2] = mat[1][2] + b[1][2];
    result[1][3] = mat[1][3] + b[1][3];
    result[2][0] = mat[2][0] + b[2][0];
    result[2][1] = mat[2][1] + b[2][1];
    result[2][2] = mat[2][2] + b[2][2];
    result[2][3] = mat[2][3] + b[2][3];
    result[3][0] = mat[3][0] + b[3][0];
    result[3][1] = mat[3][1] + b[3][1];
    result[3][2] = mat[3][2] + b[3][2];
    result[3][3] = mat[3][3] + b[3][3];

    return result;
}

Matrix Matrix::operator-(const Matrix& b) const {
    Matrix result;

    result[0][0] = -mat[0][0];
    result[0][1] = -mat[0][1];
    result[0][2] = -mat[0][2];
    result[0][3] = -mat[0][3];
    result[1][0] = -mat[1][0];
    result[1][1] = -mat[1][1];
    result[1][2] = -mat[1][2];
    result[1][3] = -mat[1][3];
    result[2][0] = -mat[2][0];
    result[2][1] = -mat[2][1];
    result[2][2] = -mat[2][2];
    result[2][3] = -mat[2][3];
    result[3][0] = -mat[3][0];
    result[3][1] = -mat[3][1];
    result[3][2] = -mat[3][2];
    result[3][3] = -mat[3][3];

    return result;
}

Matrix Matrix::transpose() const {
    Matrix result;

    result[0][0] = mat[0][0];
    result[0][1] = mat[1][0];
    result[0][2] = mat[2][0];
    result[0][3] = mat[3][0];
    result[1][0] = mat[0][1];
    result[1][1] = mat[1][1];
    result[1][2] = mat[2][1];
    result[1][3] = mat[3][1];
    result[2][0] = mat[0][2];
    result[2][1] = mat[1][2];
    result[2][2] = mat[2][2];
    result[2][3] = mat[3][2];
    result[3][0] = mat[0][3];
    result[3][1] = mat[1][3];
    result[3][2] = mat[2][3];
    result[3][3] = mat[3][3];

    return result;
}

Matrix Matrix::invert() const {
    Matrix result;
    const Matrix& m = *this;

    // Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    if (det == 0)
        return Matrix::zero();

    result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
    result[1][1] =  m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
    result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
    result[3][1] =  m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
    result[0][2] =  m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
    result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
    result[2][2] =  m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
    result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
    result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
    result[1][3] =  m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
    result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
    result[3][3] =  m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

    result = result*(1.0f/det);
    return result;
}

bool Matrix::operator==(const Matrix& b) const {
    bool result;

    result =     
    mat[0][0] == b[0][0] &&
    mat[0][1] == b[0][1] &&
    mat[0][2] == b[0][2] &&
    mat[0][3] == b[0][3] &&
    mat[1][0] == b[1][0] &&
    mat[1][1] == b[1][1] &&
    mat[1][2] == b[1][2] &&
    mat[1][3] == b[1][3] &&
    mat[2][0] == b[2][0] &&
    mat[2][1] == b[2][1] &&
    mat[2][2] == b[2][2] &&
    mat[2][3] == b[2][3] &&
    mat[3][0] == b[3][0] &&
    mat[3][1] == b[3][1] &&
    mat[3][2] == b[3][2] &&
    mat[3][3] == b[3][3];

    return result;
}

bool Matrix::operator!=(const Matrix& b) const {
    bool result;

    result =     
    mat[0][0] == b[0][0] &&
    mat[0][1] == b[0][1] &&
    mat[0][2] == b[0][2] &&
    mat[0][3] == b[0][3] &&
    mat[1][0] == b[1][0] &&
    mat[1][1] == b[1][1] &&
    mat[1][2] == b[1][2] &&
    mat[1][3] == b[1][3] &&
    mat[2][0] == b[2][0] &&
    mat[2][1] == b[2][1] &&
    mat[2][2] == b[2][2] &&
    mat[2][3] == b[2][3] &&
    mat[3][0] == b[3][0] &&
    mat[3][1] == b[3][1] &&
    mat[3][2] == b[3][2] &&
    mat[3][3] == b[3][3];

    return !result;
}

Matrix product(const Matrix& a, const Matrix& b) {
    //not sure if this is correct
    Matrix result;

    result[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0] + a[0][3]*b[3][0];
    result[0][1] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0] + a[0][3]*b[3][0];
    result[0][2] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0] + a[0][3]*b[3][0];
    result[0][3] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0] + a[0][3]*b[3][0];
    result[1][0] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1] + a[1][3]*b[3][1];
    result[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1] + a[1][3]*b[3][1];
    result[1][2] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1] + a[1][3]*b[3][1];
    result[1][3] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1] + a[1][3]*b[3][1];
    result[2][0] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2] + a[2][3]*b[3][2];
    result[2][1] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2] + a[2][3]*b[3][2];
    result[2][2] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2] + a[2][3]*b[3][2];
    result[2][3] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2] + a[2][3]*b[3][2];
    result[3][0] = a[3][0]*b[0][3] + a[3][1]*b[1][3] + a[3][2]*b[2][3] + a[3][3]*b[3][3];
    result[3][1] = a[3][0]*b[0][3] + a[3][1]*b[1][3] + a[3][2]*b[2][3] + a[3][3]*b[3][3];
    result[3][2] = a[3][0]*b[0][3] + a[3][1]*b[1][3] + a[3][2]*b[2][3] + a[3][3]*b[3][3];
    result[3][3] = a[3][0]*b[0][3] + a[3][1]*b[1][3] + a[3][2]*b[2][3] + a[3][3]*b[3][3];

    return result;
}

Matrix operator*(const Matrix& a, float scalar) {
    Matrix result;

    result[0][0] = a[0][0] * scalar;
    result[0][1] = a[0][1] * scalar;
    result[0][2] = a[0][2] * scalar;
    result[0][3] = a[0][3] * scalar;
    result[1][0] = a[1][0] * scalar;
    result[1][1] = a[1][1] * scalar;
    result[1][2] = a[1][2] * scalar;
    result[1][3] = a[1][3] * scalar;
    result[2][0] = a[2][0] * scalar;
    result[2][1] = a[2][1] * scalar;
    result[2][2] = a[2][2] * scalar;
    result[2][3] = a[2][3] * scalar;
    result[3][0] = a[3][0] * scalar;
    result[3][1] = a[3][1] * scalar;
    result[3][2] = a[3][2] * scalar;
    result[3][3] = a[3][3] * scalar;

    return result;
}

Matrix operator*(float scalar, const Matrix& a) {
    Matrix result;

    result[0][0] = a[0][0] * scalar;
    result[0][1] = a[0][1] * scalar;
    result[0][2] = a[0][2] * scalar;
    result[0][3] = a[0][3] * scalar;
    result[1][0] = a[1][0] * scalar;
    result[1][1] = a[1][1] * scalar;
    result[1][2] = a[1][2] * scalar;
    result[1][3] = a[1][3] * scalar;
    result[2][0] = a[2][0] * scalar;
    result[2][1] = a[2][1] * scalar;
    result[2][2] = a[2][2] * scalar;
    result[2][3] = a[2][3] * scalar;
    result[3][0] = a[3][0] * scalar;
    result[3][1] = a[3][1] * scalar;
    result[3][2] = a[3][2] * scalar;
    result[3][3] = a[3][3] * scalar;

    return result;
}

Float4 Matrix::operator*(const Float4& b) const {
    Float4 result;

    result[0] = mat[0][0]*b[0] + mat[0][1]*b[1] + mat[0][2]*b[2] + mat[0][3]*b[3];
    result[1] = mat[1][0]*b[0] + mat[1][1]*b[1] + mat[1][2]*b[2] + mat[1][3]*b[3];
    result[2] = mat[2][0]*b[0] + mat[2][1]*b[1] + mat[2][2]*b[2] + mat[2][3]*b[3];
    result[3] = mat[3][0]*b[0] + mat[3][1]*b[1] + mat[3][2]*b[2] + mat[3][3]*b[3];

    return result;
}

Vector Matrix::operator*(const Vector& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Point Matrix::operator*(const Point& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Matrix::det() const {
    //copied from inverse calculation
    Matrix result;
    const Matrix& m = *this;

    // Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    return det;
}

Matrix Matrix::zero() {
    Matrix result;

    result[0][0] = 0;
    result[0][1] = 0;
    result[0][2] = 0;
    result[0][3] = 0;
    result[1][0] = 0;
    result[1][1] = 0;
    result[1][2] = 0;
    result[1][3] = 0;
    result[2][0] = 0;
    result[2][1] = 0;
    result[2][2] = 0;
    result[2][3] = 0;
    result[3][0] = 0;
    result[3][1] = 0;
    result[3][2] = 0;
    result[3][3] = 0;

    return result;
}

Matrix Matrix::identity() {
    Matrix result;

    result[0][0] = 1;
    result[0][1] = 0;
    result[0][2] = 0;
    result[0][3] = 0;
    result[1][0] = 0;
    result[1][1] = 1;
    result[1][2] = 0;
    result[1][3] = 0;
    result[2][0] = 0;
    result[2][1] = 0;
    result[2][2] = 1;
    result[2][3] = 0;
    result[3][0] = 0;
    result[3][1] = 0;
    result[3][2] = 0;
    result[3][3] = 1;

    return result;
}

Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
    /* TODO */ NOT_IMPLEMENTED;
}

}