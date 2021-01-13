#ifndef CG1RAYTRACER_GROUPS_MOTION_BLUR_HEADER
#define CG1RAYTRACER_GROUPS_MOTION_BLUR_HEADER

#include <core/random.h>
#include <core/matrix.h>
#include <core/interpolate.h>
#include <rt/groups/group.h>
#include <rt/primmod/instance.h>

namespace rt {

class MotionBlur : public Group {
public:
	Primitive* p;
	Matrix tr = Matrix::identity();

	MotionBlur() {}
	void translate(const Vector& t) {
        Matrix translate = Matrix::identity();
		translate[0][3] = t.x;
		translate[1][3] = t.y;
		translate[2][3] = t.z;
		tr = product(translate, tr);
    };

    virtual BBox getBounds() const {
        BBox box = p->getBounds();
		box.extend(tr * box.min);
		box.extend(tr * box.max);
		return box;
    };

    virtual Intersection intersect(const Ray& ray, float previousBestDistance) const {
        Instance p_inst = Instance(p);
		p_inst.T_inv = product(p_inst.T_inv, lerp(Matrix::identity(), tr, random()));
		return p_inst.intersect(ray, previousBestDistance);
    };

    virtual void rebuildIndex() {};
    virtual void add(Primitive* primitive) {p = primitive;};
    virtual void setMaterial(Material* m) {p->setMaterial(m);};
    virtual void setCoordMapper(CoordMapper* cm) {p->setCoordMapper(cm);};
    virtual float getArea() const {return p->getArea();};
};

}

#endif