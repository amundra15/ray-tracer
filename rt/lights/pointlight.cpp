#include <rt/lights/pointlight.h>

#include <core/vector.h>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity)
{
	this->position = position;
	this->intensity = intensity;
}

LightHit PointLight::getLightHit(const Point& p) const {
    
    Vector dir = position - p;
    float len = dir.length();

    LightHit l;
    l.direction = dir/len;
    l.distance = len;
    l.normal = -dir/len;

    return l;
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
	return intensity/(irr.distance * irr.distance);
}

}
