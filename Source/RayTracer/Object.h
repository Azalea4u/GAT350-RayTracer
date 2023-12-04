#pragma once
#include "Material.h"
#include <memory>

class Object
{
public:
	Object() = default;
	Object(std::shared_ptr<Material> material) :
		//<shared pointer of type Material> material) :
		m_material{ material } {}

	virtual bool Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) = 0;
		//< make pure virtual > ;

	Material* GetMaterial() { return m_material.get(); }
		//<get the raw pointer of the m_material>; }

protected:
	std::shared_ptr<Material> m_material;
		//<shared pointer of type Material> m_material;
};