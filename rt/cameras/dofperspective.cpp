#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius)
{
    /* TODO */
}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
    /* TODO */ NOT_IMPLEMENTED;
}

}