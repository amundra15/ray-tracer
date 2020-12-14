#ifndef CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER
#define CG1RAYTRACER_LIGHTS_PROJECTIVELIGHT_HEADER

#include <core/scalar.h>
#include <core/vector.h>
#include <rt/lights/pointlight.h>

namespace rt {

class ProjectiveLight : public PointLight {
public:
	ProjectiveLight() {}
	ProjectiveLight(const Point& position, const RGBColor& intensity);
    virtual RGBColor getIntensity(const LightHit& irr) const;
};

}

#endif
