#include <rt/solids/quad.h>

namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material)
{
    this->origin = origin;
	this->s1 = span1;
	this->s2 = span2;
	this->n = cross(s1, s2).normalize();
	a = origin;
	b = origin + s1;
	c = origin + s2;
	d = origin + s1 + s2;

	this->t1 = Triangle(a, b, c, texMapper, material);
	this->t2 = Triangle(b, d, c, texMapper, material);
}

BBox Quad::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {
   
		Intersection t1_intersect = t1.intersect(ray, previousBestDistance);
		if (t1_intersect && t1_intersect.distance > 0 && t1_intersect.distance < previousBestDistance) {
			Vector hp = t1_intersect.hitPoint() - a;
			Point local = Point(dot(hp, s1) / s1.lensqr(), dot(hp, s2) / s2.lensqr(), 0);
			return Intersection(t1_intersect.distance, ray, this, t1_intersect.normal(), local);
		}
		
		Intersection t2_intersect = t2.intersect(ray, previousBestDistance);
		if (t2_intersect && t2_intersect.distance > 0 && t2_intersect.distance < previousBestDistance) {
			Vector hp = t2_intersect.hitPoint() - a;
			Point local = Point(dot(hp, s1) / s1.lensqr(), dot(hp, s2) / s2.lensqr(), 0);
			return Intersection(t2_intersect.distance, ray, this, t2_intersect.normal(), local);
		}

		return Intersection::failure();
}

Solid::Sample Quad::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Quad::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
