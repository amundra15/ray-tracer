#include <rt/primmod/instance.h>

namespace rt {

Instance::Instance(Primitive* content)
{
    /* TODO */
}

Primitive* Instance::content() {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::reset() {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::translate(const Vector& t) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::rotate(const Vector& nnaxis, float angle) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::scale(float f) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::scale(const Vector& s) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {
    /* TODO */ NOT_IMPLEMENTED;
}

BBox Instance::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}