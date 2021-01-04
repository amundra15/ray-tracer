#include <rt/coordmappers/world.h>

namespace rt {

Point WorldMapper::getCoords(const Intersection& hit) const {
   Point hitPoint = hit.hitPoint();
        return Point(scale.x * hitPoint.x, scale.y * hitPoint.y, scale.z * hitPoint.z);
}

WorldMapper::WorldMapper()
{  
        scale = Vector(1.0f, 1.0f, 1.0f); //point
}

WorldMapper::WorldMapper(const Vector& scale)
   :scale(scale){}

}