#include "interpolate.h"

namespace rt {

template <typename T>
T lerp(const T& px0, const T& px1, float xPoint) {
    return px0 * (1 - xPoint) + px1 * xPoint ;
}

template <typename T>
T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight) {
    return a * aWeight + b * bWeight + c * (1 - aWeight - bWeight);
}

template <typename T>
T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xWeight, float yWeight) {
    return lerp(lerp(px0y0, px1y0, xWeight), lerp(px0y1, px1y1, xWeight),  yWeight);

}

template <typename T>
T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
    const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
    float xPoint, float yPoint, float zPoint)
{
    T c00 = px0y0z0 * (1 - xPoint) + px1y0z0 * xPoint;
    T c10 = px0y1z0 * (1 - xPoint) + px1y1z0 * xPoint;
    T c01 = px0y0z1 * (1 - xPoint) + px1y0z1 * xPoint;
    T c11 = px0y1z1 * (1 - xPoint) + px1y1z1 * xPoint;
    
    T c0 = c00 * (1 - yPoint) + c10 * yPoint;
    T c1 = c01 * (1 - yPoint) + c11 * yPoint; 

    return c0 * (1 - zPoint) + c1 * zPoint;
}

}