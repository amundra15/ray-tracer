#ifndef CG1RAYTRACER_COORDMAPPERS_SPHERICAL_HEADER
#define CG1RAYTRACER_COORDMAPPERS_SPHERICAL_HEADER

#include <rt/coordmappers/coordmapper.h>
#include <core/matrix.h> 
#include <core/point.h>
#include<core/vector.h>
#include <rt/intersection.h>

namespace rt {

class Vector;

class SphericalCoordMapper : public CoordMapper {
public:
    SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef);
    virtual Point getCoords(const Intersection& hit) const;
    Point origin;
    Vector zenith, azimuth;
    float radius, scaleX, scaleY;
};

}

#endif