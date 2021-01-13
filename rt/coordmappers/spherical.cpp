#include <rt/coordmappers/spherical.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef)
{
    this->origin = origin;
    this->zenith = zenith;
    this->azimuth = azimuthRef;
    this->scaleX = azimuth.length();
    this->scaleY = zenith.length();
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    //Vector azimuth_new = azimuth - (dot(azimuth,zenith)/dot(zenith,zenith))*zenith;
    Vector hitvect  = hit.local()-origin;

    Vector z = cross(zenith, azimuth);
    Vector azm = cross(z,zenith);

    float theta = acosf(dot(hitvect.normalize(), zenith.normalize()));

    //float u = dot(hitvect, azimuth) /azimuth.lensqr();
    //float v = dot(hitvect, z) / z.lensqr();
    float u = dot(hitvect.normalize(), azm.normalize());
    float v = dot(hitvect.normalize(), z.normalize());
    //float phi = atan2f(dot(Vector(0,v,0),azimuth.normalize()),dot(Vector(u,0,0),azimuth.normalize()) );
    float phi = -atan2f(v,u);
    //float phi = atan2f(dot(Vector(u,v,0).normalize(),z),dot(Vector(0,u,v).normalize(),azimuth.normalize()) );

    //float phi = acosf(dot(Vector(u, 0.0f, v).normalize(), azimuth.normalize()));



    return Point (phi / (2 * pi *scaleX), theta/(pi*scaleY), hitvect.length());

        
}

}
