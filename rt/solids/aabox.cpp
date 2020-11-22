#include <rt/solids/aabox.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material)
{
	this->corner1 = corner1;	
	this->corner2 = corner2;	
}

BBox AABox::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
	
	//this section could be quite bug-gy

	//intersection distances of the ray with the 6 points defined by the 2 points
	Vector t1 = (corner1 - ray.o) / ray.d;
	Vector t2 = (corner2 - ray.o) / ray.d;

	//intersection criteria
	Vector t_near = min(t1,t2);
	Vector t_far = max(t1,t2);

	float t_near_farthest = std::max(std::max(t_near.x,t_near.y),t_near.z);
	float t_far_closest = std::min(std::min(t_far.x,t_far.y),t_far.z);

	if(t_near_farthest < t_far_closest)
	{
		//t_near_farthest is the intersection point
		if(t_near_farthest>0 && t_near_farthest<previousBestDistance)
		{
			Point intersectionPoint = ray.o + t_near_farthest*ray.d;
			Vector n;

			//finding intersection plane and computing normal
			if(t_near_farthest == t_near.x)		//intersected with plane parallel to x axis
				n = Vector(1,0,0);
			else if(t_near_farthest == t_near.y)		//intersected with plane parallel to y axis
				n = Vector(0,1,0);			
			else if(t_near_farthest == t_near.z)		//intersected with plane parallel to z axis
				n = Vector(0,0,1);
			else
				std::cout << "Can't find AABB normal" << std::endl;

			return Intersection(t_near_farthest, ray, this, n, intersectionPoint);
		}
	}
	return Intersection::failure();
}

}
