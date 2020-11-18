#include <rt/cameras/perspective.h>
#include <cmath>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
	this->center = center;
	this->d = forward.length();
	this->w = -forward.normalize();
	Vector u = d * tan(horizontalOpeningAngle/2) * cross(up,w).normalize();
	Vector v = d * tan(verticalOpeningAngle/2) * cross(w,u).normalize();
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    Vector direction = -d*w + x*u + y*v;
    return Ray(center,direction.normalize());
}

}
