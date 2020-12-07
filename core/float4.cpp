#include <core/float4.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/assert.h>
#include <core/scalar.h>

namespace rt {

Float4::Float4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Float4::Float4(const Point& p) {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
    this->w = 1.0f;    
}

Float4::Float4(const Vector& vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
    this->w = 0.0f;    
}

float& Float4::operator [] (int idx) {
    if (idx==0) return x;
    else if (idx==1) return y;
    else if (idx==2) return z;
    else if (idx==3) return w;
}

float Float4::operator [] (int idx) const {
    if (idx==0) return x;
    else if (idx==1) return y;
    else if (idx==2) return z;
    else if (idx==3) return w;
}

Float4 Float4::operator + (const Float4& b) const {
    return Float4(this->x + b.x, this->y + b.y, this->z + b.z, this->w + b.w);
}

Float4 Float4::operator - (const Float4& b) const {
    return Float4(this->x - b.x, this->y - b.y, this->z - b.z, this->w - b.w);
}

Float4 Float4::operator * (const Float4& b) const {
    return Float4(this->x*b.x, this->y*b.y, this->z*b.z, this->w*b.w);
}

Float4 Float4::operator / (const Float4& b) const {
    return Float4(this->x/b.x, this->y/b.y, this->z/b.z, this->w/b.w);
}

Float4 operator * (float scalar, const Float4& b) {
    return Float4(scalar*b.x, scalar*b.y, scalar*b.z,scalar*b.w);
}

Float4 operator * (const Float4& a, float scalar) {
    return Float4(scalar*a.x, scalar*a.y, scalar*a.z,scalar*a.w);
}

Float4 operator / (const Float4& a, float scalar) {
    return Float4(a.x/scalar, a.y/scalar, a.z/scalar, a.w/scalar);
}

float dot(const Float4& a, const Float4& b) {
    return (a.x*b.x)+(a.y*b.y)+(a.z*b.z)+(a.w*b.w);
}

Float4 Float4::operator - () const {
    return Float4(-x,-y,-z,-w);
}

bool Float4::operator == (const Float4& b) const {
    return (this->x == b.x) && (this->y == b.y) && (this->z == b.z) && (this->w == b.w);
}

bool Float4::operator != (const Float4& b) const {
    return !((this->x == b.x) && (this->y == b.y) && (this->z == b.z) && (this->w == b.w));
}

Float4 min(const Float4& a, const Float4& b) {
    return Float4(std::min(a.x,b.x),std::min(a.y,b.y),std::min(a.z,b.z),std::min(a.w,b.w));
}

Float4 max(const Float4& a, const Float4& b) {
    return Float4(std::max(a.x,b.x),std::max(a.y,b.y),std::max(a.z,b.z),std::max(a.w,b.w));
}

}