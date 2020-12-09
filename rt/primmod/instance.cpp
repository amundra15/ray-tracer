#include <rt/primmod/instance.h>
#include <math.h>

namespace rt {

Instance::Instance(Primitive* content)
{
    primitive = content;
    T = Matrix::identity();
    T_inv = Matrix::identity();
}

Primitive* Instance::content() {
    return primitive;
}

void Instance::reset() {
    T = Matrix::identity();
    T_inv = Matrix::identity();
}

void Instance::translate(const Vector& t) {
    Matrix translation = Matrix::identity();
    translation[0][3] = t.x;
    translation[1][3] = t.y;
    translation[2][3] = t.z;

    Matrix invertedTranslation = Matrix::identity();
    invertedTranslation[0][3] = -t.x;
    invertedTranslation[1][3] = -t.y;
    invertedTranslation[2][3] = -t.z;

    T = product(translation,T);
    T_inv = product(T_inv,invertedTranslation);
}

void Instance::rotate(const Vector& nnaxis, float angle) {

    Vector r = nnaxis.normalize();

     //construct an orthogonal basis using the rotation axis
    float minVal = std::min(std::min(r.x,r.y),r.z);

    Vector s_;
    if(abs(minVal-r.x) <= epsilon)
        s_ = Vector(0,-r.z,r.y);
    else if(abs(minVal-r.y) <= epsilon)
        s_ = Vector(-r.z,0,r.x);
    else if(abs(minVal-r.z) <= epsilon)
        s_ = Vector(-r.y,r.x,0);

    Vector s = s_.normalize();
    Vector t = cross(r,s).normalize();

    Matrix systemChange = Matrix::system(r,s,t);


    //rotation matrix (arounf x-axis, since that's how we have constructed the new system)
    Matrix rotation = Matrix::identity();
    rotation[1][1] = cos(angle);
    rotation[1][2] = -sin(angle);
    rotation[2][1] = sin(angle);
    rotation[2][2] = cos(angle);


    Matrix compositeRotation = product(systemChange, product(rotation,systemChange.transpose()));
    Matrix compositeRotation_inv = product(systemChange, product(rotation.transpose(),systemChange.transpose()));

    T = product(compositeRotation,T);
    T_inv = product(T_inv,compositeRotation_inv);
}

void Instance::scale(float f) {   
    Matrix scaling = Matrix::identity();
    scaling[0][0] = f;
    scaling[1][1] = f;
    scaling[2][2] = f;

    float inverted_f = 1.0/f; 
    Matrix invertedScaling = Matrix::identity();
    invertedScaling[0][0] = inverted_f;
    invertedScaling[1][1] = inverted_f;
    invertedScaling[2][2] = inverted_f;

    T = product(scaling,T);
    T_inv = product(T_inv,invertedScaling);
}

void Instance::scale(const Vector& s) {
    Matrix scaling = Matrix::identity();
    scaling[0][0] = s.x;
    scaling[1][1] = s.y;
    scaling[2][2] = s.z;

    Matrix invertedScaling = Matrix::identity();
    invertedScaling[0][0] = 1.0/s.x;
    invertedScaling[1][1] = 1.0f/s.y;
    invertedScaling[2][2] = 1.0f/s.z;

    //since we are using T only for the normals, we will be replacing scaling with transpose(inverse(scaling)) for this case (non-uniform scaling) - check lecture slides for details
    // T = product(scaling, T_inv.transpose());
    T = product(invertedScaling.transpose(),T);
    T_inv = product(T_inv,invertedScaling);
}

void Instance::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {

    //inverse transform the ray
    Ray transformedRay;
    transformedRay.o = T_inv * ray.o;
    transformedRay.d = T_inv * ray.d;

    //since previousBestDistance is along the ray, it will scale same as the ray normal after the transformation
    float scalingFactor = transformedRay.d.length();
    previousBestDistance *= scalingFactor;
    transformedRay.d = transformedRay.d / scalingFactor;      //normlaise the ray direction vector

    Intersection intersectionObj = primitive->intersect(transformedRay, previousBestDistance);


    if(intersectionObj)
    {        
        //the ray in the intersection object should be the original ray
        intersectionObj.ray = ray;
        intersectionObj.distance *= 1.0f/scalingFactor;
        intersectionObj.normal_vec = (T * intersectionObj.normal_vec).normalize();      //TODO_a: make sure T is supposed to be used here and not T_inv
    }

    return intersectionObj;
}

BBox Instance::getBounds() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Instance::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}