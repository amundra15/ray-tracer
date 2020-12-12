#include <rt/groups/bvh.h>
#include <tuple>
#include <numeric>

namespace rt {

    int max_primitives = 3;

    BVH::BVH() {
    }

    void BVH::rebuildIndex() {
        root->p = primitives;
       std::tie(root->area, root->box) = root->getBounds();

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
            if (SAH) {split = SAHSplit(bool_axis, len_axis, parent);}
            else {split = MiddleSplit(bool_axis, parent);}

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

                if ( pmiddle < split    ) {
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
                 std::tie(parent->left->area, parent->left->box) = parent->left->getBounds();
                if (parent->left->p.size() != parent->p.size()) buildRecursive(parent->left);
            }
            if (parent->right != nullptr) {
                std::tie(parent->right->area, parent->right->box) = parent->right->getBounds();
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

    float BVH::SAHSplit(int bool_axis, float len_axis, BVHNode* parent) {
        for (int i = 0; i < bin; i++) {
            bins[i] = 0; bins_n[i] = 0;
           // binr[i] = (i+1)*(len_axis/bin);
            
        }

        //assign primitives to bin
        float mid; int num;
        // Implement Binning SAH
        for (int i = 0; i < parent->p.size(); i++) {
            BBox pbox = parent->p[i]->getBounds();
            if (bool_axis == 0) {
                mid = (pbox.min.x + pbox.max.x) / 2;
                num = roundf((mid - parent->box.min.x) / len_axis * (bin - 1));
            } else if (bool_axis == 1) {
                mid = (pbox.min.y + pbox.max.y) / 2;
                num = roundf((mid - parent->box.min.y) / len_axis * (bin - 1));
            } else if (bool_axis == 2) {
                mid = (pbox.min.z + pbox.max.z) / 2;
                num = roundf((mid - parent->box.min.z) / len_axis * (bin - 1));
            }
            bins[num] += pbox.area();
            bins_n[num] ++;
        }
        // Compute cost
        float SA_Left = 0, Primitives_Left = 0;
        float minCost = 10000;
        float cost_left;
        float cost_right;
        float sah_split;
        for (int i = 1; i <= bin; i++) {
            SA_Left = 0;
            Primitives_Left = 0;
            for (int j = 0; j < i; j++) {
                SA_Left = SA_Left + bins[j]; Primitives_Left = Primitives_Left + bins_n[j];
            };
            cost_left = SA_Left / parent->area * Primitives_Left;
            cost_right = (parent->area - SA_Left) / parent->area * (parent->p.size() - Primitives_Left);
            //cost[i]=cost_left + cost_right;
            // std::cout<<cost[i]<<std::endl;
            if (cost_left + cost_right < minCost) 
                {
                    sah_split = i; minCost = cost_left + cost_right;
            }
        }
         //std::cout<<cleft+cright<<std::endl;
        
        //float minCost = 10000;
        //int minCostSplitBucket = 0;
        //for (int i = 1; i <= bin; i++) {
            //std::cout<<cost[i]<<std::endl;
          //  if (cost[i] < minCost) {
        //minCost = cost[i];
      //  minCostSplitBucket = i;
       
    //}
  //  sah_split = minCostSplitBucket;
    //std::cout<<sah_split<<std::endl;

//}

       // }
        
        if (bool_axis == 0) return parent->box.min.x + ((sah_split/bin) * len_axis);
        if (bool_axis == 1) return parent->box.min.y + ((sah_split/bin) * len_axis);
        if (bool_axis == 2) return parent->box.min.z + ((sah_split/bin) * len_axis);
    }

    Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
        
        Intersection primitive_hit = Intersection::failure();
        BBox b = BBox();
        float d = previousBestDistance;

        std::vector<BVHNode*> nodes;
        nodes.push_back(this->root);

        BVHNode* n = new BVHNode();

        
        while (nodes.size() > 0) {

            n = nodes.back();
            nodes.pop_back();

            
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
                // float bmin, bmax;
                // if (n->left != nullptr) {
                //     b = n->left->box;
                //     std::tie(bmin, bmax) = b.intersect(ray);
                //     if (bmin < FLT_MAX && bmax > FLT_MIN) {nodes.push_back(n->left);};
                // }
                // if (n->right != nullptr) {
                //     b = n->right->box;
                //     std::tie(bmin, bmax) = b.intersect(ray);
                //     if (bmin < FLT_MAX && bmax > FLT_MIN) {nodes.push_back(n->right);};
                // }



                //check if the current node is behind the any previously computed primitive intersection
                float bmin, bmax;
                std::tie(bmin, bmax) = n->box.intersect(ray);
                if(d < std::min(fabs(bmin),fabs(bmax)))
                    continue;
                    // return primitive_hit;

                bool leftIntersection = 0;
                bool rightIntersection = 0;
                float bmin1, bmin2, bmax1, bmax2;
                if (n->left != nullptr) {
                    b = n->left->box;
                    std::tie(bmin1, bmax1) = b.intersect(ray);
                    leftIntersection = (bmin1 < FLT_MAX && bmax1 > FLT_MIN && !n->left->p.empty());
                    //intersection criteria: intersects with the box, and there is atleast one primitive there
                }
                if (n->right != nullptr) {
                    b = n->right->box;
                    std::tie(bmin2, bmax2) = b.intersect(ray);
                    rightIntersection = (bmin2 < FLT_MAX && bmax2 > FLT_MIN && !n->right->p.empty());
                }


                if (leftIntersection && rightIntersection)
                {
                    //estimate the farther node and put in stack first (so that it pops later)
                    float leftIntersectionDistance = std::min(fabs(bmin1),fabs(bmax1));
                    float rightIntersectionDistance = std::min(fabs(bmin2),fabs(bmax2));
                
                    if(leftIntersectionDistance >= rightIntersectionDistance)
                    {
                        nodes.push_back(n->left);
                        nodes.push_back(n->right);
                    }
                    else
                    {
                        nodes.push_back(n->right);                        
                        nodes.push_back(n->left);
                    }
                }
                else if (leftIntersection) 
                    nodes.push_back(n->left);
                else if (rightIntersection) 
                    nodes.push_back(n->right);

            }
        }

        return primitive_hit;
    }

    BBox BVH::getBounds() const {
        return root->box;
    }

    void BVH::add(Primitive* p) {
        primitives.push_back(p);
    }

    void BVH::setMaterial(Material* m) {
        for(uint iter=0; iter<this->primitives.size(); iter++)
            primitives[iter]->setMaterial(m);
        
    }

    void BVH::setCoordMapper(CoordMapper* cm) {
        /* TODO */ NOT_IMPLEMENTED;
    }
  
	void BVH::serialize(BVH::Output& output) {
    	// To implement this function:
    	// - Call output.setNodeCount() with the number of nodes in the BVH
   	 	/* TODO */
    	// - Set the root node index using output.setRootId()
    	/* TODO */
    	// - Write each and every one of the BVH nodes to the output using output.writeNode()
    	/* TODO */ NOT_IMPLEMENTED;
	}
	void BVH::deserialize(BVH::Input& input) {
    	// To implement this function:
    	// - Allocate and initialize input.getNodeCount() nodes
    	/* TODO */
    	// - Fill your nodes with input.readNode(index)
    	/* TODO */
    	// - Use the node at index input.getRootId() as the root node
    	/* TODO */ NOT_IMPLEMENTED;
	}

   float BVH::getArea() const {
        return 0;
    }

}
