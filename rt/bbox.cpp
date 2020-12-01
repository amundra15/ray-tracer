#include <rt/bbox.h>
#include <rt/primitive.h>
#include <algorithm>

namespace rt {

	BBox BBox::empty() {
		BBox empty_obj = BBox();
		empty_obj.max = Point(FLT_MIN,FLT_MIN,FLT_MIN);
		empty_obj.min = Point(FLT_MAX,FLT_MAX,FLT_MAX);
		return empty_obj;
	}

	BBox BBox::full() {
		BBox full_obj = BBox();
	full_obj.min = Point(FLT_MIN,FLT_MIN,FLT_MIN);
	full_obj.max = Point(FLT_MAX,FLT_MAX,FLT_MAX);
	//full_obj._flag = true;
	return full_obj;
		
	}


	void BBox::extend(const Point& point) {
		if(min != rt::min(min,max)) {
			min = point; max = point;
		}
		else {
			min = rt::min(min, point);
			max = rt::max(max, point);
		}
		
	}

	void BBox::extend(const BBox& bbox) {
    if(min != rt::min(min,max)) {
		min = bbox.min;
		max = bbox.max;
	}
	else {
			
			min = rt::min(min, bbox.min);
			max = rt::max(max, bbox.max);
		}
		
	}

	std::pair<float, float> BBox::intersect(const Ray& ray) const {
			//handle full and empty objects TODO_a
	// if (obj_description = -)

	//intersection distances of the ray with the 6 planes defined by the 2 points
	//refernce: https://developer.arm.com/documentation/100140/0302/advanced-graphics-techniques/implementing-reflections-with-a-local-cubemap/ray-box-intersection-algorithm
	Vector t1 = (this->min - ray.o) / ray.d;
	Vector t2 = (this->max - ray.o) / ray.d;

	//intersection criteria
	//closer and farther plane intersection points for each dimension
	Vector t_near = rt::min(t1,t2);		//point of intersection with three closer xyz planes
	Vector t_far = rt::max(t1,t2);		//point of intersection with three farther xyz planes

	float t_near_farthest = std::max(std::max(t_near.x,t_near.y),t_near.z);		//where the ray enter the box; largest distance among the three closer planes 
	float t_far_closest = std::min(std::min(t_far.x,t_far.y),t_far.z);			//where the ray leaves the box; shortest distance among the three farther planes

	
		if (t_near_farthest > t_far_closest) { return std::make_pair(FLT_MAX, FLT_MIN); };
		return std::make_pair(t_near_farthest,t_far_closest);
	}

	bool BBox::isUnbound() {
		Point min_test = rt::min(min, max);
		Point max_test = rt::max(min, max);
		return (
			min_test.x == -FLT_MAX || min_test.y == -FLT_MAX || min_test.z == -FLT_MAX ||
			max_test.x == FLT_MAX || max_test.y == FLT_MAX || max_test.z == FLT_MAX);
	}

}