#ifndef CG1RAYTRACER_SOLIDS_DISC_HEADER
#define CG1RAYTRACER_SOLIDS_DISC_HEADER

#include <rt/solids/solid.h>

namespace rt {

class Disc : public Solid {
	Point c;
	Vector n;
	float r;
public:
    Disc() {}
    Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;
	// Vector polar2cartesian(float r, float theta) const;
};

}

#endif