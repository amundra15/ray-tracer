#include <rt/lights/pointlight.h>

#include <core/vector.h>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity)
{
    /* TODO */
}

LightHit PointLight::getLightHit(const Point& p) const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
