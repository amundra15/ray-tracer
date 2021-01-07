#include <rt/coordmappers/plane.h>
#include <rt/intersection.h>


namespace rt
{
    PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2)
    :e1(e1), e2(e2)
    {
        Vector normal = cross(e1, e2);
        transformation = Matrix::system(e1, e2, normal).invert();
    }
    Point PlaneCoordMapper::getCoords(const Intersection& hit) const 
    {
        //Point hitPoint = hit.hitPoint();
        Point translatedPoint = transformation * hit.local();
        //std::cout<<translatedPoint.x / e1.length()<<std::endl;
        return translatedPoint;

    } 
}