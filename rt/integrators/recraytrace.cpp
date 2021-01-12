#include <rt/integrators/recraytrace.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/solids/solid.h>
#include <rt/lights/light.h>
#include <rt/materials/material.h>
#include <core/float4.h>
#include <rt/coordmappers/coordmapper.h>

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

namespace rt {

#define MAX_DEPTH 6

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
	int depth = 1;
	return getRadiance(ray, depth);
}

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray, int depth) const 
{
	RGBColor totalIntensity = RGBColor::rep(0.0f);
	
	//check recurssion depth
	if (depth >= MAX_DEPTH) 
		return totalIntensity;

	Intersection intersectionObj = world->scene->intersect(ray);
	
	if (intersectionObj) 
	{
		Material* objMaterial = intersectionObj.solid->material;

		Vector hn = intersectionObj.normal().normalize();
		Point hp = intersectionObj.hitPoint();
		Vector out_dir = ray.d.normalize();		//note that out_dir is incoming at a point here, whereas, it is outgoing in the slides

		// Texture
		auto tex = intersectionObj.solid->texMapper;
		if (tex == nullptr) {tex = tex_nullptr;}
		Point tex_p = tex->getCoords(intersectionObj);

		//emitted intensity
		totalIntensity = totalIntensity + objMaterial->getEmission(tex_p, hn, -out_dir);;
			
		if (objMaterial->useSampling() == Material::Sampling::SAMPLING_NOT_NEEDED) 
		{
			// SAMPLING_NOT_NEEDED - non-mirror
			//iterate over the light sources and integrate the reflectance
			for (auto light: world->light) 
			{
				LightHit lh = light->getLightHit(hp);
				
				//confirm that the shadow ray and the primary ray leave the surface on the same side
				if (sgn(dot(lh.direction,intersectionObj.normal())) != sgn(dot(-ray.d,intersectionObj.normal())))
					continue;
					
				//trace shadow ray
				Vector in_dir = lh.direction.normalize();
				Ray shadowRay = Ray(hp + epsilon * in_dir, in_dir);
				Intersection shadowObj = world->scene->intersect(shadowRay, lh.distance - 2.0f * epsilon);
				if(shadowObj)
					continue;

				//if no object in between, compute the reflected intensity
				RGBColor refl_totalIntensity = objMaterial->getReflectance(tex_p, hn, -out_dir, in_dir);
				totalIntensity = totalIntensity + (refl_totalIntensity * light->getIntensity(lh));
			}
		} 
		else if (objMaterial->useSampling() == Material::Sampling::SAMPLING_ALL) 
		{
			// SAMPLING_ALL - mirror material
			//shoot a secondary ray in the reflected ray direction
			//hn = dot(ray.d, intersectionObj.normal()) > 0 ? -intersectionObj.normal() : intersectionObj.normal();
			Material::SampleReflectance sample = objMaterial->getSampleReflectance(tex_p, hn, -out_dir);
			Vector in_dir = sample.direction.normalize();

			Ray secondary_ray = Ray(hp + in_dir * epsilon, in_dir);
			totalIntensity = totalIntensity + sample.reflectance * getRadiance(secondary_ray, depth + 1);
		} 
		else if (objMaterial->useSampling() == Material::Sampling::SAMPLING_SECONDARY) 
		{
			// SAMPLING_SECONDARY - combination of mirror and non-mirror
			//iterate over the light sources and integrate the reflectance
			for (auto light: world->light) 
			{
				LightHit lh = light->getLightHit(hp);

				//confirm that the shadow ray and the primary ray leave the surface on the same side
				if (sgn(dot(lh.direction,intersectionObj.normal())) != sgn(dot(-ray.d,intersectionObj.normal())))
					continue;
					
				//trace shadow ray
				Vector in_dir = lh.direction.normalize();
				Ray shadowRay = Ray(hp + epsilon * in_dir, in_dir);
				Intersection shadowObj = world->scene->intersect(shadowRay, lh.distance);
				if(shadowObj)
					continue;

				//if no object in between, compute the reflected intensity
				RGBColor refl_totalIntensity = objMaterial->getReflectance(tex_p, hn, -out_dir, in_dir);
				totalIntensity = totalIntensity + (refl_totalIntensity * light->getIntensity(lh));
			}

			//shoot a secondary ray in the reflected ray direction
			Material::SampleReflectance sample = objMaterial->getSampleReflectance(tex_p, hn, -out_dir);
			Vector in_dir = sample.direction.normalize();

			Ray secondary_ray = Ray(hp + in_dir * epsilon, in_dir);
			RGBColor refl_totalIntensity = getRadiance(secondary_ray, depth + 1);
			
			totalIntensity = totalIntensity + refl_totalIntensity * sample.reflectance;
		}
		
		return totalIntensity;	
	}
	
	else
		return RGBColor::rep(0.0f);
			
}

}