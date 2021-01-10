#include <rt/coordmappers/spherical.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
{
    this->sphorigin = origin;
    this->sphzenith = zenith;
    this->sphazimuthRef = azimuthRef;
    this->sphscaleX = sphazimuthRef.length();
    this->sphscaleY = sphzenith.length();
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    Vector hitvect  = hit.local()-sphorigin;

    Vector z = cross(sphzenith, sphazimuthRef).normalize() * sphscaleX;

    float theta = acosf(dot(hitvect.normalize(), sphzenith.normalize()));

    //float u = dot(hitvect, sphazimuthRef) /sphazimuthRef.lensqr();
    //float v = dot(hitvect, z) / z.lensqr();
    float u = dot(hitvect.normalize(), sphazimuthRef.normalize());
    float v = dot(hitvect.normalize(), z.normalize());
    //float phi = atan2f(dot(Vector(0,v,0).normalize(),sphazimuthRef.normalize()),dot(Vector(u,0,0).normalize(),sphazimuthRef.normalize()) );
    float phi = atan2f(v,u);
    //float phi = acosf(dot(Vector(u, 0.0f, v).normalize(), sphazimuthRef.normalize()));



    return Point (-phi / (2 * pi *sphscaleX), theta/(pi*sphscaleY), hitvect.length());

        
}

}
