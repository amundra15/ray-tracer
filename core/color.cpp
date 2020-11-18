#include <core/color.h>
#include <core/scalar.h>
#include <core/float4.h>

namespace rt {

RGBColor::RGBColor(const Float4& f4)
{
/* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::operator + (const RGBColor& c) const {
    return RGBColor(this->r + c.r, this->g + c.g, this->b + c.b);
}

RGBColor RGBColor::operator - (const RGBColor& c) const {
    return RGBColor(this->r - c.r, this->g - c.g, this->b - c.b);
}

RGBColor RGBColor::operator * (const RGBColor& c) const {
    return RGBColor(this->r * c.r, this->g * c.g, this->b * c.b);
}

bool RGBColor::operator == (const RGBColor& c) const {
    return (this->r == c.r) && (this->g == c.g) && (this->b == c.b);
}

bool RGBColor::operator != (const RGBColor& b) const {
    return !((this->r == b.r) && (this->g == b.g) && (this->b == b.b));
}

RGBColor RGBColor::clamp() const {
    float r_clampped = std::min(1.0f,std::max(0.0f,this->r));
    float g_clampped = std::min(1.0f,std::max(0.0f,this->g));
    float b_clampped = std::min(1.0f,std::max(0.0f,this->b));
    return RGBColor(r_clampped,g_clampped,b_clampped);
}

RGBColor RGBColor::gamma(float gam) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float RGBColor::luminance() const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator * (float scalar, const RGBColor& c) {
    return RGBColor(scalar*c.r, scalar*c.g, scalar*c.b);
}

RGBColor operator * (const RGBColor& c, float scalar) {
    return RGBColor(scalar*c.r, scalar*c.g, scalar*c.b);
}

RGBColor operator / (const RGBColor& c, float scalar) {
    return RGBColor(c.r/scalar, c.g/scalar, c.b/scalar);
}

}
