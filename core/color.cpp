#include <core/color.h>
#include <core/scalar.h>
#include <core/float4.h>

namespace rt {

RGBColor::RGBColor(const Float4& f4)
{
/* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::operator + (const RGBColor& c) const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::operator - (const RGBColor& c) const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::operator * (const RGBColor& c) const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool RGBColor::operator == (const RGBColor& c) const {
    /* TODO */ NOT_IMPLEMENTED;
}

bool RGBColor::operator != (const RGBColor& b) const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::clamp() const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::gamma(float gam) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float RGBColor::luminance() const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator * (float scalar, const RGBColor& c) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator * (const RGBColor& c, float scalar) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator / (const RGBColor& c, float scalar) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
