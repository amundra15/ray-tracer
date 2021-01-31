
#include <rt/solids/striangle.h>
#include <rt/intersection.h>

#define LOG(x) std::cout<<x<<std::endl;


namespace rt {

SmoothTriangle::SmoothTriangle(Point vertices[3], Vector n[3], CoordMapper* texMapper, Material* material)
{
    this->n[0] = n[0];
    this->n[1] = n[1];
    this->n[2] = n[2];
    this-> v[0] = vertices[0];
    this-> v[1] = vertices[1];
    this-> v[2] = vertices[2];
    this->texMapper = texMapper;
    this->material = material;
}

SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, const Vector& n1, const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material)
{
    this->n[0] = n1;
    this->n[1] = n2;
    this->n[2] = n3;
    this-> v[0] = v1;
    this-> v[1] = v2;
    this-> v[2] = v3;
    this->texMapper = texMapper;
    this->material = material;
}

BBox SmoothTriangle::getBounds() const {
    return BBox(
        Point(
            std::min(std::min(v[0].x, v[1].x), v[2].x),
            std::min(std::min(v[0].y, v[1].y), v[2].y),
            std::min(std::min(v[0].z, v[1].z), v[2].z)
        ),
        Point(
            std::max(std::max(v[0].x, v[1].x), v[2].x),
            std::max(std::max(v[0].y, v[1].y), v[2].y),
            std::max(std::max(v[0].z, v[1].z), v[2].z)
        )
    );
}

Intersection SmoothTriangle::intersect(const Ray& ray, float previousBestDistance) const {

    Vector vec1 = this->v[1] - this->v[0];
    Vector vec2 = this->v[2] - this->v[0];
    Vector normal = cross(vec1, vec2).normalize();
    float rayNormal = dot(ray.d, normal);

    if(rayNormal == 0.0f){

        return Intersection::failure();
    }

    float t = dot(this->v[0] - ray.o, normal) / rayNormal;

    if(t > previousBestDistance ||  t < 0){
        return Intersection::failure();
    }

   Point intPoint = ray.getPoint(t);
    Vector vecP = intPoint - this->v[0];

    if(dot(cross(vec1,vecP),  cross(vec1,vec2)) < 0.0f){
        return Intersection::failure();
    }

    if(dot(cross(vec2,vecP),  cross(vec2,vec1)) < 0.0f){
        return Intersection::failure();
    }


    float denominator = cross(vec2,vec1).length();
    float c = cross(vec1,vecP).length()/denominator;
    float b = cross(vec2,vecP).length()/denominator;
    float a = 1-b-c;

    if(b+c >= 1.0f){
        return Intersection::failure();
    }

    Vector New_Normal = (this->n[0] * a + this->n[1] * b + this->n[3] * c).normalize();

    return Intersection(t, ray, this, New_Normal, Point(a, b, c));
    
}
}