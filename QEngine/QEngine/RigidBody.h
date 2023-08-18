#pragma once
#include "Component.h"
#include "Transform.h"
#include "btBulletDynamicsCommon.h"

namespace QEngine
{
	class RigidBody : public Component
	{
	public:
		RigidBody(GameObject* gameObject, btCollisionShape* shape, btDiscreteDynamicsWorld* pWorld, btScalar mass, btVector3* scale, btVector3* offset);
		~RigidBody();

	private:
		bool isStatic;

		btScalar mass;
		btDefaultMotionState* motionState;
		btDiscreteDynamicsWorld* physicsWorld;
		btRigidBody* rb;

	public:
		void Initialise();
		void Update();

		bool IsStatic();		
		
		void GetPhysicsObjectTransform(btScalar* transform);
		btRigidBody* GetPhysicsRigidBody();
	};
}