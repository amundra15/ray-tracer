#ifndef CG1RAYTRACER_INTEGRATORS_CASTING_HEADER
#define CG1RAYTRACER_INTEGRATORS_CASTING_HEADER

#include <rt/integrators/integrator.h>

namespace rt {

class RayCastingIntegrator : public Integrator {
    World* world;
public:
    RayCastingIntegrator(World* world) : Integrator(world) 
    {
    	this->world = world;
    }
    virtual RGBColor getRadiance(const Ray& ray) const;

};

}

#endif