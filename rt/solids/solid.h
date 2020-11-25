#ifndef CG1RAYTRACER_SOLIDS_SOLID_HEADER
#define CG1RAYTRACER_SOLIDS_SOLID_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/primitive.h>

namespace rt {

class Material;
class CoordMapper;

/*
A solid is a physical primitive that has material and can be textured
*/
class Solid : public Primitive {
public:
    struct Sample {
        Point point;
        Vector normal;
    };

    Material* material;
    CoordMapper* texMapper;
    float a,b,c,d,e,f,g,h,i,j;
    explicit Solid(CoordMapper* texMapper = nullptr, Material* material = nullptr);
    Solid(const float& a, const float& b, const float& c, const float& d, const float& e, const float& f, const float& g, const float& h, const float& i, const float& j, CoordMapper* texMapper, Material* material);
    
    virtual BBox getBounds() const;
    virtual Sample sample() const;
    virtual float getArea() const;
    virtual void setMaterial(Material* m) { material = m; }
    virtual void setCoordMapper(CoordMapper* cm) { texMapper = cm; }

    virtual Intersection intersect(const Ray& ray, float previousBestDistance) const;
};

}


#endif