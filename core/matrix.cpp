#include <core/matrix.h>
#include <core/assert.h>

#include <core/vector.h>
#include <core/point.h>

namespace rt {

Matrix::Matrix(const Float4& r0, const Float4& r1, const Float4& r2, const Float4& r3) {
    this->r0 = r0;
    this->r1 = r1;
    this->r2 = r2;
    this->r3 = r3;
}

Float4& Matrix::operator[](int idx) {
    if(idx==0)
        return r0;
    if(idx==1)
        return r1;
    if(idx==2)
        return r2;
    if(idx==3)
        return r3;
}

Float4 Matrix::operator[](int idx) const {
    if(idx==0)
        return r0;
    if(idx==1)
        return r1;
    if(idx==2)
        return r2;
    if(idx==3)
        return r3;
}

Matrix Matrix::operator+(const Matrix& b) const {
    return Matrix(r0+b[0],r1+b[1],r2+b[2],r3+b[3]);
}

Matrix Matrix::operator-(const Matrix& b) const {
    return Matrix(r0-b[0],r1-b[1],r2-b[2],r3-b[3]);
}

Matrix Matrix::transpose() const {
    Matrix result;

    result[0][0] = r0[0];
    result[0][1] = r1[0];
    result[0][2] = r2[0];
    result[0][3] = r3[0];
    result[1][0] = r0[1];
    result[1][1] = r1[1];
    result[1][2] = r2[1];
    result[1][3] = r3[1];
    result[2][0] = r0[2];
    result[2][1] = r1[2];
    result[2][2] = r2[2];
    result[2][3] = r3[2];
    result[3][0] = r0[3];
    result[3][1] = r1[3];
    result[3][2] = r2[3];
    result[3][3] = r3[3];

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
    return r0==b[0] && r1==b[1] && r2==b[2] && r3==b[3];
}

bool Matrix::operator!=(const Matrix& b) const {
    return !(r0==b[0] && r1==b[1] && r2==b[2] && r3==b[3]);
}

Matrix product(const Matrix& a, const Matrix& b) {
    Matrix b_ = b.transpose();

    Float4 row0 = Float4(dot(a[0],b[0]), dot(a[0],b[1]), dot(a[0],b[2]), dot(a[0],b[3]));
    Float4 row1 = Float4(dot(a[1],b[0]), dot(a[1],b[1]), dot(a[1],b[2]), dot(a[1],b[3]));
    Float4 row2 = Float4(dot(a[2],b[0]), dot(a[2],b[1]), dot(a[2],b[2]), dot(a[2],b[3]));
    Float4 row3 = Float4(dot(a[3],b[0]), dot(a[3],b[1]), dot(a[3],b[2]), dot(a[3],b[3]));

    return Matrix(row0, row1, row2, row3);
}

Matrix operator*(const Matrix& a, float scalar) {
    return Matrix(scalar*a[0], scalar*a[1], scalar*a[2], scalar*a[3]);
}

Matrix operator*(float scalar, const Matrix& a) {
    return Matrix(scalar*a[0], scalar*a[1], scalar*a[2], scalar*a[3]);
}

Float4 Matrix::operator*(const Float4& b) const {
    return Float4(dot(r0,b),dot(r1,b),dot(r2,b),dot(r3,b));
}

Vector Matrix::operator*(const Vector& b) const {
    Float4 b_ = Float4(b);
    return Vector(dot(r0,b_),dot(r1,b_),dot(r2,b_));
}

Point Matrix::operator*(const Point& b) const {
    Float4 b_ = Float4(b);
    float w = dot(r3,b_);
    return Point(dot(r0,b_)/w,dot(r1,b_)/w,dot(r2,b_)/w);
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
    Float4 row0 = Float4::rep(0.0f);
    Float4 row1 = Float4::rep(0.0f);
    Float4 row2 = Float4::rep(0.0f);
    Float4 row3 = Float4::rep(0.0f);
    return Matrix(row0, row1, row2, row3);
}

Matrix Matrix::identity() {
    Float4 row0 = Float4(1.0f,0.0f,0.0f,0.0f);
    Float4 row1 = Float4(0.0f,1.0f,0.0f,0.0f);
    Float4 row2 = Float4(0.0f,0.0f,1.0f,0.0f);
    Float4 row3 = Float4(0.0f,0.0f,0.0f,1.0f);
    return Matrix(row0, row1, row2, row3);
}

Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
    /* TODO */ NOT_IMPLEMENTED;
}

}