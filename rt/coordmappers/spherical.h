#ifndef CG1RAYTRACER_COORDMAPPERS_SPHERICAL_HEADER
#define CG1RAYTRACER_COORDMAPPERS_SPHERICAL_HEADER

#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <core/matrix.h>

namespace rt {

class Intersection;
class SphericalCoordMapper : public CoordMapper {
public:
    SphericalCoordMapper();
    SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef);
    virtual Point getCoords(const Intersection& hit) const;
private:
    Point origin;
    Vector zenith; //Y
    Vector azimuthRef; //X
    Vector thirdZ; //z
    float aScale, zScale;
    Matrix transformation;
};

}

#endif