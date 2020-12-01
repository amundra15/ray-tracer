#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>    

namespace rt {

class BVHNode {
public:
    BVHNode() {}

    BBox box;
    BVHNode* left = nullptr;
    BVHNode* right = nullptr;
    typedef std::vector<Primitive *> primitives;
    primitives p;
    float area;

    void add(Primitive* primitive) {
        p.push_back(primitive);
    }

     BBox getBounds() const {
        BBox b = BBox::empty();
        float a = 0;
        for (uint i = 0; i < p.size(); i++) {
            b.extend(p[i]->getBounds());
            
        };
        return b;
    }
};

class BVH : public Group {
public:
    BVHNode* root = new BVHNode();
    BVH();
    virtual ~BVH();
    int bin = 16;
    float bins[16], bins_n[16];
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual BBox getBounds() const;
    virtual float MiddleSplit(int bool_axis, BVHNode* parent);
    virtual void rebuildIndex();
    virtual void buildRecursive(BVHNode* parent);
    virtual void add(Primitive* prim);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
    virtual float getArea() const;
};

}

#endif