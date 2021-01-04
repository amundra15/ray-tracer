#include <rt/materials/dummy.h>
#include <core/assert.h>

namespace rt {

DummyMaterial::DummyMaterial() {
    /* TODO */
}

/*
– inDir – the direction vector (in world coordinate space) from which the light is incoming
– outDir – the direction to the viewer, where the light is reflected to
– normal – the surface normal vector at the hit point
– texPoint – the local coordinate of the hit point.
*/

RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
	float cosTheta = dot(inDir,normal) / (inDir.length()*normal.length());
	return RGBColor::rep(1.0f * cosTheta);
}

RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor::rep(0.0f);
}

Material::SampleReflectance DummyMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ NOT_IMPLEMENTED;
}

}