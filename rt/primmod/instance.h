#ifndef CG1RAYTRACER_PRIMMOD_INSTANCE_HEADER
#define CG1RAYTRACER_PRIMMOD_INSTANCE_HEADER

#include <core/vector.h>
#include <core/matrix.h>
#include <rt/primitive.h>

namespace rt {

class Instance : public Primitive {
public:
    Primitive* primitive;
    Instance(Primitive* content);
    Primitive* content();

    Matrix T;       //will be used only for updating the normal after the intersection
    Matrix T_inv;   //to save computation, we will keep updating T_inv along with T
    
    void reset(); //reset transformation back to identity
    void translate(const Vector& t);
    void rotate(const Vector& axis, float angle);
    void scale(float scale);
    void scale(const Vector& scale);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
    virtual float getArea() const;
};

}

#endif