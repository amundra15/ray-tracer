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
    /* TODO */
}

Vector::Vector(const Float4& f4)
{
    /* TODO */
}

Vector Vector::operator + (const Vector& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector Vector::operator - (const Vector& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector Vector::operator - () const {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector Vector::normalize() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector operator * (float scalar, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector operator * (const Vector& a, float scalar) {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector operator / (const Vector& a, float scalar) {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector cross(const Vector& a, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

float dot(const Vector& a, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

float Vector::lensqr() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Vector::length() const {
    /* TODO */ NOT_IMPLEMENTED;
}


bool Vector::operator == (const Vector& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool Vector::operator != (const Vector& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector min(const Vector& a, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Vector max(const Vector& a, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Point operator + (const Point& a, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Point operator + (const Vector& a, const Point& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Point operator - (const Point& a, const Vector& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Point operator * (const Float4& scale, const Point& p) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
