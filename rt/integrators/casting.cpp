#include <rt/integrators/casting.h>
#include <rt/world.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {

	Intersection intersectionObj = world->scene->intersect(ray);

	float grayVal;
	if(intersectionObj)
		grayVal = std::abs(dot(ray.d,intersectionObj.normal()));
	else
		grayVal = 0;
	return RGBColor::rep(grayVal);
}

}
