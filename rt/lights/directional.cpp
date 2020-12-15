#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
{
   this->dir=direction;
   this->intensity=color;
}

LightHit DirectionalLight::getLightHit(const Point& p) const 
{
	LightHit l;
	l.direction = -dir;
	l.distance = FLT_MAX;
	l.normal = l.direction.normalize();
	return l;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
	return intensity;
}

}
