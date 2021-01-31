#include <rt/solids/striangle.h>
#include <rt/intersection.h>
#include <rt/solids/infiniteplane.h>
#include <rt/solids/solid.h>
#include <core/interpolate.h>

namespace rt {

SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material)
{
    this->texMapper = texMapper;
    this->material = material;

    this->v1 = vertices[0];
    this->v2 = vertices[1];
    this->v3 = vertices[2];

    this->n1 = normals[0];
    this->n2 = normals[1];
    this->n3 = normals[2];
}

SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, const Vector& n1, const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material)
{
    this->texMapper = texMapper;
    this->material = material;
    
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    this->n1 = n1;
    this->n2 = n2;
    this->n3 = n3;
}

BBox SmoothTriangle::getBounds() const {
    return BBox(
        Point(
            std::min(std::min(v1.x, v2.x), v3.x),
            std::min(std::min(v1.y, v2.y), v3.y),
            std::min(std::min(v1.z, v2.z), v3.z)
        ),
        Point(
            std::max(std::max(v1.x, v2.x), v3.x),
            std::max(std::max(v1.y, v2.y), v3.y),
            std::max(std::max(v1.z, v2.z), v3.z)
        )
    );
}

Intersection SmoothTriangle::intersect(const Ray& ray, float previousBestDistance) const {
    Vector vec1 = (v2 - v1);
    Vector vec2 = (v3 - v1);
     Vector normal = cross(vec1, vec2).normalize();
    Vector s = ray.o - v1;
    float rayNormal = dot(ray.d, normal);

    if(rayNormal == 0.0f){
        return Intersection::failure();
    }

    float t = dot(v1 - ray.o, normal) / rayNormal;
    
    if(t > previousBestDistance ||  t < 0){
        return Intersection::failure();
    }
    Point intPoint = ray.getPoint(t);
    Vector P = intPoint - v1;
    
    if(dot(cross(vec1,P),cross(vec1,P)) < 0.0f){
        return Intersection::failure();
    }

    if(dot(cross(vec2,P),cross(vec2,vec1)) < 0.0f){
        return Intersection::failure();
    }

    float denom = cross(vec2,vec1).length();
    float c = cross(vec1,P).length()/denom;
    float b = cross(vec2,P).length()/denom;
    float a = 1-b-c;

    if(b+c >= 1.0f){
        return Intersection::failure();
    }

    Vector pNormal = (n1 * a + n2 * b + n3 * c).normalize();

    return Intersection(t, ray, this, pNormal, Point(a, b, c));
}

}