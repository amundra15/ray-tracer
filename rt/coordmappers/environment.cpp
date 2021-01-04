#include <rt/coordmappers/environment.h>

namespace rt {

EnvironmentMapper::EnvironmentMapper() {
}

Point EnvironmentMapper::getCoords(const Intersection& hit) const {
    return Point(hit.ray.d.x, hit.ray.d.y, hit.ray.d.z);
}

}