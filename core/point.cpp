#include <core/point.h>
#include <core/float4.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

Point::Point(float x, float y, float z)
{
    /* TODO */
}

Point::Point(const Float4& f4)
{
    /* TODO */ NOT_IMPLEMENTED;
}

Vector Point::operator - (const Point& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool Point::operator == (const Point& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool Point::operator != (const Point& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

Point operator * (float scalar, const Point& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Point operator * (const Point& a, float scalar) {
    /* TODO */ NOT_IMPLEMENTED;
}

Point min(const Point& a, const Point& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

Point max(const Point& a, const Point& b) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
