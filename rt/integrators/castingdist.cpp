#include <rt/integrators/castingdist.h>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world)
{
    /* TODO */
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
