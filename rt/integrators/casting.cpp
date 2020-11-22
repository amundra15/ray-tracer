#include <rt/integrators/casting.h>
#include <rt/world.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {

	Intersection intersectionObj = world->scene->intersect(ray);

	float grayVal=0;
	if(intersectionObj)
		grayVal = (dot(intersectionObj.normal(),-ray.d));
		grayVal	= grayVal<0 ? 0: grayVal;
	
	return RGBColor::rep(grayVal);
}

}
