#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <vector>
#include <rt/groups/group.h>
#include <rt/bbox.h>    
// #include <mutex>

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

     std::pair<float, BBox> getBounds() const {
        BBox b = BBox::empty();
        float a = 0;
        for (uint i = 0; i < p.size(); i++) {
            b.extend(p[i]->getBounds());
            a = a + p[i]->getArea();
        };
        return std::make_pair(a, b);
    }
};

class BVH : public Group {
public:
    BVHNode* root = new BVHNode();
    // mutable std::recursive_mutex mtx;   
    BVH();
    bool SAH = false;
    int bin = 16;
    float bins[16], bins_n[16], binr[16],cost[16];

    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual BBox getBounds() const;
    virtual float MiddleSplit(int bool_axis, BVHNode* parent);
    virtual float SAHSplit(int bool_axis, float len_axis, BVHNode* parent);
    virtual void rebuildIndex();
    virtual void buildRecursive(BVHNode* parent);
    virtual void add(Primitive* prim);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);   
    virtual float getArea() const;

    struct SerializedNode {
        bool isLeaf;
        BBox bbox;

        // For leaves only
        std::vector<Primitive*> primitives;

        // For internal nodes only
        size_t leftChildId;
        size_t rightChildId;
    };

    // Implement this function if you want to take part in the BVH speed competition
    struct Output {
        virtual void setNodeCount(size_t nodeCount) = 0;
        virtual void setRootId(size_t rootId) = 0;
        virtual void writeNode(size_t nodeId, const SerializedNode& node) = 0;
    };
    void serialize(Output& output);

    // Implementing this is optional and not needed for the BVH speed competition,
    // but it will allow you to run the benchmark utility and test your BVH exporter.
    struct Input {
        virtual size_t getNodeCount() = 0;
        virtual size_t getRootId() = 0;
        virtual const SerializedNode& readNode(size_t nodeId) = 0;
    };
    void deserialize(Input& input);
};

}

#endif
