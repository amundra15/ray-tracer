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
	//RGBColor clr = RGBColor(0, 0, 0);

	if(intersectionObj)
	{
		float distanceFraction = (intersectionObj.distance - nearDist) / (farDist - nearDist);
		distanceFraction = distanceFraction < 0 ? 0 : distanceFraction;
		distanceFraction = distanceFraction > 1 ? 1 : distanceFraction;

		float cosineVal = dot(-ray.d,intersectionObj.normal());
		//cosineVal = cosineVal < 0 ? 0 : cosineVal;


		RGBColor interpolatedColor = nearColor * (1.0f-distanceFraction) + farColor * distanceFraction;
				
	
		return interpolatedColor*cosineVal;	
		
	}
	else
		return RGBColor::rep(0);
	
		
}

}