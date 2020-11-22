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
	RGBColor clr = RGBColor(0, 0, 0);

	if(intersectionObj)
	{
		float interpolate = (intersectionObj.distance - nearDist) / (farDist - nearDist);
		interpolate = interpolate < 0 ? 0 : interpolate;
		interpolate = interpolate > 1 ? 1 : interpolate;

		float cosineVal = (dot(intersectionObj.normal(),-ray.d));
		cosineVal = cosineVal < 0 ? 0 : cosineVal;


		clr = (
					(interpolate * farColor) + ((1 - interpolate) * nearColor)
				) * cosineVal;
	
		
		
	}
	
		return clr;
}

}