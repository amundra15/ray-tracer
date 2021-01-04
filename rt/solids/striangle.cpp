#include <rt/solids/striangle.h>
#include <rt/intersection.h>

namespace rt {

SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material)
{
    /* TODO */
}

SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, const Vector& n1, const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material)
{
    /* TODO */
}

Intersection SmoothTriangle::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ NOT_IMPLEMENTED;
}

}