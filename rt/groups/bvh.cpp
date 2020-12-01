#include <rt/groups/bvh.h>
#include <tuple>
#include <numeric>

namespace rt {

    int max_primitives = 3;

    BVH::BVH() {
    }

    void BVH::rebuildIndex() {
        root->p = primitives;
        root->box = root->getBounds();

        buildRecursive(root); 
    }

    void BVH::buildRecursive(BVHNode* parent) {
        if (parent->p.size() > max_primitives) {
            float lenx = parent->box.max.x - parent->box.min.x;
            float leny = parent->box.max.y - parent->box.min.y;
            float lenz = parent->box.max.z - parent->box.min.z;
            // Get the longest axis length
            float len_axis = std::max(std::max(lenx, leny), lenz);
            int bool_axis = len_axis == lenx ? 0 : 2;
            bool_axis = len_axis == leny ? 1 : bool_axis;

            float split;
            
            split = MiddleSplit(bool_axis, parent);

            std::vector<Primitive *> primitives_list;
            primitives_list = parent->p;

            while (primitives_list.size() > 0) {
                Primitive* temp_p = primitives_list.back();
                primitives_list.pop_back();
                
                BBox pbox = temp_p->getBounds();
                // Get middle point of the primitive
                float pmiddle;
                if (bool_axis == 0) {pmiddle = (pbox.max.x + pbox.min.x) / 2;}
                else if (bool_axis == 1) {pmiddle = (pbox.max.y + pbox.min.y) / 2;}
                else if (bool_axis == 2) {pmiddle = (pbox.max.z + pbox.min.z) / 2;}

                if (
                    pmiddle < split 
                ) {
                    // Add to left child
                    if (parent->left == nullptr) {parent->left = new BVHNode();}
                    parent->left->add(temp_p);
                } else {
                    // Add to right child
                    if (parent->right == nullptr) {parent->right = new BVHNode();}
                    parent->right->add(temp_p);
                }
            }
            //std::cout<<"left"<<parent->left->p.size()<<std::endl;

            //std::cout<<"overall"<<parent->p.size()<<std::endl;
             

            if (parent->left != nullptr) {
                 parent->left->box = parent->left->getBounds();
                if (parent->left->p.size() != parent->p.size()) buildRecursive(parent->left);
            }
            if (parent->right != nullptr) {
                 parent->right->box = parent->right->getBounds();
                if (parent->right->p.size() != parent->p.size()) buildRecursive(parent->right);
            }
        }
    }

    float BVH::MiddleSplit(int bool_axis, BVHNode* parent) {
        // Search for middle point of the longest axis
        float split;
        if (bool_axis == 0) {split = (parent->box.min.x + parent->box.max.x) / 2;}
        else if (bool_axis == 1) {split = (parent->box.min.y + parent->box.max.y) / 2;}
        else if (bool_axis == 2) {split = (parent->box.min.z + parent->box.max.z) / 2;}
        return split;
    }

    Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
        Intersection primitive_hit = Intersection::failure();
        BBox b = BBox();
        float d = previousBestDistance;

        std::vector<BVHNode*> nodes;
        nodes.push_back(this->root);
        //std::cout<<nodes.size()<<std::endl;

        BVHNode* n = new BVHNode();

        
        while (nodes.size() > 0) {
            n = nodes.back();
            nodes.pop_back();
            //
            if (n->left == nullptr && n->right == nullptr) {
                // Leaf
                for (auto primitive: n->p) {
                    Intersection primitive_hit_temp = primitive->intersect(ray, d);
                    if (primitive_hit_temp && primitive_hit_temp.distance < d) {
                        d = primitive_hit_temp.distance;
                        primitive_hit = primitive_hit_temp;
                    }
                }
            } else {
                // Non-Leaf
                float bmin, bmax;
                if (n->left != nullptr) {
                    b = n->left->box;
                    std::tie(bmin, bmax) = b.intersect(ray);
                    if (bmin < FLT_MAX && bmax > FLT_MIN) {nodes.push_back(n->left);};
                }
                if (n->right != nullptr) {
                    b = n->right->box;
                    std::tie(bmin, bmax) = b.intersect(ray);
                    if (bmin < FLT_MAX && bmax > FLT_MIN) {nodes.push_back(n->right);};
                }
            }
        }

        return primitive_hit;
    }

    BBox BVH::getBounds() const {
      /* TODO */ NOT_IMPLEMENTED;
   
    }

    void BVH::add(Primitive* p) {
        primitives.push_back(p);
    }

    void BVH::setMaterial(Material* m) {
        /* TODO */ NOT_IMPLEMENTED;
        
    }

    void BVH::setCoordMapper(CoordMapper* cm) {
        /* TODO */ NOT_IMPLEMENTED;
    }

}
