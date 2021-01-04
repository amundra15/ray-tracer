#include <rt/textures/checkerboard.h>
#include <math.h>
#include <core/point.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black)
{
    this->w = white;
    this->b = black;
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {

    int lu = floor(coord.x*2);
    int lv = floor(coord.y*2);
    int lw = floor(coord.z*2);

    int p = abs(lu + lv + lw) % 2;
    if (p == 1) {return b;}
    return w;
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
    return RGBColor::rep(0.0f);
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
    return RGBColor::rep(0.0f);
}

}