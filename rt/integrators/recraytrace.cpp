
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

	RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray, int depth) const {
		RGBColor totalIntensity = RGBColor(0, 0, 0);
		if (depth >= MAX_DEPTH) {return totalIntensity;}

		Intersection intersectionObj = this->world->scene->intersect(ray);
		if (intersectionObj) {
			Vector hn = intersectionObj.normal().normalize();
			Point hp = intersectionObj.hitPoint();
			Vector out_dir = ray.d.normalize();

			// Texture
			auto tex = intersectionObj.solid->texMapper;
			if (tex == nullptr) {tex = tex_nullptr;}
			Point tex_p = tex->getCoords(intersectionObj);

            totalIntensity = totalIntensity + intersectionObj.solid->material->getEmission(tex_p, hn, -out_dir);;
			
			if (intersectionObj.solid->material->useSampling() == Material::Sampling::SAMPLING_NOT_NEEDED) {
				// SAMPLING_NOT_NEEDED
				for (auto light: this->world->light) {
					LightHit lh = light->getLightHit(hp);
					 if (sgn(dot(lh.direction,intersectionObj.normal())) != sgn(dot(-ray.d,intersectionObj.normal()))){
        continue;
      }
					Vector in_dir = lh.direction.normalize();
					Intersection shadowObj = this->world->scene->intersect(
						Ray(hp + epsilon * in_dir, in_dir)
						,lh.distance - 2.0f * epsilon);
					if ( shadowObj) {continue;}

					RGBColor refl_totalIntensity = intersectionObj.solid->material->getReflectance(
						tex_p, hn, -out_dir, in_dir);
					totalIntensity = totalIntensity + ( refl_totalIntensity * light->getIntensity(lh));
				}
			} else if (intersectionObj.solid->material->useSampling() == Material::Sampling::SAMPLING_ALL) {
				// SAMPLING_ALL
				//hn = dot(ray.d, intersectionObj.normal()) > 0 ? -intersectionObj.normal() : intersectionObj.normal();
				Material::SampleReflectance sample = intersectionObj.solid->
					material->getSampleReflectance(tex_p, hn, -out_dir);
				Vector in_dir = sample.direction.normalize();

				Ray secondary_ray = Ray(hp + in_dir * epsilon, in_dir);
				totalIntensity = totalIntensity + sample.reflectance * this->getRadiance(secondary_ray, depth + 1);
			} else if (intersectionObj.solid->material->useSampling() == Material::Sampling::SAMPLING_SECONDARY) {
				for (auto light: this->world->light) {
					LightHit lh = light->getLightHit(hp);
						 if (sgn(dot(lh.direction,intersectionObj.normal())) != sgn(dot(-ray.d,intersectionObj.normal()))){
        continue;
      }
					Vector in_dir = lh.direction.normalize();
					Intersection shadowObj = this->world->scene->intersect(
						Ray(hp + epsilon * in_dir, in_dir), 
						lh.distance);
					if (shadowObj) {continue;}
					RGBColor refl_totalIntensity = intersectionObj.solid->material->getReflectance(
						tex_p, hn, -out_dir, in_dir);
					totalIntensity = totalIntensity + (refl_totalIntensity * light->getIntensity(lh));
				}
				Material::SampleReflectance sample = intersectionObj.solid->
					material->getSampleReflectance(tex_p, hn, -out_dir);
				Vector in_dir = sample.direction.normalize();
				RGBColor refl_totalIntensity = this->getRadiance(
					Ray(hp + epsilon * in_dir, in_dir),
					depth + 1
				);
				totalIntensity = totalIntensity + refl_totalIntensity * sample.reflectance;
			}
				return totalIntensity;
			
		}
		else
		return RGBColor::rep(0);

		
		
	}

}