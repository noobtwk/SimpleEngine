#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include"Texture2D.h"
#include<vector>

class Material
{
public:
	Material();
	~Material();

	void setDiffuseMap(std::vector<Texture2D*> diffuse);
	void setSpecularMap(std::vector<Texture2D*> specular);
	void setReflectionMap(std::vector<Texture2D*> reflection);
	void setHeighMap(std::vector<Texture2D*> heigh);
	void setNormalMap(std::vector<Texture2D*> normal);
	void setAmbientMap(std::vector<Texture2D*> ambient);
	void setLightMap(std::vector<Texture2D*> light);
	void setDisplacementMap(std::vector<Texture2D*> displacement);
	void setShininessMap(std::vector<Texture2D*> shininess);

	std::vector<Texture2D*> getDiffuseMap() const;
	std::vector<Texture2D*> getSpecularMap() const;
	std::vector<Texture2D*> getReflectionMap() const;
	std::vector<Texture2D*> getHeighMap() const;
	std::vector<Texture2D*> getNormalMap() const;
	std::vector<Texture2D*> getAmbientMap() const;
	std::vector<Texture2D*> getLightMap() const;
	std::vector<Texture2D*> getDisplacementMap() const;
	std::vector<Texture2D*> getShininessMap() const;

private:
	std::vector<Texture2D*> diffuseMap;
	std::vector<Texture2D*> specularMap;
	std::vector<Texture2D*> reflectionMap;
	std::vector<Texture2D*> heighMap;
	std::vector<Texture2D*> normalMap;
	std::vector<Texture2D*> ambientMap;
	std::vector<Texture2D*> lightMap;
	std::vector<Texture2D*> displacementMap;
	std::vector<Texture2D*> shininessMap;
};

#endif // !MATERIAL_H
