#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>
#include <core/assert.h>
#include <algorithm>
#include <cmath>

namespace rt {

Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(const Float4& f4)
{
    assert(f4.w==0); 
    this->x = f4.x;
    this->y = f4.y;
    this->z = f4.z;
}

Vector Vector::operator + (const Vector& b) const {
    return Vector(this->x + b.x, this->y + b.y, this->z + b.z);
}

Vector Vector::operator - (const Vector& b) const {
    return Vector(this->x - b.x, this->y - b.y, this->z - b.z);
}

Vector Vector::operator - () const {
    return Vector(-1*this->x, -1*this->y, -1*this->z);
}

Vector Vector::normalize() const {
    float l = this->length();
	return Vector(this->x / l, this->y / l, this->z / l);
}

Vector operator * (float scalar, const Vector& b) {
    return Vector(scalar*b.x, scalar*b.y, scalar*b.z);
}

Vector operator * (const Vector& a, float scalar) {
    return Vector(scalar*a.x, scalar*a.y, scalar*a.z);
}

Vector operator / (const Vector& a, float scalar) {
    return Vector(a.x/scalar, a.y/scalar, a.z/scalar);
}

Vector cross(const Vector& a, const Vector& b) {
    return Vector(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}

float dot(const Vector& a, const Vector& b) {
    return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
}

float Vector::lensqr() const {
    return x*x + y*y + z*z;
}

float Vector::length() const {
    return std::sqrt(lensqr());
}


bool Vector::operator == (const Vector& b) const {
    //TODO_a: should we implement the epsilon thing here? Note: epsilon is given in scalar.h
    //random: turns out you shouldn't get the absolute value of a float with abs() but rather with fabs()
    return (this->x == b.x) && (this->y == b.y) && (this->z == b.z);
}

bool Vector::operator != (const Vector& b) const {
    return !((this->x == b.x) && (this->y == b.y) && (this->z == b.z));
}

Vector min(const Vector& a, const Vector& b) {
    return Vector(std::min(a.x,b.x),std::min(a.y,b.y),std::min(a.z,b.z));
}

Vector max(const Vector& a, const Vector& b) {
    return Vector(std::max(a.x,b.x),std::max(a.y,b.y),std::max(a.z,b.z));
}

Vector operator / (const Vector& a, const Vector& b) {
    return Vector(a.x/b.x, a.y/b.y, a.z/b.z);
}

Point operator + (const Point& a, const Vector& b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator + (const Vector& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator - (const Point& a, const Vector& b) {
    return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point operator * (const Float4& scale, const Point& p) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
