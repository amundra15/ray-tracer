#ifndef CG1RAYTRACER_LIGHTS_SPOTLIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_SPOTLIGHT_HEADER

#include <core/scalar.h>
#include <core/vector.h>
#include <rt/lights/pointlight.h>

namespace rt {

class SpotLight : public PointLight {
public:
	SpotLight() {}
	SpotLight(const Point& position, const Vector& direction, float angle, float exp, const RGBColor& intensity);
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}

#endif
