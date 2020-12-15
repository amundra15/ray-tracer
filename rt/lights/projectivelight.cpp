#include <rt/lights/projectivelight.h>
#include <core/julia.h>

namespace rt {

static const int numIter = 512;

int juliaLight(const Vector& v, const Point& c) {
    Vector p = v;
    int i=0;
    for (i = 0; i<numIter; ++i) {
        if (p.lensqr()>1.0e+8)
            break;
        Vector q = p;
        q.y = -p.y;
        p = Vector(dot(q,p), cross(q,p).z, 0.0f) + c - Point::rep(0.0f);
    }
    return i;
}

float a1computeLightWeight(const Vector& direction, const Point& c, float div) {
    int numIter = juliaLight(direction, c);
    return numIter/(numIter+div);
}

RGBColor a1computeLightColor(const Vector& direction) {
    RGBColor color = RGBColor::rep(0.0f);

    Vector projectedDirection = Vector(direction.x, direction.y, 0);

    color = color + a1computeLightWeight(projectedDirection, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
    color = color + a1computeLightWeight(projectedDirection, Point(-0.6f, 0.2f, 0.0f), 64.0f) * 0.2f * RGBColor(0.5f, 0.5f, -0.2f);
    color = color + a1computeLightWeight(projectedDirection, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.2f, 0.3f, 0.4f);
    return RGBColor::rep(1.0f) - color;
}

ProjectiveLight::ProjectiveLight(const Point& position, const RGBColor& intensity)
{
	this->position = position;
	this->intensity = intensity;
}

RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const {
	return a1computeLightColor(irr.direction) * intensity/(irr.distance * irr.distance);
}

}
