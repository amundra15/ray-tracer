#include <rt/cameras/dofperspective.h>
#include <rt/solids/disc.h>
#include <rt/ray.h>
#include <cmath>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius)
{
	this->center = center;
	this->d = forward.length();
	this->w = -forward.normalize();
	this->u = d * tan(horizontalOpeningAngle/2) * cross(up,w).normalize();
	this->v = d * tan(verticalOpeningAngle/2) * cross(w,u).normalize();
	this->focalDistance = focalDistance;
	this->apertureRadius = apertureRadius;
}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {

	Vector primaryDirection = (-d*w + x*u + y*v).normalize();
	Point focalPoint = center + focalDistance*primaryDirection;

	Disc lensAperature = Disc(center, w, apertureRadius, nullptr, nullptr);
	Point pointOnLens = lensAperature.sample().point;

	Vector secondaryDirection = focalPoint - pointOnLens;

    return Ray(pointOnLens, secondaryDirection.normalize());
}

}