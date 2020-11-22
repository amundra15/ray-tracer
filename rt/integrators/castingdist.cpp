#include <rt/integrators/castingdist.h>
#include <rt/world.h>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world)
{
    this->world = world;
    this->nearColor = nearColor;
    this->farColor = farColor;
    this->nearDist = nearDist;
    this->farDist = farDist;
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {

	Intersection intersectionObj = world->scene->intersect(ray);

	if(intersectionObj)
	{
		float distanceFraction = (intersectionObj.distance - nearDist) / (farDist - nearDist);
		RGBColor interpolatedColor = nearColor * (1.0f-distanceFraction) + farColor * distanceFraction;
	
		float cosineVal = std::abs(dot(ray.d,intersectionObj.normal()));
		return RGBColor(interpolatedColor*cosineVal);
	}
	else
		return RGBColor::rep(0);
}

}
