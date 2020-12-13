#include <rt/integrators/raytrace.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {

	RGBColor totalIntensity = RGBColor::rep(0);

	Intersection intersectionObj = world->scene->intersect(ray);

	if(intersectionObj)
	{
		for(int iter = 0; iter < world->light.size(); iter++)
		{
			Light* l = world->light[iter];
			LightHit lightHit = l->getLightHit(intersectionObj.hitPoint());

			//confirm that the shadow ray and the primary ray leave the surface on the same side
			if (sgn(dot(lightHit.direction,intersectionObj.normal())) != sgn(dot(-ray.d,intersectionObj.normal())))
				continue;
			
			//trace shadow ray
			Ray shadowRay = Ray(intersectionObj.hitPoint(), lightHit.direction.normalize());
			Intersection shadowObj = world->scene->intersect(shadowRay, lightHit.distance);
			if(shadowObj)
				continue;

			//if no object in between, compute the intensity
			RGBColor intensity = l->getIntensity(lightHit);

			Material* materialObj = intersectionObj.solid->material;
			RGBColor reflectedIntensity = intensity * materialObj->getReflectance(intersectionObj.local(), intersectionObj.normal(), -ray.d, -lightHit.direction);
			RGBColor emittedIntensity = intensity * materialObj->getEmission(intersectionObj.local(), intersectionObj.normal(), -ray.d);

			totalIntensity = totalIntensity + reflectedIntensity + emittedIntensity;
		}

		return totalIntensity;
	}
	else
		return RGBColor::rep(0);
	
}

}