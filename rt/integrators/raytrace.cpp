#include <rt/integrators/raytrace.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/solids/solid.h>
#include <rt/lights/light.h>
#include <rt/materials/material.h>
#include <core/float4.h>
#include <rt/textures/texture.h>
#include <rt/coordmappers/world.h>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

namespace rt {

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {

  RGBColor totalIntensity = RGBColor::rep(0);

  Intersection intersectionObj = world->scene->intersect(ray);

  if(intersectionObj)
  {
    auto tex = intersectionObj.solid->texMapper;
      if (tex == nullptr) {tex = new WorldMapper(Vector::rep(1));}
      Point tex_p = tex->getCoords(intersectionObj);

      totalIntensity = totalIntensity + intersectionObj.solid->material->getEmission(tex_p, intersectionObj.normal(), -ray.d);;
    for(int iter = 0; iter < world->light.size(); iter++)
    {
      Light* l = world->light[iter];
      LightHit lightHit = l->getLightHit(intersectionObj.hitPoint());

      //confirm that the shadow ray and the primary ray leave the surface on the same side
      if (sgn(dot(lightHit.direction,intersectionObj.normal())) != sgn(dot(-ray.d,intersectionObj.normal()))){
        continue;
      }
      
      //trace shadow ray
      Ray shadowRay = Ray(intersectionObj.hitPoint() + 0.0001*lightHit.direction, lightHit.direction.normalize());
      Intersection shadowObj = world->scene->intersect(shadowRay, lightHit.distance);
      if(shadowObj){
        continue;
      }

      //if no object in between, compute the intensity
      RGBColor intensity = l->getIntensity(lightHit);

      Material* materialObj = intersectionObj.solid->material;
      RGBColor reflectedIntensity = intensity * materialObj->getReflectance(tex_p, intersectionObj.normal(), -ray.d, lightHit.direction);
      //RGBColor emittedIntensity = intensity * materialObj->getEmission(intersectionObj.local(), intersectionObj.normal(), -ray.d);

      // std::cout << reflectedIntensity.r << " " << reflectedIntensity.g << " " << reflectedIntensity.b << std::endl;

      totalIntensity = totalIntensity + reflectedIntensity;
    }

    return totalIntensity.clamp();
  }
  else
    return RGBColor::rep(0);
  
}

}