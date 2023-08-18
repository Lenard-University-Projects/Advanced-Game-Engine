#pragma once
#include "Component.h"
#include "Material.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

namespace QEngine{
	class Renderer : public Component {
	protected:
		Material * material;
		glm::mat4 mvp, modelMatrix;
	public:
		Renderer(GameObject * gameObject, Material *material) :Component(gameObject){
			this->material = material;
		}
		~Renderer(){}
	};
}
