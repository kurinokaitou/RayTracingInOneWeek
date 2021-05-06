#ifndef MATERIAL_H
#define MATERIAL_H
#include "vec3.h"
enum class MaterialType
{
	DIFFUSE,
	DIFFUSE_AND_GLOSSY,
	REFLECTIVE_AND_GLOSSY,
	REFLECTIVE_AND_REFRACTIVE,
	REFLECTIVE
};
class Material
{
public:
	Material() = default;
	Material(const color c,const vec3 e, MaterialType t = MaterialType::DIFFUSE_AND_GLOSSY):type(t),col(c),emittion(e){
		ior = 1.2;
		ka = 0.2;
		kd = 0.5;
		ks = 1.0;
		specularExponent = 150;
		albedo = 0.5;
	}
	MaterialType getType() const { return type; }
	color getBaseColor() const { return col; }
	vec3 getEmittion() const { return emittion; }
	double getKa() const { return ka; }
	double getKd() const{ return kd; }
	double getKs() const{ return ks; }
	double getSpecular() const{ return specularExponent; }
	double getIor() const { return ior; }
	double getAlbedo() const { return albedo; }
	void setIor(double Ior) { ior = Ior; }
private:
	MaterialType type = MaterialType::DIFFUSE_AND_GLOSSY;
	color col = color(0.0);
	vec3 emittion = vec3(0.0);
	double ior = 1.0;
	double ka = 0.0;
	double kd = 0.0;
	double ks = 0.0;
	double specularExponent = 0.0;
	double albedo = 0.5;
};
#endif
