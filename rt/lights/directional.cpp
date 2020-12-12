#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
{
    /* TODO */
}

LightHit DirectionalLight::getLightHit(const Point& p) const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
