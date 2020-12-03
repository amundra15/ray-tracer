#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>
#include <rt/ray.h>
#include <rt/bbox.h>
#include <float.h>

namespace rt {

class Ray;

class BBox {
public:
    Point min, max;
    Point center;
    bool _flag = false;
    BBox() {}
    BBox(const Point& min, const Point& max)
    {
        if(min != rt::min(min,max)) 
        {   
            //"negative" box; empty box created; no intersection will succeed
            this->max = Point(FLT_MIN,FLT_MIN,FLT_MIN);
            this->min = Point(FLT_MAX,FLT_MAX,FLT_MAX);
        }
        else
        {
            this->min = min;
            this->max = max;
            this->center = 0.5f * (min+max);
        }

    }

    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);

    Vector diagonal() const {
        return max - min;
    }

    float area() const {
        float area_xy = (max.x - min.x) * (max.y - min.y);
        float area_yz = (max.y - min.y) * (max.z - min.z);
        float area_xz = (max.x - min.x) * (max.z - min.z);
        return 2 * (area_xy + area_yz + area_xz); 
    }

    std::pair<float, float> intersect(const Ray& ray) const;

    bool isUnbound();
};

}

#endif