#include <rt/bbox.h>

namespace rt {

BBox BBox::empty() {
    /* TODO */ NOT_IMPLEMENTED;
}

BBox BBox::full() {
    /* TODO */ NOT_IMPLEMENTED;
}


void BBox::extend(const Point& point) {
    /* TODO */ NOT_IMPLEMENTED;
}

void BBox::extend(const BBox& bbox) {
    /* TODO */ NOT_IMPLEMENTED;
}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool BBox::isUnbound() {
    /* TODO */ NOT_IMPLEMENTED;
}

}