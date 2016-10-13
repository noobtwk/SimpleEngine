#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::setDiffuseMap(std::vector<Texture2D*>  diffuse)
{
	diffuseMap = diffuse;
}

void Material::setSpecularMap(std::vector<Texture2D*>  specular)
{
	specularMap = specular;
}

void Material::setReflectionMap(std::vector<Texture2D*>  reflection)
{
	reflectionMap = reflection;
}

void Material::setHeighMap(std::vector<Texture2D*>  heigh)
{
	heighMap = heigh;
}

void Material::setNormalMap(std::vector<Texture2D*>  normal)
{
	normalMap = normal;
}

void Material::setAmbientMap(std::vector<Texture2D*>  ambient)
{
	ambientMap = ambient;
}

void Material::setLightMap(std::vector<Texture2D*>  light)
{
	lightMap = light;
}

void Material::setDisplacementMap(std::vector<Texture2D*>  displacement)
{
	displacementMap = displacement;
}

void Material::setShininessMap(std::vector<Texture2D*> shininess)
{
	shininessMap = shininess;
}

std::vector<Texture2D*>  Material::getDiffuseMap() const
{
	return diffuseMap;
}

std::vector<Texture2D*>  Material::getSpecularMap() const
{
	return specularMap;
}

std::vector<Texture2D*>  Material::getReflectionMap() const
{
	return reflectionMap;
}

std::vector<Texture2D*>  Material::getHeighMap() const
{
	return heighMap;
}

std::vector<Texture2D*>  Material::getNormalMap() const
{
	return normalMap;
}

std::vector<Texture2D*>  Material::getAmbientMap() const
{
	return ambientMap;
}

std::vector<Texture2D*>  Material::getLightMap() const
{
	return lightMap;
}

std::vector<Texture2D*>  Material::getDisplacementMap() const
{
	return displacementMap;
}

std::vector<Texture2D*> Material::getShininessMap() const
{
	return shininessMap;
}
