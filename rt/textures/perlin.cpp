#include <rt/textures/perlin.h>
#include <core/point.h>
#include <vector>
#include <math.h>
#include <core/interpolate.h>

namespace rt {

// returns a value in range -1 to 1
static inline float noise(int x, int y, int z) {
    int n = x + y * 57 + z * 997;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black)
{
    this->w = white;
    this->b = black;
}


rt::RGBColor PerlinTexture::getColor(const Point& coord) {
    float interpolation = 0.0f;
	for (int i = 0; i < f.size(); i++) {
		int lu = floorf(coord.x * f[i]);
		int lv = floorf(coord.y * f[i]);
		int lw = floorf(coord.z * f[i]);

		float wu = coord.x * f[i] - lu;
		float wv = coord.y * f[i] - lv;
		float ww = coord.z * f[i] - lw;

		interpolation = interpolation +
            lerp3d(
                noise(lu,     lv,       lw), 
                noise(lu + 1, lv,       lw),
                noise(lu,     lv + 1,   lw),
                noise(lu + 1, lv + 1,   lw), 
                noise(lu,     lv,       lw + 1), 
                noise(lu + 1, lv,       lw + 1),
                noise(lu,     lv + 1,   lw + 1), 
                noise(lu + 1, lv + 1,   lw + 1),
                wu, 
                wv, 
                ww
            )*a[i];
	}

	interpolation = (interpolation + 1) / 2;
	RGBColor color = lerp(b, w, interpolation);
	return color;
}

rt::RGBColor PerlinTexture::getColorDX(const Point& coord) {
    return RGBColor::rep(0.0f);
}

rt::RGBColor PerlinTexture::getColorDY(const Point& coord) {
    return RGBColor::rep(0.0f);
}

void PerlinTexture::addOctave(float amplitude, float frequency) {
    a.push_back(amplitude);
	f.push_back(frequency);
}

}