#include <rt/solids/solid.h>

namespace rt {

Solid::Solid(CoordMapper* texMapper, Material* material) {}
// Solid::Solid(const float& coeff[10], CoordMapper* texMapper, Material* material)
// {
// 	a = coeff[0];
// 	b = coeff[1];
// 	c = coeff[2];
// 	d = coeff[3];
// 	e = coeff[4];
// 	f = coeff[5];
// 	g = coeff[6];
// 	h = coeff[7];
// 	i = coeff[8];
// 	j = coeff[9];
// }

Solid::Solid(const float& a, const float& b, const float& c, const float& d, const float& e, const float& f, const float& g, const float& h, const float& i, const float& j, CoordMapper* texMapper, Material* material)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->e = e;
	this->f = f;
	this->g = g;
	this->h = h;
	this->i = i;
	this->j = j;

	this->material = material;
	this->texMapper = texMapper;
}


Intersection Solid::intersect(const Ray& ray, float previousBestDistance) const 
{
	float x1 = ray.o.x;
	float y1 = ray.o.y;
	float z1 = ray.o.z;
	float x2 = ray.d.x;
	float y2 = ray.d.y;
	float z2 = ray.d.z;
	
	float t = FLT_MAX;

	float A = a*x2*x2 + b*y2*y2 + c*z2*z2 + d*x2*y2 + e*x2*z2 + f*y2*z2;
	float B = 2*a*x1*x2 + 2*b*y1*y2 + 2*c*z1*z2 + d*x1*y2 + d*x2*y1 + e*x1*z2 + e*x2*z1 + f*y1*z2 + f*y2*z1 + g*x2 + h*y2 + i*z2;
	float C = a*x1*x1 + b*y1*y1 + c*z1*z1 + d*x1*y1 + e*x1*z1 + f*y1*z1 + g*x1 + h*y1 + i*z1 + j;

	float discriminator = B*B - 4*A*C;

	if(discriminator<0)
		t = -1;		//will result in intersection failure
	else if(discriminator==0)
		t = -B/(2*A);
	else
	{
		float t1 = (-B-sqrt(discriminator)) / (2*A);
		float t2 = (-B+sqrt(discriminator)) / (2*A);

		//select the minimum positive value between the two
		if (t1 > 0)
			t = std::min(t1,t);
		if (t2 > 0)
			t = std::min(t2,t);
	}

	//consider intersection only if it is in the direction of the camera
	if(t>0 && t<previousBestDistance)
	{
		Point intersectionPoint = ray.o + (t*ray.d);

		float px = intersectionPoint.x;
		float py = intersectionPoint.y;
		float pz = intersectionPoint.z;

		float nx = 2*a*px + d*py + e*pz + g;
		float ny = 2*b*py + d*px + f*pz + h;
		float nz = 2*c*pz + e*px + f*py + i;
		Vector normal = Vector(nx,ny,nz).normalize();

		return Intersection(t, ray, this, normal, intersectionPoint);
	}
	else
		return Intersection::failure();
}


BBox Solid::getBounds() const 
{
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample Solid::sample() const {
    NOT_IMPLEMENTED;
}

float Solid::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
