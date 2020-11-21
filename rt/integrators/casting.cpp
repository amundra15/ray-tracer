#include <rt/integrators/casting.h>
#include <vector>
// #include <rt/primitive.h>
#include <rt/world.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {

	Intersection intersectionObj = world->scene->intersect(ray);

	float grayVal = std::abs(dot(ray.d,intersectionObj.normal()));
	return RGBColor::rep(grayVal);
}

}
